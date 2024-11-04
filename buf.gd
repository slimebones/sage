# Buffers take care of most core operations, and gives control of
# insert and visual modes implementation, as well as dispatches executed
# commands to a connected processor.
extends Control
class_name Buf

@export var _mode_text: Label
@export var _cmd_text: Label
@export var _debug_text: Label

# Modes carry the general idea of working with buf's content, but can be
# implemented differently per content's processor choice.
enum Mode {
	Normal,
	Insert,
	Visual,
	Cmd,
}

enum ContentType {
	Str,
	Bytes,
}

# Path to file opened within buf where the content fetched from.
var content_path: String = ""
var content_type: ContentType
# We use arrays for all content representations, since it's convenient,
# especially for editors.
# Content string array, if can represent
var content_str: PackedStringArray = []
# Content bytes, if can represent
var content_bytes: PackedByteArray = []

var _mode: Mode
var is_active: bool = false
var _processor: Node = null

var _is_shift_pressed: bool = false
var _is_ctrl_pressed: bool = false
var _is_alt_pressed: bool = false
var _last_processed_keycode: int = -1
var _last_pressed_keycode: int = -1
var _await_next_insert_escape: bool = false
var _last_inp_time: int = 0
var _same_inp_delay: int = 100
var _keychain_index: int = 0
var _possible_keychains = {}

var _cmd_field_text: String = ""

func connect_processor(a_processor: Node):
	if _processor != null:
		_processor.set_buf(null)
	_processor = a_processor
	_processor.set_buf(self)

func debug(a_text: String):
	_debug_text.text = a_text

func _ready() -> void:
	# TMP, connect editor by default
	content_type = ContentType.Str
	content_str = [""]
	connect_processor($Editor)

	# All bufs start in normal mode
	set_mode(Mode.Normal, true)
	_reset_keychain()

func get_mode() -> Mode:
	return _mode

func set_mode(a_mode: Mode, should_callback_processor: bool = false):
	if a_mode == _mode:
		return
	var old_mode = _mode
	_mode = a_mode
	_mode_text.text = _str_mode()
	if should_callback_processor && _processor != null:
		_processor.on_mode_changed(old_mode, _mode)
	queue_redraw()

func _is_keychain_started():
	return _keychain_index > 0

func _str_mode():
	match _mode:
		Mode.Normal:
			return "Normal"
		Mode.Insert:
			return "Insert"
		Mode.Visual:
			return "Visual"
		Mode.Cmd:
			return "Command"

func _reset_keychain():
	_keychain_index = 0
	_possible_keychains = common.config.layout.keychains

func _process_normal_keychains():
	# We wait infinitely for the new keycode while in keychain
	if _last_pressed_keycode == -1:
		return

	var _old_keychain_index = _keychain_index
	var new_possible_keychains = {}
	for cmd in _possible_keychains.keys():
		var keychain = _possible_keychains[cmd]
		# Since we increase keychain index before processing the
		# _possible_keychains dictionary, we need to be sure we don't hit any
		# already-invalid keychains.
		if _keychain_index >= keychain.size():
			continue

		if (
			keychain[_keychain_index] is Inp.Shifted
			&& _is_shift_pressed
			&& keychain[_keychain_index].keycode == _last_pressed_keycode
		) || (
			!(keychain[_keychain_index] is Inp.Shifted)
			&& !_is_shift_pressed
			&& !_is_ctrl_pressed
			&& !_is_alt_pressed
			&& keychain[_keychain_index] == _last_pressed_keycode
		):
			# Last hit keychain lead to the final command execution
			if keychain.size() - 1 == _keychain_index:
				_execute_cmd(cmd)
				_reset_keychain()
				return
			# Increment only once
			if new_possible_keychains.size() == 0:
				_keychain_index += 1
			new_possible_keychains[cmd] = keychain

	var current_combination = _possible_keychains.values()[0].slice(0, _keychain_index)
	if new_possible_keychains.size() == 0:
		print("Unknown combination: ", current_combination)
		_reset_keychain()
		return
	_possible_keychains = new_possible_keychains

func _execute_cmd(cmd: String):
	var r = _processor.execute_cmd(cmd)
	if err.ee(r):
		print("Error: ", r.msg)
	elif r != "":
		print(r)

func _process_normal_mode():
	# We block any other actions if we've hit the keychain
	if _is_keychain_started():
		_process_normal_keychains()
	elif _last_pressed_keycode == common.config.layout.toggle_cmd_mode:
		set_mode(Mode.Cmd, true)
		_cmd_text.text = "> "
		_cmd_text.visible = true
		_mode_text.visible = false
	elif _last_pressed_keycode == common.config.layout.toggle_insert_mode:
		set_mode(Mode.Insert, true)
	elif _last_pressed_keycode == common.config.layout.toggle_visual_mode:
		set_mode(Mode.Visual, true)
	else:
		_process_normal_keychains()

	_last_inp_time = core.time()
	_last_processed_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

func _process_cmd_mode():
	if _last_pressed_keycode == common.config.layout.toggle_cmd_mode:
		set_mode(Mode.Normal, true)
		_execute_cmd(_cmd_field_text)
		_cmd_text.visible = false
		_mode_text.visible = true
		_cmd_field_text = ""
		_cmd_text.text = ""
	else:
		var c = ""
		if _is_shift_pressed:
			c = common.config.layout.writables[_last_pressed_keycode][1]
		else:
			c = common.config.layout.writables[_last_pressed_keycode][0]
		_write_cmd_field(c)
	_last_inp_time = core.time()
	_last_processed_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

func _process_visual_mode():
	if _last_pressed_keycode == common.config.layout.toggle_visual_mode:
		set_mode(Mode.Normal, true)
	elif _processor != null:
		var flag = _processor.on_key_pressed(
			_mode,
			_last_pressed_keycode,
			_is_shift_pressed,
			_is_alt_pressed,
			_is_ctrl_pressed,
		)
		if flag == ProcessorFlag.KeySkip:
			return
		if flag == ProcessorFlag.KeyReset:
			_last_pressed_keycode = -1
			return
	_last_inp_time = core.time()
	_last_processed_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

enum ProcessorFlag {
	KeyCooldown,
	KeyReset,
	KeySkip,
}

func _process_insert_mode():
	if _processor != null:
		var flag = _processor.on_key_pressed(
			_mode,
			_last_pressed_keycode,
			_is_shift_pressed,
			_is_alt_pressed,
			_is_ctrl_pressed,
		)
		if flag == ProcessorFlag.KeySkip:
			return
		if flag == ProcessorFlag.KeyReset:
			_last_pressed_keycode = -1
			return
	_last_inp_time = core.time()
	_last_processed_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

func _physics_process(_delta: float) -> void:
	if Input.is_key_pressed(KEY_ESCAPE):
		get_tree().quit()
		return
	_read_keys()

	# Prevent too fast input handling
	if _last_pressed_keycode == -1 || (
		_last_pressed_keycode == _last_processed_keycode
		&& core.is_cooldown(_last_inp_time, _same_inp_delay)
	):
		_last_pressed_keycode = -1
		return

	if _mode == Mode.Insert:
		if _last_pressed_keycode == common.config.layout.toggle_insert_mode:
			if !_await_next_insert_escape:
				_await_next_insert_escape = true
			else:
				set_mode(Mode.Normal, true)
				_await_next_insert_escape = false
				_last_inp_time = core.time()
				_last_processed_keycode = _last_pressed_keycode
				_last_pressed_keycode = -1
				return
		else:
			_await_next_insert_escape = false

	match _mode:
		Mode.Normal:
			_process_normal_mode()
		Mode.Cmd:
			_process_cmd_mode()
		Mode.Insert:
			_process_insert_mode()
		Mode.Visual:
			_process_visual_mode()

func _read_keys():
	_is_shift_pressed = Input.is_key_pressed(KEY_SHIFT)
	_is_ctrl_pressed = Input.is_key_pressed(KEY_CTRL)
	_is_alt_pressed = Input.is_key_pressed(KEY_ALT)

	if _last_pressed_keycode == -1:
		for keycode in Inp.KEYCODES:
			if Input.is_key_pressed(keycode):
				_last_pressed_keycode = keycode
				return
		_last_pressed_keycode = -1

func _write_cmd_field(c: String):
	assert(c.length() <= 1)
	if c == "":
		return

	# For command field we always treat tabs as a single space.
	c = c.replace("\t", " ")
	_cmd_field_text += c
	_cmd_text.text = "> %s" % _cmd_field_text

func _erase_cmd_field_left_char():
	_cmd_field_text = _cmd_field_text.substr(0, _cmd_field_text.length() - 1)
	_cmd_text.text = "> %s" % _cmd_field_text

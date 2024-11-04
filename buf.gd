# Buffers take care of most core operations, and gives control of
# insert and visual modes implementation, as well as dispatches executed
# commands to a connected processor.
extends Control
class_name Buf

@onready var _mode_text: Label = core.find("Info/Mode")
@onready var _cmd_text: Label = core.find("Info/Cmd")
@onready var _debug_text: Label = core.find("Info/Debug")

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

# Path to content_file opened within buf where the content is fetched from.
var content_path: String = ""
# Opened content_file for a buffer. Buffer opens a content_file as soon as it gets a path.
# The opening mode, for now, is always FileAccess.READ_WRITE.
# But buffer never reads the content_file to fill it's content_type, content_str,
# content_bytes, etc., to give such an opportunity to processor
var content_file: FileAccess = null
var content_type: ContentType
# We use arrays for all content representations, since it's convenient,
# especially for editors.
# Content string array, if can represent
var content_str: PackedStringArray = []
# Content bytes, if can represent
var content_bytes: PackedByteArray = []

var _mode: Mode
var _buf_num: int = 1
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

func open_file(a_path: String):
	if content_file != null:
		_processor.on_file_closing(content_file)
		content_file.close()
	content_path = a_path

	var content_ext = path.get_ext(content_path)
	if content_ext == "" || !common.config.buf_content_processor_scenes.has(content_ext):
		content_ext = "_default"
	var _new_processor_scene = \
		common.config.buf_content_processor_scenes[content_ext]
	# Don't reinitialize the processor if it's the same.
	if !_new_processor_scene.is_class(_processor.get_class()):
		connect_processor(_new_processor_scene)

	content_file = FileAccess.open(a_path, FileAccess.READ_WRITE)
	_processor.on_file_opened.call_deferred(content_file)

func connect_processor(a_processor_scene: PackedScene):
	if _processor != null:
		_processor.disconnect_buf()
		_processor.queue_free()
	_processor = a_processor_scene.instantiate()
	add_child.call_deferred(_processor)
	_processor.connect_buf.call_deferred(self)

func debug(a_text: String):
	_debug_text.text = a_text

func _ready() -> void:
	# All bufs start in normal mode, with default processor
	connect_processor(common.config.buf_content_processor_scenes["_default"])
	set_mode(Mode.Normal, true)
	_reset_keychain()

func get_mode() -> Mode:
	return _mode

func set_mode(a_mode: Mode, should_callback_processor: bool = false):
	if a_mode == _mode:
		return
	var old_mode = _mode
	_mode = a_mode
	_mode_text.text = "#%d: %s" % [_buf_num, _str_mode()]
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

# Buffer-specific commands - don't send to processor.
var _cmds = {
	"open": _toggle_open_window,
}

func _toggle_open_window():
	open_file(common.var_dir.path_join("assets/test.txt"))

func _execute_cmd(cmd: String):
	var r

	if _cmds.has(cmd):
		r =_cmds[cmd].call()
	else:
		r = _processor.execute_cmd(cmd)

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

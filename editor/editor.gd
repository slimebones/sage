extends Control

enum Mode {
	Normal,
	Insert,
	Visual,
	Cmd,
}

# We don't have SHIFT, CTRL and ALT here, since we use them in various
# combinations.
const KEYCODES = [
	KEY_ESCAPE,

	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,

	KEY_QUOTELEFT,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_BACKSPACE,

	KEY_TAB,
	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_T,
	KEY_Y,
	KEY_U,
	KEY_I,
	KEY_O,
	KEY_P,
	KEY_BRACKETLEFT,
	KEY_BRACKETRIGHT,
	KEY_BACKSLASH,

	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_ENTER,

	KEY_Z,
	KEY_X,
	KEY_C,
	KEY_V,
	KEY_B,
	KEY_N,
	KEY_M,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,

	KEY_SPACE,
]
const WRITABLE_KEYCODES = {
	KEY_QUOTELEFT: ["`", "~"],
	KEY_1: ["1", "!"],
	KEY_2: ["2", "@"],
	KEY_3: ["3", "#"],
	KEY_4: ["4", "$"],
	KEY_5: ["5", "%"],
	KEY_6: ["6", "^"],
	KEY_7: ["7", "&"],
	KEY_8: ["8", "*"],
	KEY_9: ["9", "("],
	KEY_0: ["0", ")"],
	KEY_MINUS: ["-", "_"],
	KEY_EQUAL: ["=", "+"],
	# Does erasing, so technically is "Writable"
	KEY_BACKSPACE: ["", ""],

	KEY_TAB: ["\t", "\t"],
	KEY_Q: ["q", "Q"],
	KEY_W: ["w", "W"],
	KEY_E: ["e", "E"],
	KEY_R: ["r", "R"],
	KEY_T: ["t", "T"],
	KEY_Y: ["y", "Y"],
	KEY_U: ["u", "U"],
	KEY_I: ["i", "I"],
	KEY_O: ["o", "O"],
	KEY_P: ["p", "P"],
	KEY_BRACKETLEFT: ["[", "{"],
	KEY_BRACKETRIGHT: ["]", "}"],
	KEY_BACKSLASH: ["\\", "|"],

	KEY_A: ["a", "A"],
	KEY_S: ["s", "S"],
	KEY_D: ["d", "D"],
	KEY_F: ["f", "F"],
	KEY_G: ["g", "G"],
	KEY_H: ["h", "H"],
	KEY_J: ["j", "J"],
	KEY_K: ["k", "K"],
	KEY_L: ["l", "L"],
	KEY_SEMICOLON: [";", ":"],
	KEY_APOSTROPHE: ["'", "\""],
	KEY_ENTER: ["\n", "\n"],

	KEY_Z: ["z", "Z"],
	KEY_X: ["x", "X"],
	KEY_C: ["c", "C"],
	KEY_V: ["v", "V"],
	KEY_B: ["b", "B"],
	KEY_N: ["n", "N"],
	KEY_M: ["m", "M"],
	KEY_COMMA: [",", "<"],
	KEY_PERIOD: [".", ">"],
	KEY_SLASH: ["/", "?"],

	KEY_SPACE: [" ", " "],
}

class Shifted:
	var keycode: int = -1

	func _init(a_keycode: int):
		keycode = a_keycode

class Layout:
	var toggle_cmd_mode: int = KEY_ENTER
	var toggle_visual_mode: int = KEY_V
	var toggle_insert_mode: int = KEY_I

	# Binds that invoke commands. Works only in normal mode.
	# We only allow one bind per command for simplicity and
	# straightforwardness.
	#
	# Once the editor is in keychain flag, and in normal mode, it accepts
	# combinations in strict order, unless they have no continuation, or lead
	# to the final command.
	var keychains = {
		"left": [KEY_J],
		"down": [KEY_K],
		"up": [KEY_L],
		"right": [KEY_SEMICOLON],
		"open": [KEY_SPACE, KEY_O],
		"append": [KEY_A],
		"append_line": [KEY_O],
		"prepend_line": [Shifted.new(KEY_O)],
	}

var _cmd_to_fn = {
	"left": func f():
		_move_caret(-1, 0)
		queue_redraw(),
	"right": func f():
		_move_caret(1, 0)
		queue_redraw(),
	"up": func f():
		_move_caret(0, -1)
		queue_redraw(),
	"down": func f():
		_move_caret(0, 1)
		queue_redraw(),
	"open": _toggle_open,
	"append": _toggle_append,
	"append_line": _append_line,
	"prepend_line": _prepend_line,
}

class Settings:
	var layout: Layout = Layout.new()

var settings: Settings = Settings.new()

var _keychain_index: int = 0
var _possible_keychains = {}

var _mode: Mode
var _is_shift_pressed: bool = false
var _is_ctrl_pressed: bool = false
var _is_alt_pressed: bool = false
var _last_processed_keycode: int = -1
var _last_pressed_keycode: int = -1
var _await_next_insert_escape: bool = false
var _last_inp_time: int = 0
var _same_inp_delay: int = 100
var _font_size: int = 32

var _caret: Vector2i = Vector2i.ZERO

@onready var _mode_text = core.find("Info/Mode")
@onready var _cmd_text = core.find("Info/Cmd")
@onready var _debug_text = core.find("Info/Debug")
@onready var _font = preload("res://assets/monogram.ttf")
@onready var _caret_text = core.find("CaretText")
var line_spacing: float = 20

enum IndentMode {
	Tab,
	Space,
}
var indent_mode: IndentMode = IndentMode.Tab
# How many pixels to use for a tab
var tab_size: float = 40
# Actual only for IndentMode.Space. How many spaces are inserted per tab.
var space_indent_amount: int = 4

var line_number_right_margin: float = 50
var lines: PackedStringArray = [""]
var line_sizes: PackedInt64Array = []
var line_y_poses: PackedFloat64Array = []
var normal_cursor_size: Vector2 = Vector2(10, -20)
var insert_cursor_size: Vector2 = Vector2(1, -20)

func _ready() -> void:
	_set_mode(Mode.Normal)
	_reset_keychain()

func _reset_keychain():
	_keychain_index = 0
	_possible_keychains = settings.layout.keychains

func _is_keychain_started():
	return _keychain_index > 0

func _set_mode(a_mode: Mode):
	_mode = a_mode
	_mode_text.text = _str_mode()
	queue_redraw()

## Draws cursor at caret position.
func _draw_cursor():
	var caret_pos = _get_caret_pos()
	if _mode == Mode.Insert:
		var rect: Rect2 = Rect2(caret_pos, insert_cursor_size)
		draw_rect(rect, Color(1, 1, 1, 1))
	elif _mode == Mode.Normal:
		var rect: Rect2 = Rect2(caret_pos, normal_cursor_size)
		draw_rect(rect, Color(1, 1, 1, 0.5))

func _get_caret_pos() -> Vector2:
	var caret_line = _get_caret_line()
	var caret_line_x = \
		line_number_right_margin \
		+ _font.get_string_size(
			caret_line.substr(0, _caret.x),
			HORIZONTAL_ALIGNMENT_LEFT,
			-1,
			_font_size
		).x
	var caret_line_y = line_y_poses[_caret.y]
	return Vector2(
		caret_line_x,
		caret_line_y
	)

func _draw() -> void:
	var pos = Vector2(0, line_spacing)
	var lineno = 1
	line_sizes = []
	line_y_poses = []
	for line in lines:
		draw_string(
			_font,
			Vector2(
				0 - _font.get_string_size(
					String.num_uint64(lineno), HORIZONTAL_ALIGNMENT_LEFT, -1, _font_size
				).x,
				pos.y
			),
			"%d" % lineno,
			HORIZONTAL_ALIGNMENT_CENTER,
			-1,
			_font_size,
			Color(1, 1, 1, 0.25)
		)
		line_y_poses.append(pos.y)
		var tabbed_parts = line.split("\t")
		pos.x = line_number_right_margin
		var i = 0
		for part in tabbed_parts:
			draw_string(_font, pos, part, HORIZONTAL_ALIGNMENT_CENTER, -1, _font_size)

			var str_size = _font.get_string_size(
				part, HORIZONTAL_ALIGNMENT_CENTER, -1, _font_size
			)
			pos.x += str_size.x
			var before_tab_pos = pos
			pos.x += tab_size
			var after_tab_pos = pos

			# Draw graphics for tabs
			if i < tabbed_parts.size() - 1:
				var font_height = _font.get_height(_font_size) / 4
				before_tab_pos.y -= font_height
				after_tab_pos.y -= font_height
				# Disabled for now
				# draw_dashed_line(before_tab_pos, after_tab_pos, Color.GRAY, -1, 4)
			i += 1

		var line_size = line.length()
		if lineno < lines.size():
			# Count+Write newline sign
			lines[lineno - 1] += "\n"
			line_size += 1
		line_sizes.append(line_size)

		pos.y += line_spacing
		lineno += 1

	_draw_cursor()

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

## Move display by pixels.
func _move_display(v: Vector2):
	# TODO: Implement display movement
	pass

## `chars` can be negative to move to the left, otherwise move to the right.
func _move_display_horizontal_chars(chars: int):
	# TODO: Implement display movement
	pass

## `lines` can be negative to move to the top, otherwise move to the bottom.
func _move_display_vertical_lines(lines: int):
	# TODO: Implement display movement
	pass

func _move_caret(x: int, y: int):
	var offset = Vector2i(x, y)
	_caret += offset

	if _caret.x < 0:
		_caret.x = 0
	if _caret.y < 0:
		_caret.y = 0

	if _caret.y > lines.size() - 1:
		_caret.y = lines.size() - 1
	# If a caret moves to a new line, the X position will always be at the end,
	# if overflown
	if _caret.x > lines[_caret.y].length():
		_caret.x = lines[_caret.y].length()

enum WriteTarget {
	Buffer,
	CmdField,
}

var _cmd_field_text: String = ""

## Write at current caret position.
func _write(c: String, target: WriteTarget):
	assert(c.length() <= 1)
	if c == "":
		return

	if indent_mode == IndentMode.Space:
		var space_chunk = ""
		for _i in range(space_indent_amount):
			space_chunk += " "
		c = c.replace("\t", space_chunk)

	if target == WriteTarget.Buffer:
		if c == "\n":
			var remaining = lines[_caret.y].substr(_caret.x)
			lines[_caret.y] = lines[_caret.y].substr(0, _caret.x)
			lines.append(remaining)
			_move_caret(0, 1)
			_caret.x = 0
		else:
			_set_caret_line(lines[_caret.y].insert(_caret.x, c))
			_move_caret(1, 0)
		queue_redraw()
	elif target == WriteTarget.CmdField:
		_cmd_field_text += c
		_cmd_text.text = "> %s" % _cmd_field_text

func _get_caret_line() -> String:
	return lines[_caret.y]

func _set_caret_line(s: String):
	lines[_caret.y] = s

func _erase_left_char(target: WriteTarget):
	if target == WriteTarget.Buffer:
		if _caret == Vector2i.ZERO:
			return

		if _get_caret_line().length() == 0:
			lines.remove_at(_caret.y)
			_move_caret(0, -1)
			# Put caret to the end of the previous line upon erasing the old
			# one
			_caret.x = _get_caret_line().length()
			queue_redraw()
			return
		# We can erase only by positive count, so we move caret to the left by
		# the required amount, and only then erase.
		_move_caret(-1, 0)
		_set_caret_line(_get_caret_line().erase(_caret.x, 1))
		queue_redraw()
	elif target == WriteTarget.CmdField:
		_cmd_field_text = _cmd_field_text.substr(0, _cmd_field_text.length() - 1)
		_cmd_text.text = "> %s" % _cmd_field_text

func _debug(a_text: String):
	_debug_text.text = a_text

func _process_keyboard():
	_is_shift_pressed = Input.is_key_pressed(KEY_SHIFT)
	_is_ctrl_pressed = Input.is_key_pressed(KEY_CTRL)
	_is_alt_pressed = Input.is_key_pressed(KEY_ALT)

	if _last_pressed_keycode == -1:
		for keycode in KEYCODES:
			if Input.is_key_pressed(keycode):
				_last_pressed_keycode = keycode
				return
		_last_pressed_keycode = -1

func _process_insert():
	if !WRITABLE_KEYCODES.has(_last_pressed_keycode):
		_last_pressed_keycode = -1
		return

	if _last_pressed_keycode == KEY_BACKSPACE:
		_erase_left_char(WriteTarget.Buffer)
	else:
		var c = ""
		if _is_shift_pressed:
			c = WRITABLE_KEYCODES[_last_pressed_keycode][1]
		else:
			c = WRITABLE_KEYCODES[_last_pressed_keycode][0]
		_write(c, WriteTarget.Buffer)
	_last_inp_time = core.time()
	_last_processed_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

func _process_normal():
	# We block any other actions if we've hit the keychain
	if _is_keychain_started():
		_process_normal_keychains()
	elif _last_pressed_keycode == settings.layout.toggle_cmd_mode:
		_set_mode(Mode.Cmd)
		_cmd_text.text = "> "
		_cmd_text.visible = true
		_mode_text.visible = false
	elif _last_pressed_keycode == settings.layout.toggle_insert_mode:
		_set_mode(Mode.Insert)
	else:
		_process_normal_keychains()

	_last_inp_time = core.time()
	_last_processed_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

func _process_normal_keychains():
	# We wait infinitely for the new keycode while in keychain
	if _last_pressed_keycode == -1:
		return

	var _old_keychain_index = _keychain_index
	var new_possible_keychains = {}
	for cmd in _possible_keychains.keys():
		var keychain = _possible_keychains[cmd]
		if (
			keychain[_keychain_index] is Shifted
			&& _is_shift_pressed
			&& keychain[_keychain_index].keycode == _last_pressed_keycode
		) || (
			!_is_shift_pressed
			&& !_is_ctrl_pressed
			&& !_is_alt_pressed
			&& keychain[_keychain_index] == _last_pressed_keycode
		):
			# Last hit keychain lead to the final command execution
			if keychain.size() - 1 == _keychain_index:
				_exe_cmd(cmd)
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

func _exe_cmd(cmd: String):
	if !_cmd_to_fn.has(cmd):
		print("Not found: ", cmd)
		return
	print("Executing: ", cmd)
	_cmd_to_fn[cmd].call()

func _process_cmd_mode():
	if _last_pressed_keycode == settings.layout.toggle_cmd_mode:
		_set_mode(Mode.Normal)
		_exe_cmd(_cmd_field_text)
		_cmd_text.visible = false
		_mode_text.visible = true
		_cmd_field_text = ""
		_cmd_text.text = ""
	elif _last_pressed_keycode == KEY_BACKSPACE:
		_erase_left_char(WriteTarget.CmdField)
	else:
		var c = ""
		if _is_shift_pressed:
			c = WRITABLE_KEYCODES[_last_pressed_keycode][1]
		else:
			c = WRITABLE_KEYCODES[_last_pressed_keycode][0]
		_write(c, WriteTarget.CmdField)
	_last_inp_time = core.time()
	_last_processed_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

func _process_visual():
	pass

func _physics_process(_delta: float) -> void:
	_caret_text.text = "(%d,%d)" % [_caret.x, _caret.y]
	if Input.is_key_pressed(KEY_ESCAPE):
		get_tree().quit()
		return
	_process_keyboard()

	# Prevent too fast input handling
	if _last_pressed_keycode == -1 || (_last_pressed_keycode == _last_processed_keycode && core.is_cooldown(_last_inp_time, _same_inp_delay)):
		_last_pressed_keycode = -1
		return

	if _mode == Mode.Insert:
		if _last_pressed_keycode == settings.layout.toggle_insert_mode:
			if !_await_next_insert_escape:
				_await_next_insert_escape = true
			else:
				# Erase last written `i` symbols
				_erase_left_char(WriteTarget.Buffer)
				_set_mode(Mode.Normal)
				_await_next_insert_escape = false
				_last_inp_time = core.time()
				_last_processed_keycode = _last_pressed_keycode
				_last_pressed_keycode = -1
				return
		else:
			_await_next_insert_escape = false

	match _mode:
		Mode.Normal:
			_process_normal()
		Mode.Cmd:
			_process_cmd_mode()
		Mode.Insert:
			_process_insert()
		Mode.Visual:
			_process_visual()

func _toggle_open():
	pass

func _toggle_append():
	_move_caret(1, 0)
	_set_mode(Mode.Insert)
	queue_redraw()

func _append_line():
	lines.insert(_caret.y + 1, "")
	_move_caret(0, 1)
	_set_mode(Mode.Insert)
	queue_redraw()

func _prepend_line():
	lines.insert(_caret.y, "")
	_move_caret(0, -1)
	_set_mode(Mode.Insert)
	queue_redraw()

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

class FollowingKeychain:
	var following: Array
	var cmd: StringName

	func _init(f: Array, c: StringName):
		following = f
		cmd = c

class Layout:
	var toggle_cmd_mode: int = KEY_ENTER
	var toggle_visual_mode: int = KEY_V
	var enable_insert_mode: int = KEY_I

	# Binds that invoke commands. Works only in normal mode
	var cmd_binds = {
		KEY_H: [
			FollowingKeychain.new(
				[],
				"left"
			),
		],
		KEY_K: [
			FollowingKeychain.new(
				[],
				"down"
			),
		],
		KEY_L: [
			FollowingKeychain.new(
				[],
				"up"
			),
		],
		KEY_SEMICOLON: [
			FollowingKeychain.new(
				[],
				"right"
			),
		],
		KEY_SPACE: [
			FollowingKeychain.new(
				[KEY_O],
				"open"
			),
		],
	}

class Settings:
	var layout: Layout = Layout.new()

var settings: Settings = Settings.new()

# !!
var _is_keychain_started = false
# Which keys are available to continue the combination
var _next_possible_keychains: Array = []

var _mode: Mode
var _is_shift_pressed: bool = false
var _is_ctrl_pressed: bool = false
var _is_alt_pressed: bool = false
var _last_processed_keycode: int = -1
var _last_pressed_keycode: int = -1
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
	_next_possible_keys = settings.layout.cmd_binds.keys()

func _set_mode(a_mode: Mode):
	_mode = a_mode
	_mode_text.text = _get_mode_str()
	queue_redraw()

## Draws cursor at caret position.
func _draw_cursor():
	var caret_pos = _get_caret_pos()
	if _mode == Mode.Insert:
		var rect: Rect2 = Rect2(caret_pos, insert_cursor_size)
		draw_rect(rect, Color.WHITE)
	elif _mode == Mode.Normal:
		var rect: Rect2 = Rect2(caret_pos, normal_cursor_size)
		draw_rect(rect, Color.WHITE)

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

func _get_mode_str():
	match _mode:
		Mode.Normal:
			return "Normal"
		Mode.Insert:
			return "Insert"
		Mode.Visual:
			return "Visual"
		Mode.Cmd:
			return "Command"

func _move_caret(x: int, y: int):
	var offset = Vector2i(x, y)
	_caret += offset

	if _caret.x < 0:
		_caret.x = 0
	if _caret.y < 0:
		_caret.y = 0

	if _caret.y > lines.size() - 1:
		_caret.y = lines.size() - 1
	# If caret moves to new line, the X position will always be at the end,
	# if overflown
	if _caret.x > lines[_caret.y].length():
		_caret.x = lines[_caret.y].length()

enum WriteTarget {
	Buffer,
	CmdField,
}

var _cmd_field_text: String = ""

# Write at current caret position.
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
		_set_caret_line(lines[_caret.y].insert(_caret.x, c))
		_move_caret(1, 0)
		if c == "\n":
			lines.append("")
			_move_caret(0, 1)
		queue_redraw()
	elif target == WriteTarget.CmdField:
		_cmd_field_text += c
		_cmd_text.text = "> %s" % _cmd_field_text

func _get_caret_line() -> String:
	return lines[_caret.y]

func _set_caret_line(s: String):
	lines[_caret.y] = s

# Erase certain amount of characters. If the amount is negative, erase to the
# left of the caret, otherwise erase to the right.
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
	if _last_pressed_keycode == settings.layout.toggle_cmd_mode:
		_set_mode(Mode.Cmd)
		_cmd_text.text = "> "
		_cmd_text.visible = true
		_mode_text.visible = false
	elif _last_pressed_keycode == settings.layout.enable_insert_mode:
		_set_mode(Mode.Insert)
	elif _next_possible_keys.has(
	_last_inp_time = core.time()
	_last_processed_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

func _exe_cmd(cmd: String):
	print("Executing: ", cmd)

func _process_cmd():
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

	if _mode == Mode.Insert && _is_alt_pressed:
		_set_mode(Mode.Normal)
		return

	# Prevent too fast input handling
	if _last_pressed_keycode == -1 || (_last_pressed_keycode == _last_processed_keycode && core.is_cooldown(_last_inp_time, _same_inp_delay)):
		_last_pressed_keycode = -1
		return
	match _mode:
		Mode.Normal:
			_process_normal()
		Mode.Cmd:
			_process_cmd()
		Mode.Insert:
			_process_insert()
		Mode.Visual:
			_process_visual()


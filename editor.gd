extends Control

enum Mode {
	Normal,
	Insert,
	Visual,
	Cmd,
}

var _mode = Mode.Insert
var _is_shift_pressed: bool = false
var _is_ctrl_pressed: bool = false
var _is_alt_pressed: bool = false
var _last_written_keycode: int = -1
var _last_pressed_keycode: int = -1
var _last_inp_time: int = 0
var _same_inp_delay: int = 100
var _font_size: int = 32

var _text: String = ""
# Index of which the caret are positioned right now.
var _caret: int = 0

@onready var _mode_text = core.find("Info/Mode")
@onready var _debug_text = core.find("Info/Debug")
@onready var _font = preload("res://assets/monogram.ttf")
var line_spacing: float = 20

enum IndentMode {
	Tab,
	Space,
}
var indent_mode: IndentMode = IndentMode.Tab
# Actual only for IndentMode.Tab
var tab_size: int = 10
# Actual only for IndentMode.Space. How many spaces are inserted per tab.
var space_indent_amount: int = 4

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

	KEY_SHIFT,
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

	KEY_CTRL,
	KEY_ALT,
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

func _ready() -> void:
	_mode_text.text = _get_mode_str()

func _draw() -> void:
	var lines = _text.split("\n")
	var pos = Vector2.ZERO
	for line in lines:
		draw_string(_font, pos, line, HORIZONTAL_ALIGNMENT_LEFT, -1, _font_size)
		pos.y += line_spacing

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

func _move_caret(offset: int):
	_caret += offset
	if _caret < 0:
		_caret = 0
	elif _caret > _text.length():
		_caret = _text.length() - 1

# Write at current caret position.
func _write(a_text: String):
	_text += a_text
	_move_caret(a_text.length())
	queue_redraw()

# Erase certain amount of characters. If the amount is negative, erase to the
# left of the caret, otherwise erase to the right.
func _erase(count: int):
	if count > 0:
		_text = _text.erase(_caret, count)
	else:
		# We can erase only by positive count, so we move caret to the left by
		# the required amount, and only then erase.
		_text = _text.erase(_caret + count, abs(count))
	_move_caret(count)
	queue_redraw()

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
	if (_last_pressed_keycode == _last_written_keycode && core.is_cooldown(_last_inp_time, _same_inp_delay)) \
			|| !WRITABLE_KEYCODES.has(_last_pressed_keycode):
		_last_pressed_keycode = -1
		return

	if _last_pressed_keycode == KEY_BACKSPACE:
		_erase(-1)
	else:
		var c = ""
		if _is_shift_pressed:
			c = WRITABLE_KEYCODES[_last_pressed_keycode][1]
		else:
			c = WRITABLE_KEYCODES[_last_pressed_keycode][0]
		_write(c)
	_last_inp_time = core.time()
	_last_written_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

func _physics_process(_delta: float) -> void:
	_debug("%s" % _caret)
	if Input.is_key_pressed(KEY_ESCAPE):
		get_tree().quit()
	_process_keyboard()
	match _mode:
		Mode.Insert:
			_process_insert()


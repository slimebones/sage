extends Label

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
var _same_inp_delay: int = 500
@onready var _mode_text = core.find("Info/Mode")
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

	KEY_ASCIITILDE,
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

	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_T
]

func _ready() -> void:
	_mode_text.text = _get_mode_str()

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

func _write(a_text: String):
	text += a_text

func _process_keyboard():
	_is_shift_pressed = Input.is_key_pressed(KEY_SHIFT)
	_is_ctrl_pressed = Input.is_key_pressed(KEY_CTRL)
	_is_alt_pressed = Input.is_key_pressed(KEY_ALT)

	if _last_pressed_keycode == -1:
		for keycode in range(100):
			if Input.is_key_pressed(keycode):
				_last_pressed_keycode = keycode
				return
		_last_pressed_keycode = -1

func _process_insert():
	if _last_pressed_keycode == _last_written_keycode && core.is_cooldown(_last_inp_time, _same_inp_delay):
		_last_pressed_keycode = -1
		return
	match _last_pressed_keycode:
		KEY_W:
			_write("w")
		KEY_S:
			_write("s")
		KEY_MINUS:
			_write("-")
	_last_inp_time = core.time()
	_last_written_keycode = _last_pressed_keycode
	_last_pressed_keycode = -1

func _physics_process(_delta: float) -> void:
	if Input.is_key_pressed(KEY_ESCAPE):
		get_tree().quit()
	_process_keyboard()
	match _mode:
		Mode.Insert:
			_process_insert()


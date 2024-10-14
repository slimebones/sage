extends CodeEdit

enum Mode {
	Normal,
	Insert,
	Visual,
	Cmd,
}

var _mode = Mode.Normal
@onready var _mode_text = core.find("Info/Mode")

func _ready() -> void:
	auto_brace_completion_enabled = true
	indent_size = 4
	indent_use_spaces = false
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

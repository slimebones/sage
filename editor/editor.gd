extends Control
class_name Editor

@onready var _font = preload("res://assets/monogram.ttf")

class Config:
	pass

var _cmds = {
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
	"append": _toggle_append,
	"append_line": _append_line,
	"prepend_line": _prepend_line,
}

var _font_size: int = 32
var _caret: Vector2i = Vector2i.ZERO
var line_spacing: float = 20

enum IndentMode {
	Tab,
	Space,
}
var indent_mode: IndentMode = IndentMode.Tab
var tab_graphic: StringName = "    "

var line_number_right_margin: float = 50
var line_sizes: PackedInt64Array = []
var line_y_poses: PackedFloat64Array = []
var normal_cursor_size: Vector2 = Vector2(10, -20)
var insert_cursor_size: Vector2 = Vector2(1, -20)
var _buf: Buf = null

func connect_buf(a_buf: Buf):
	_buf = a_buf
	_buf.content_type = Buf.ContentType.Str
	if _buf.content_file == null:
		_buf.content_str = [""]
	else:
		_read_new_file(_buf.content_file)

func disconnect_buf():
	_buf = null

func _read_new_file(file: FileAccess):
	_buf.content_str = file.get_as_text().split("\n")

func on_file_opened(file: FileAccess):
	_read_new_file(file)

func on_file_closing(_file: FileAccess):
	pass

func on_mode_changed(old_mode: Buf.Mode, new_mode: Buf.Mode):
	match old_mode:
		Buf.Mode.Insert:
			match new_mode:
				Buf.Mode.Normal:
					# Erase last written `i` symbol
					_erase_left_char()
	queue_redraw()

func on_key_pressed(
	mode: Buf.Mode,
	key: int,
	is_shift_pressed: bool,
	is_ctrl_pressed: bool,
	is_alt_pressed: bool,
):
	if mode == Buf.Mode.Insert:
		if !common.config.layout.writables.has(key):
			assert(_buf != null)
			return Buf.ProcessorFlag.KeyReset
		if is_ctrl_pressed || is_alt_pressed:
			return
		if !is_shift_pressed && key == KEY_BACKSPACE:
			_erase_left_char()
			return
		var c = ""
		if is_shift_pressed:
			c = common.config.layout.writables[key][1]
		else:
			c = common.config.layout.writables[key][0]
		_write(c)
	elif mode == Buf.Mode.Visual:
		# TODO: Implement visual
		pass

func execute_cmd(cmd: String):
	if !_cmds.has(cmd):
		return err.err("", err.CODE_NOT_FOUND_ERR)
	_cmds[cmd].call()
	return ""

# Draws cursor at caret position.
func _draw_cursor():
	var caret_pos = _get_caret_pos()
	if _buf.get_mode() == Buf.Mode.Insert:
		var rect: Rect2 = Rect2(caret_pos, insert_cursor_size)
		draw_rect(rect, Color(1, 1, 1, 1))
	elif _buf.get_mode() == Buf.Mode.Normal:
		var rect: Rect2 = Rect2(caret_pos, normal_cursor_size)
		draw_rect(rect, Color(1, 1, 1, 0.5))

func _get_caret_pos() -> Vector2:
	var caret_line = _get_caret_line().substr(0, _caret.x)
	var caret_line_x = line_number_right_margin
	for c in caret_line:
		if c == "\t":
			caret_line_x += _font.get_char_size(" ".unicode_at(0), _font_size).x * tab_graphic.length()
			continue
		caret_line_x += _font.get_char_size(c.unicode_at(0), _font_size).x
	# var caret_line_x = \
	# 	line_number_right_margin \
	# 	+ _font.get_string_size(
	# 		caret_line.replace("\t", tab_graphic).substr(0, _caret.x),
	# 		HORIZONTAL_ALIGNMENT_LEFT,
	# 		-1,
	# 		_font_size
	# 	).x
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
	for line in _buf.content_str:
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
			Color(1, 1, 1, 0.2511)
		)
		line_y_poses.append(pos.y)
		pos.x = line_number_right_margin
		var line_to_draw = line.replace("\t", tab_graphic)
		draw_string(_font, pos, line_to_draw, HORIZONTAL_ALIGNMENT_CENTER, -1, _font_size)

		var line_size = line.length()
		if lineno < _buf.content_str.size():
			# Count+Write newline sign
			_buf.content_str[lineno - 1] += "\n"
			line_size += 1
		line_sizes.append(line_size)

		pos.y += line_spacing
		lineno += 1

	_draw_cursor()

# Write at current caret position.
func _write(c: String):
	assert(c.length() <= 1)
	if c == "":
		return

	if indent_mode == IndentMode.Space:
		c = c.replace("\t", tab_graphic)

	if c == "\n":
		var remaining = _buf.content_str[_caret.y].substr(_caret.x)
		_buf.content_str[_caret.y] = _buf.content_str[_caret.y].substr(0, _caret.x)
		_buf.content_str.append(remaining)
		_move_caret(0, 1)
		_caret.x = 0
	else:
		_set_caret_line(_buf.content_str[_caret.y].insert(_caret.x, c))
		_move_caret(c.length(), 0)
	queue_redraw()

func _get_caret_line() -> String:
	return _buf.content_str[_caret.y]

func _set_caret_line(s: String):
	_buf.content_str[_caret.y] = s

func _erase_left_char():
	if _caret == Vector2i.ZERO:
		return

	if _get_caret_line().length() == 0:
		_buf.content_str.remove_at(_caret.y)
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

func _toggle_append():
	_move_caret(1, 0)
	_buf.set_mode(Buf.Mode.Insert)
	queue_redraw()

func _append_line():
	_buf.content_str.insert(_caret.y + 1, "")
	_move_caret(0, 1)
	_buf.set_mode(Buf.Mode.Insert)
	queue_redraw()

func _prepend_line():
	_buf.content_str.insert(_caret.y, "")
	_move_caret(0, -1)
	_buf.set_mode(Buf.Mode.Insert)
	queue_redraw()

# Move display by pixels.
func _move_display(v: Vector2):
	# TODO: Implement display movement
	pass

# `chars` can be negative to move to the left, otherwise move to the right.
func _move_display_horizontal_chars(chars: int):
	# TODO: Implement display movement
	pass

# `_buf.content_str` can be negative to move to the top, otherwise move to the bottom.
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

	if _caret.y > _buf.content_str.size() - 1:
		_caret.y = _buf.content_str.size() - 1
	# If a caret moves to a new line, the X position will always be at the end,
	# if overflown
	if _caret.x > _buf.content_str[_caret.y].length():
		_caret.x = _buf.content_str[_caret.y].length()

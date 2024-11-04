extends Node


class Config:
	var _editor_processor_scene = preload("res://editor/editor.tscn")

	var layout: Inp.Layout = Inp.Layout.new()
	var editor: Editor.Config = Editor.Config.new()
	var buf_content_processor_scenes = {
		"_default": _editor_processor_scene,
	}

var config = Config.new()
var data_dir = "C:/Users/thed4/.sage"
var var_dir = data_dir.path_join("var")

# Opens file relative to var dir
func open_var(p: String, access: int) -> FileAccess:
	return FileAccess.open(var_dir.path_join(p), access)

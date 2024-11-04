extends Node

func get_ext(path: String) -> String:
	var parts = path.split(".")
	if parts.size() <= 1:
		return ""
	return parts[-1]

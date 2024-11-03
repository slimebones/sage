extends Node

const CODE_NOT_FOUND_ERR = "not_found_err"

class Err:
	var msg: String
	var code: StringName

	func _init(a_msg: String = "", a_code: StringName = ""):
		msg = a_msg
		code = a_code

func ee(v) -> bool:
	return v is Err

func err(msg: String = "", code: StringName = "") -> Err:
	return Err.new(msg, code)

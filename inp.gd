extends Node
class_name Inp

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
		"open_file": [KEY_SPACE, KEY_O],
		"write_file": [KEY_SPACE, KEY_W],
		"append": [KEY_A],
		"append_line": [KEY_O],
		"prepend_line": [Shifted.new(KEY_O)],
	}

	# Second symbol is shifted.
	var writables = {
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

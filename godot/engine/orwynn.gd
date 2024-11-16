extends Node

var _code_to_subs = {}
var _code_to_last_msg = {}

func _clear():
    _code_to_subs.clear()
    _code_to_last_msg.clear()

func _sub(code: String, fn: Callable) -> Callable:
    if !_code_to_subs.has(code):
        _code_to_subs[code] = []
    _code_to_subs[code].push_back(fn)
    if _code_to_last_msg.has(code):
        fn.call(_code_to_last_msg[code])
    return func unsub():
        if !_code_to_subs.has(code):
            return
        var i = _code_to_subs[code].find(fn)
        if i >= 0:
            _code_to_subs[code].remove_at(i)

# Pub can be available both at Bus and here since it's not required to be
# freed
func pub(code: String, msg = null):
    _code_to_last_msg[code] = msg
    if _code_to_subs.has(code):
        for sub_ in _code_to_subs[code]:
            sub_.call(msg)
    if code == "unload_scene":
        _clear()

func link() -> Bus:
    return Bus.new()

class Bus:
    var unsubs = []

    func sub(code: String, fn: Callable):
        unsubs.append(orwynn._sub(code, fn))

    func pub(code: String, msg = null):
        return orwynn.pub(code, msg)

    func unlink():
        for u in unsubs:
            u.call()

extends Node2D

signal scene_loaded
signal scene_unloaded

class Axis:
	var up: String
	var left: String
	var down: String
	var right: String

	func _init(up_: String, left_: String, down_: String, right_: String):
		up = up_
		left = left_
		down = down_
		right = right_

	func dir() -> Vector2:
		var r = Vector2.ZERO
		if Input.is_action_pressed(up):
			r.y -= 1
		if Input.is_action_pressed(down):
			r.y += 1
		if Input.is_action_pressed(left):
			r.x -= 1
		if Input.is_action_pressed(right):
			r.x += 1
		return r.normalized()

func median(arr: Array):
	var n = arr.size()
	if n % 2 == 0:
		return arr[round((n+1)/2.0)]
	else:
		return (arr[round(n/2.0)] + arr[round(n/2.0+1)]) / 2.0

class Ptr:
	var val
	func _init(val_):
		val = val_

class Rangei:
	var _min: int
	var _max: int

	func _init(min_: int, max_: int):
		_min = min_
		_max = max_

	func get_min() -> int:
		return _min

	func get_max() -> int:
		return _max

	func has(val: int) -> bool:
		return _min <= val && val <= _max

	## Both vector coords must be in range.
	func has_vec(vec: Vector2i) -> bool:
		return has(vec.x) && has(vec.y)

	## Clamp both vector coord in range [Vector2(min, min), Vector2(max, max)]
	func clamp_vec(vec: Vector2i) -> Vector2i:
		return vec.clamp(Vector2i(_min, _min), Vector2i(_max, _max))

class Rangef:
	var _min: float
	var _max: float

	func _init(min_: float, max_: float):
		_min = min_
		_max = max_

	func get_min() -> float:
		return _min

	func get_max() -> float:
		return _max

	func get_middle() -> float:
		return lerpf(_min, _max, 0.5)

	func has(val: float) -> bool:
		return _min <= val && val <= _max

	## Both vector coords must be in range.
	func has_vec(vec: Vector2) -> bool:
		return has(vec.x) && has(vec.y)

	## Clamp both vector coord in range [Vector2(min, min), Vector2(max, max)]
	func clamp_vec(vec: Vector2) -> Vector2:
		return vec.clamp(Vector2(_min, _min), Vector2(_max, _max))

class Rangev2:
	var _min: Vector2
	var _max: Vector2

	func _init(min_: Vector2, max_: Vector2):
		_min = min_
		_max = max_

	func get_min() -> Vector2:
		return _min

	func get_max() -> Vector2:
		return _max

	func get_middle() -> Vector2:
		return lerp(_min, _max, 0.5)

	func has(val: Vector2) -> bool:
		return _min <= val && val <= _max


func get_scene() -> Node:
	return get_tree().get_current_scene()

func add_to_scene(node: Node):
	get_scene().add_child(node)

# Fetches node relative to scene
func find(t: String = ".") -> Node:
	return get_tree().get_current_scene().get_node(t)

func time() -> int:
	return Time.get_ticks_msec()

func utc() -> int:
	return floor(Time.get_unix_time_from_system() * 1000)

func is_cooldown(
	last: int, cooldown: int, unlock_starters: bool = true
) -> bool:
	# By default make cooldowns unlocked at the start of the engine
	if unlock_starters && last == 0:
		return false
	return time() - last <= cooldown

func percent(current_val: float, max_val: float) -> float:
	return current_val / max_val

func get_viewport_mouse_pos() -> Vector2:
	return get_viewport().get_mouse_position()

func get_group_members(group: StringName) -> Array[Node]:
	return get_tree().get_nodes_in_group(group)

func debug(arr: Array):
	print(", ".join(arr))

func choose_first_non_empty(arrs: Array) -> Array:
	for arr in arrs:
		if len(arr) > 0:
			return arr
	printerr("All are empty")
	return []

func raycast(from: Vector2, to: Vector2) -> Dictionary:
	var state = get_world_2d().direct_space_state
	var q = PhysicsRayQueryParameters2D.create(from, to)
	return state.intersect_ray(q)

func find_if_null(val, node_name: StringName) -> Node:
	if val == null:
		return core.find(node_name)
	return val

func load_file_scene(path: String):
	scene_unloaded.emit()
	get_tree().change_scene_to_file(path)
	is_scene_load_msg_sent = false

func load_packed_scene(scene: PackedScene):
	scene_unloaded.emit()
	get_tree().change_scene_to_packed(scene)
	is_scene_load_msg_sent = false

func reload_scene():
	scene_unloaded.emit()
	get_tree().reload_current_scene()
	is_scene_load_msg_sent = false

func _ready():
	is_scene_load_msg_sent = true
	scene_loaded.emit.call_deferred()

var is_scene_load_msg_sent = false
var _scheduled_call_after = []

func call_after(ms: int, fn: Callable):
	_scheduled_call_after.append([core.time() + ms, fn])

func _process(_delta: float) -> void:
	# Signal scene load once available
	if !is_scene_load_msg_sent && get_scene() != null:
		is_scene_load_msg_sent = true
		scene_loaded.emit()

	var i = 0
	var i_to_del = []
	for pack in _scheduled_call_after:
		if pack[0] <= core.time():
			pack[1].call()
			i_to_del.append(i)
		i += 1
	for j in i_to_del:
		_scheduled_call_after.remove_at(j)

var _rnd_gen = RandomNumberGenerator.new()

# Randomly hit chance.
func chance(chance_val: float) -> bool:
	var rnd_val = _rnd_gen.randf_range(0, 1)
	return rnd_val <= chance_val

func pick_arr(a: Array):
	return a[_rnd_gen.randi_range(0, len(a)-1)]

func pick_arr_with_remove(a: Array):
	if len(a) == 0:
		assert(false, "Empty arr to pick from")
		return
	var i = _rnd_gen.randi_range(0, len(a)-1)
	var el = a[i]
	a.remove_at(i)
	return el

func pick_map(m: Dictionary):
	return m[m.keys()[_rnd_gen.randi_range(0, m.size()-1)]]

func pick_map_as_key(m: Dictionary) -> String:
	return m.keys()[_rnd_gen.randi_range(0, m.size()-1)]

func pick_rangei(rangei: core.Rangei) -> int:
	return _rnd_gen.randi_range(rangei.get_min(), rangei.get_max())

func pick_rangef(rangef: core.Rangef) -> float:
	return _rnd_gen.randf_range(rangef.get_min(), rangef.get_max())

func pick_int(min_: int, max_: int) -> int:
	return _rnd_gen.randi_range(min_, max_)

func pick_float(min_: float, max_: float) -> float:
	return _rnd_gen.randf_range(min_, max_)

# TODO: Make screenshots
# func _ready() -> void:
# 	var dir = DirAccess.open("user://")
# 	if not dir.dir_exists("user://screensh	ots"):
# 		dir.make_dir("screenshots")

# func _process(_delta: float) -> void:
# 	if Input.is_action_just_pressed("make_screenshot"):
# 		print("SHOOT")
# 		make_screenshot()

# func make_screenshot() -> void:
# 	await RenderingServer.frame_post_draw
# 	var viewport = get_viewport()
# 	var img = viewport.get_texture().get_image()
# 	var date = Time.get_datetime_dict_from_system()
# 	img.save_png("user://screenshots/screenshot_" + str(date["year"]) + str(date["month"]) \
# 	+ str(date["day"]) + str(date["hour"]) + str(date["minute"]) + str(date["second"]) + ".png")

# Must be directly set by the app or populated using load_atlas(...)
var size_to_atlas = {}

func load_atlas(a_size: Vector2, a_path: StringName):
	size_to_atlas[a_size] = load(a_path)

# This function does not touch sprite's texture, assuming it's already set
# correctly, but modifies sprite's region.
func atlas(a_sprite: Sprite2D, a_size: Vector2, loc: Vector2):
	a_sprite.region_enabled = true
	a_sprite.region_rect.position = a_size * loc

# Remap and clamp by the (b1, b2) values
func remap_clamp(
	v: float, a1: float, a2: float, b1: float, b2: float
) -> float:
	return clamp(
		remap(
			v,
			a1,
			a2,
			b1,
			b2
		),
		b1,
		b2
	)

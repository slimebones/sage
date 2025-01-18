set shell := ["nu", "-c"]

run *a:
	@ zig build run {{a}}

test *a:
	@ zig build test {{a}}
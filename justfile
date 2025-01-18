set shell := ["nu", "-c"]

run *a:
	@ zig run src/main.zig {{a}}
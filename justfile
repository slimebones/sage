set shell := ["nu", "-c"]

CC := "gcc"

SOURCE := "src/**/*.c lib/ini/ini.c lib/bone/bone.c"
INCLUDES := "-Isrc/include -Ilib/ini -Ilib/raylib/include -Ilib/bone/include"
LIB := "-lgdi32 -lwinmm -Llib -l:raylib/lib/raylib.dll"

run *a: compile
	@ ./bin/main

compile: compile_plugins
	@ mkdir bin
	@ {{CC}} {{INCLUDES}} {{LIB}} -o bin/main {{SOURCE}}
	@ cp lib/raylib/lib/raylib.dll bin/

compile_plugins:
	@ cd plugins/editor; just compile
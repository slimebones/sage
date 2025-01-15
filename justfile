set shell := ["nu", "-c"]

CC := "gcc"

SOURCE := "src/**/*.c lib/ini/ini.c"
INCLUDES := "-Ilib/raylib/include -Isrc/buffer -Ilib/ini"
LIB := "-Llib -l:raylib/raylib.dll -lgdi32 -lwinmm"

run *a: compile
	@ ./bin/main

compile:
	@ {{CC}} {{INCLUDES}} {{LIB}} -o bin/main {{SOURCE}}
	@ cp lib/raylib/raylib.dll bin/

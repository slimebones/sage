set shell := ["nu", "-c"]

CC := "gcc"

SOURCE := "src/**/*.c lib/ini/ini.c"
INCLUDES := "-Isrc/buffer -Isrc/plugin -Ilib/ini -Ilib/raylib/include"
LIB := "-Llib -l:raylib/lib/raylib.dll -lgdi32 -lwinmm"

run *a: compile
	@ ./bin/main

compile:
	@ {{CC}} {{INCLUDES}} {{LIB}} -o bin/main {{SOURCE}}
	@ cp lib/raylib/lib/raylib.dll bin/

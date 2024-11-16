set shell := ["nu", "-c"]

SOURCES := "main.c buffer/buffer.c editor/editor.c utils/utils.c"
INCLUDES := "-Ilib/raylib/include -Iutils -Ibuffer -Ieditor"
LIBS := "-Llib -l:raylib/lib/raylib.dll -lgdi32 -lwinmm"

run: compile
    @ ./bin/main

compile:
    @ mkdir bin
    @ gcc {{INCLUDES}} {{LIBS}} -o bin/main {{SOURCES}}
    @ cp lib/raylib/lib/raylib.dll bin/raylib.dll

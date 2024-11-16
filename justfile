set shell := ["nu", "-c"]

run: compile
    @ ./bin/main

compile:
    @ mkdir bin
    @ gcc -Ilib/raylib/include -Llib -l:raylib/lib/raylib.dll -lgdi32 -lwinmm -o bin/main main.c
    @ cp lib/raylib/lib/raylib.dll bin/raylib.dll

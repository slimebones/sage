set shell := ["nu", "-c"]

run: compile
    @ ./zig-out/bin/sage

compile:
    @ zig build

test:
    @ zig build test

serve_docs:
    @ mkdocs serve

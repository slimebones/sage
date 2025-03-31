set shell := ["nu", "-c"]

run: build
	@ ./build/Debug/sage.exe

build:
	@ mkdir build; cd build; cmake ..; cmake --build .

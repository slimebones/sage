set shell := ["nu", "-c"]

run *a: build
	@ ./build/Debug/main.exe

build:
	@ mkdir build
	@ cd build; cmake ..; cmake --build .

clean_run: clean_build
	@ ./build/Debug/main.exe

clean_build:
	@ rm -rf build
	@ mkdir build
	@ cd build; cmake ..; cmake --build .
set shell := ["nu", "-c"]

export CC = "gcc"

run *a: compile
	./bin/main

compile:
	@ echo $env.CC

set shell := ["nu", "-c"]

run: compile
    @ ./bin/sage

compile:
    @ rm -rf bin
    @ mkdir bin
    @ CGO_ENABLED=0 go build -o bin/sage ./src/main.go

test t="":
    @ if "{{t}}" == "" { go test ./... } else { go test ./{{t}} }

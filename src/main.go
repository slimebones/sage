package main

import (
	"sage/lib/bone"

	rl "github.com/gen2brain/raylib-go/raylib"
)

func main() {
	bone.Init(bone.InitArgs{
		Appname: "sage",
	})

	rl.InitWindow(800, 600, "Sage")
	defer rl.CloseWindow()

	rl.SetTargetFPS(60)
	for !rl.WindowShouldClose() {
		rl.BeginDrawing()
		rl.ClearBackground(rl.Black)
		rl.DrawText("Hello, world!", 200, 200, 20, rl.White)
		rl.EndDrawing()
	}
}

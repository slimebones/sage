package core

import (
	"sage/lib/bone"

	rl "github.com/gen2brain/raylib-go/raylib"
)

var font rl.Font

func Init() {
	rl.SetTraceLogLevel(rl.LogWarning)
	initResources()
	initWindow()
	startLoop()
}

func initResources() {
	font = rl.LoadFont(bone.Cwd("res/inconsolata/variable.ttf"))
}

func initWindow() {
	rl.SetConfigFlags(rl.FlagWindowResizable | rl.FlagBorderlessWindowedMode)
	rl.InitWindow(800, 600, "Sage")
}

func startLoop() {
	rl.SetTargetFPS(15)
	for !rl.WindowShouldClose() {
		loop()
	}
	rl.CloseWindow()
}

func loop() {
	rl.BeginDrawing()
	rl.ClearBackground(rl.Black)
	rl.DrawTextEx(font, "Hello, world!", rl.Vector2{X: 200, Y: 200}, 40, 4, rl.White)
	rl.EndDrawing()
}

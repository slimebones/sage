package core

import rl "github.com/gen2brain/raylib-go/raylib"

func Init() {
	initWindow()
	startLoop()
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
	rl.DrawText("Hello, world!", 200, 200, 20, rl.White)
	rl.EndDrawing()
}

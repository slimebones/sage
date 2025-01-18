const rl = @cImport(@cInclude("raylib.h"));
const bone = @import("bone/bone.zig");

pub fn main() void {
	bone.log_error("Hello {s}!", .{"Mark"});

	rl.SetTraceLogLevel(rl.LOG_WARNING);
	rl.SetConfigFlags(rl.FLAG_WINDOW_RESIZABLE);
	rl.InitWindow(800, 600, "Sage");
	rl.SetTargetFPS(15);

	const icon = rl.LoadImage("res/icon.png");
	rl.SetWindowIcon(icon);

	defer rl.UnloadImage(icon);
	defer rl.CloseWindow();

	while (!rl.WindowShouldClose()) {
		rl.BeginDrawing();
		defer rl.EndDrawing();

		rl.ClearBackground(rl.BLACK);

		rl.DrawText("Hello World!", 100, 100, 20, rl.YELLOW);
	}
}
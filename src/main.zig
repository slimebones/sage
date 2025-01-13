const std = @import("std");
const rl = @import("raylib");

pub fn main() !void {
    const width = 800;
    const height = 600;

    rl.initWindow(width, height, "Sage");
    defer rl.closeWindow();
    rl.setTargetFPS(60);

    while (!rl.windowShouldClose()) {
        rl.beginDrawing();
        defer rl.endDrawing();
        rl.clearBackground(rl.Color.white);
        rl.drawText("Hello, world!", 190, 200, 20, rl.Color.light_gray);
    }
}

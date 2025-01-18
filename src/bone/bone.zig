const std = @import("std");

pub fn log(comptime fmt: []const u8, args: anytype) void {
	std.debug.print(fmt, args);
	std.debug.print("\n", .{});
}

pub fn log_error(comptime fmt: []const u8, args: anytype) void {
	std.debug.print("\x1b[31mERROR\x1b[0m: ", .{});
	std.debug.print(fmt, args);
	std.debug.print("\n", .{});
}
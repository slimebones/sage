const std = @import("std");
const ini = @import("ini");

pub fn log(comptime fmt: []const u8, args: anytype) void {
	std.debug.print(fmt, args);
	std.debug.print("\n", .{});
}

pub fn log_error(comptime fmt: []const u8, args: anytype) void {
	std.debug.print("\x1b[31mERROR\x1b[0m: ", .{});
	std.debug.print(fmt, args);
	std.debug.print("\n", .{});
}

var _cwd: []u8 = "";
var _vardir: []const u8 = "var";

pub fn cwd() []u8 {
}

pub fn vardir(allocator: std.mem.Allocator, path: []const u8) ![]const u8 {
	var all_together: [512]u8 = undefined;
	const all_together_slice = all_together[0..];
	const s = try std.fmt.bufPrint(all_together_slice, "{s}/{s}", .{ _vardir, path });
	const r = try allocator.alloc(u8, s.len);
	std.mem.copyForwards(u8, r, s);
	return r;
}

pub fn init() !void {
	_cwd = try std.process.getCwdAlloc(std.heap.page_allocator);

	var all_together: [512]u8 = undefined;
	const all_together_slice = all_together[0..];
	_vardir = try std.fmt.bufPrint(all_together_slice, "{s}/{s}", .{ _cwd, "var" });

	const out = try vardir(std.heap.page_allocator, "app.cfg");
	log("{s}", .{out});
}
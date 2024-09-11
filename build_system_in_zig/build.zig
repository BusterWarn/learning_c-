const std = @import("std");
const fs = std.fs;
const mem = std.mem;
const ArrayList = std.ArrayList;
const StringHashMap = std.StringHashMap;

const REPO_ROOT = "src";

const SwuInfo = struct {
    name: []const u8,
    source_files: ArrayList([]const u8),
    include_paths: ArrayList([]const u8),
    dependencies: ArrayList([]const u8),
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    var swu_map = try discoverAndProcessSwus(b);
    defer cleanupSwuMap(&swu_map);

    const exe = try createExecutable(b, target, optimize, &swu_map);

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "Run the application");
    run_step.dependOn(&run_cmd.step);

    try generateCompileCommands(swu_map);
}

fn discoverAndProcessSwus(b: *std.Build) !StringHashMap(SwuInfo) {
    var swu_map = StringHashMap(SwuInfo).init(b.allocator);
    try discoverSwus(b, REPO_ROOT, &swu_map);
    try processIncludeFiles(b, &swu_map);
    return swu_map;
}

fn cleanupSwuMap(swu_map: *StringHashMap(SwuInfo)) void {
    var it = swu_map.iterator();
    while (it.next()) |entry| {
        entry.value_ptr.source_files.deinit();
        entry.value_ptr.include_paths.deinit();
        entry.value_ptr.dependencies.deinit();
    }
    swu_map.deinit();
}

fn createExecutable(b: *std.Build, target: std.zig.CrossTarget, optimize: std.builtin.OptimizeMode, swu_map: *StringHashMap(SwuInfo)) !*std.Build.Step.Compile {
    const exe = b.addExecutable(.{
        .name = "cpp_project",
        .target = target,
        .optimize = optimize,
    });

    const cpp_args = [_][]const u8{"-std=c++17"};

    // Add main.cc to the executable
    const main_path = try fs.path.join(b.allocator, &[_][]const u8{ REPO_ROOT, "main.cc" });
    exe.addCSourceFile(.{
        .file = .{ .path = main_path },
        .flags = &cpp_args,
    });

    var it = swu_map.iterator();
    while (it.next()) |entry| {
        const swu = entry.value_ptr;
        try addSwuToExecutable(b, exe, swu, &cpp_args);
    }

    exe.linkLibCpp();

    return exe;
}

fn addSwuToExecutable(b: *std.Build, exe: *std.Build.Step.Compile, swu: *SwuInfo, cpp_args: []const []const u8) !void {
    for (swu.source_files.items) |file| {
        exe.addCSourceFile(.{
            .file = .{ .path = file },
            .flags = cpp_args,
        });
    }

    // Add SwU-specific include paths
    const export_path = try std.fs.path.join(b.allocator, &[_][]const u8{ REPO_ROOT, "swu", swu.name, "export" });
    const inc_path = try std.fs.path.join(b.allocator, &[_][]const u8{ REPO_ROOT, "swu", swu.name, "inc" });
    exe.addIncludePath(.{ .path = export_path });
    exe.addIncludePath(.{ .path = inc_path });

    // Add global include path
    exe.addIncludePath(.{ .path = REPO_ROOT });

    for (swu.include_paths.items) |path| {
        const full_path = try std.fs.path.join(b.allocator, &[_][]const u8{ REPO_ROOT, path });
        exe.addIncludePath(.{ .path = full_path });
    }
}

fn discoverSwus(b: *std.Build, path: []const u8, swu_map: *StringHashMap(SwuInfo)) !void {
    var dir = try fs.cwd().openIterableDir(path, .{});
    defer dir.close();

    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    while (try walker.next()) |entry| {
        if (entry.kind == .file) {
            if (mem.endsWith(u8, entry.path, ".cc") or mem.endsWith(u8, entry.path, ".cpp")) {
                const swu_name = extractSwuName(b.allocator, entry.path) catch |err| switch (err) {
                    error.SwuNameNotFound => continue,
                    else => return err,
                };
                var swu = try swu_map.getOrPut(swu_name);
                if (!swu.found_existing) {
                    swu.value_ptr.* = SwuInfo{
                        .name = swu_name,
                        .source_files = ArrayList([]const u8).init(b.allocator),
                        .include_paths = ArrayList([]const u8).init(b.allocator),
                        .dependencies = ArrayList([]const u8).init(b.allocator),
                    };
                    std.debug.print("Discovered SwU: {s}\n", .{swu_name});
                }
                try swu.value_ptr.source_files.append(try fs.path.join(b.allocator, &[_][]const u8{ path, entry.path }));
            }
        } else if (entry.kind == .directory) {
            try discoverSwus(b, try fs.path.join(b.allocator, &[_][]const u8{ path, entry.path }), swu_map);
        }
    }
}

fn extractSwuName(allocator: mem.Allocator, path: []const u8) ![]const u8 {
    var parts = mem.split(u8, path, fs.path.sep_str);
    var found_swu = false;
    while (parts.next()) |part| {
        if (found_swu) {
            return try allocator.dupe(u8, part);
        }
        if (mem.eql(u8, part, "swu")) {
            found_swu = true;
        }
    }
    return error.SwuNameNotFound;
}

fn processIncludeFiles(b: *std.Build, swu_map: *StringHashMap(SwuInfo)) !void {
    var it = swu_map.iterator();
    while (it.next()) |entry| {
        const swu = entry.value_ptr;
        const include_path = try fs.path.join(b.allocator, &[_][]const u8{ REPO_ROOT, "swu", swu.name, "src", "include.zig" });

        std.debug.print("Attempting to read file: {s}\n", .{include_path});

        const file_contents = fs.cwd().readFileAlloc(b.allocator, include_path, 1024 * 1024) catch |err| {
            std.debug.print("Error reading file {s}: {s}\n", .{ include_path, @errorName(err) });
            if (err == error.FileNotFound) {
                std.debug.print("Skipping SwU {s} as include.zig was not found\n", .{swu.name});
                continue;
            }
            return err;
        };
        defer b.allocator.free(file_contents);

        try extractArrayContents(b, file_contents, "dependencies", &swu.dependencies);
        try extractArrayContents(b, file_contents, "includes", &swu.include_paths);
    }
}

fn extractArrayContents(b: *std.Build, file_contents: []const u8, array_name: []const u8, list: *ArrayList([]const u8)) !void {
    const array_decl = try std.fmt.allocPrint(b.allocator, "pub const {s} = ", .{array_name});
    defer b.allocator.free(array_decl);

    if (std.mem.indexOf(u8, file_contents, array_decl)) |start_index| {
        const array_content = file_contents[start_index + array_decl.len ..];
        const end_index = std.mem.indexOf(u8, array_content, ";") orelse return error.MalformedIncludeFile;

        var it = std.mem.split(u8, array_content[0..end_index], ",");
        while (it.next()) |item| {
            const trimmed = std.mem.trim(u8, item, &std.ascii.whitespace);
            if (trimmed.len > 2 and trimmed[0] == '"' and trimmed[trimmed.len - 1] == '"') {
                const cleaned = trimmed[1 .. trimmed.len - 1];
                try list.append(try b.allocator.dupe(u8, cleaned));
            }
        }
    }
}

fn generateCompileCommands(swu_map: StringHashMap(SwuInfo)) !void {
    var file = try std.fs.cwd().createFile("compile_commands.json", .{});
    defer file.close();

    var writer = file.writer();

    try writer.writeAll("[\n");

    // Add main.cc
    try writer.writeAll("  {\n");
    try writer.print("    \"directory\": \".\",\n", .{});
    try writer.print("    \"file\": \"{s}/main.cc\",\n", .{REPO_ROOT});
    try writer.writeAll("    \"command\": \"clang++ -std=c++17 ");

    // Add all include paths for main.cc
    var it = swu_map.iterator();
    while (it.next()) |entry| {
        const swu = entry.value_ptr;
        try writer.print("-I{s}/swu/{s}/export -I{s}/swu/{s}/inc ", .{ REPO_ROOT, swu.name, REPO_ROOT, swu.name });
    }
    try writer.print("-I{s} {s}/main.cc\"\n  }}", .{ REPO_ROOT, REPO_ROOT });

    // Add SwU source files
    it = swu_map.iterator();
    var first = false; // Set to false since we've already added main.cc
    while (it.next()) |entry| {
        const swu = entry.value_ptr;
        for (swu.source_files.items) |source_file| {
            if (!first) {
                try writer.writeAll(",\n");
            }
            first = false;

            try writer.writeAll("  {\n");
            try writer.print("    \"directory\": \".\",\n", .{});
            try writer.print("    \"file\": \"{s}\",\n", .{source_file});
            try writer.writeAll("    \"command\": \"clang++ -std=c++17 ");

            // Add all include paths for this SwU
            var swu_it = swu_map.iterator();
            while (swu_it.next()) |swu_entry| {
                const other_swu = swu_entry.value_ptr;
                try writer.print("-I{s}/swu/{s}/export ", .{ REPO_ROOT, other_swu.name });
                if (std.mem.eql(u8, swu.name, other_swu.name)) {
                    try writer.print("-I{s}/swu/{s}/inc ", .{ REPO_ROOT, other_swu.name });
                }
            }
            try writer.print("-I{s} {s}\"\n  }}", .{ REPO_ROOT, source_file });
        }
    }

    try writer.writeAll("\n]\n");
}

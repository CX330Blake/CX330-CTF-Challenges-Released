const std = @import("std");
const exit = std.process.exit;
const ALLOWED_MS = 100;
const POLLIN = 0x001;

// Terminal control constants
const TCGETS = 0x5401;
const TCSETS = 0x5402;
const ICANON = 0x00000002;
const ECHO = 0x00000008;

const stdout = std.io.getStdOut().writer();
const stdin = std.io.getStdIn();
const allocator = std.heap.page_allocator;

const termios = extern struct {
    c_iflag: u32,
    c_oflag: u32,
    c_cflag: u32,
    c_lflag: u32,
    c_line: u8,
    c_cc: [32]u8,
    c_ispeed: u32,
    c_ospeed: u32,
};

const Weapons = enum {
    Rapier,
    Katana,
    Revolver,
};

// Global variable to store original terminal settings
var orig_termios: termios = undefined;

fn readFlag() ![]u8 {
    const flag_file = try std.fs.cwd().openFile("flag.txt", .{});
    defer flag_file.close();

    const flag = try flag_file.readToEndAlloc(allocator, 10_000); // 最多讀取 10KB
    return flag; // Don't free here, return it to caller
}

fn printIntro() !void {
    try stdout.print(
        \\=============== DUEL ===============
        \\Dueling was a ritualized combat to defend honor in Europe and America (16th–19th c.).
        \\Europeans used rapiers or smallswords; Americans later used pistols or revolvers.
        \\Duels followed strict codes but often ended fatally.
        \\====================================
        \\
    , .{});
}

fn chooseWeapon() !Weapons {
    try stdout.print("Welcome to Duel, please choose your weapon.\n", .{});
    try stdout.print("1. Rapier\n", .{});
    try stdout.print("2. Katana\n", .{});
    try stdout.print("> ", .{});

    // Read a line instead of just a byte to consume the newline
    var buf: [10]u8 = undefined;
    if (try stdin.reader().readUntilDelimiterOrEof(buf[0..], '\n')) |input| {
        if (input.len > 0) {
            const choice = input[0];
            switch (choice) {
                '1' => return Weapons.Rapier,
                '2' => return Weapons.Katana,
                '7' => return Weapons.Revolver,
                else => {
                    try stdout.print("You chose an invalid option...bad hacker...\n", .{});
                    exit(1);
                },
            }
        }
    }

    try stdout.print("You chose an invalid option...bad hacker...\n", .{});
    exit(1);
}

fn setRawMode() !void {
    // Save original terminal settings
    _ = std.os.linux.syscall3(.ioctl, @as(usize, @bitCast(@as(isize, stdin.handle))), TCGETS, @intFromPtr(&orig_termios));

    // Set terminal to raw mode
    var raw_termios = orig_termios;
    raw_termios.c_lflag &= ~@as(u32, ICANON | ECHO);
    _ = std.os.linux.syscall3(.ioctl, @as(usize, @bitCast(@as(isize, stdin.handle))), TCSETS, @intFromPtr(&raw_termios));
}

fn restoreTerminal() void {
    // Restore original terminal settings
    _ = std.os.linux.syscall3(.ioctl, @as(usize, @bitCast(@as(isize, stdin.handle))), TCSETS, @intFromPtr(&orig_termios));
}

fn duel(weapon: Weapons, flag: []u8) !void {
    switch (weapon) {
        .Rapier => {
            try stdout.print("You chose the Rapier! A weapon of legends and gentlemen...\n", .{});
        },
        .Katana => {
            try stdout.print("You chose the Katana! A weapon of ninjas and Samurai...\n", .{});
        },
        .Revolver => {
            try stdout.print("You chose the Revolver! A HIDDEN weapon of NEW ERA...\n", .{});
        },
    }

    // Generate random wait time between 1-20 seconds
    var prng = std.Random.DefaultPrng.init(blk: {
        var seed: u64 = undefined;
        try std.posix.getrandom(std.mem.asBytes(&seed));
        break :blk seed;
    });
    const rand = prng.random();
    const wait_seconds = rand.intRangeAtMost(u8, 1, 20);

    try stdout.print("Ready...\n", .{});
    try stdout.print("Wait for the signal...\n", .{});

    // Set terminal to raw mode for immediate input BEFORE the wait period
    try setRawMode();
    // Ensure terminal is restored when this function exits
    defer restoreTerminal();

    // Check for any premature input during the wait period
    var fds = [_]std.os.linux.pollfd{
        .{
            .fd = stdin.handle,
            .events = POLLIN,
            .revents = 0,
        },
    };

    var wait_elapsed: u64 = 0;
    const wait_ms = @as(u64, wait_seconds) * 1000;

    while (wait_elapsed < wait_ms) {
        const nready = std.os.linux.poll(&fds, 1, 100); // 100ms timeout
        if (nready > 0 and (fds[0].revents & POLLIN) != 0) {
            // Someone pressed something during the wait period
            const premature_key = try stdin.reader().readByte();
            if (premature_key == '\n') {
                try stdout.print("\nYou pressed enter too early! Cheating is not allowed...bad hacker\n", .{});
                return;
            }
            // Ignore other keys during wait period
        }
        wait_elapsed += 100;
    }

    try stdout.print("Start!\n", .{});

    const start_time = std.time.milliTimestamp();

    var buf: u8 = undefined;
    while (true) {
        const current_time = std.time.milliTimestamp();
        const elapsed = current_time - start_time;

        // Check for input with short timeout
        const nready = std.os.linux.poll(&fds, 1, 50); // 50ms timeout
        if (nready > 0 and (fds[0].revents & POLLIN) != 0) {
            buf = try stdin.reader().readByte();
            if (buf == ' ') {
                const press_time = std.time.milliTimestamp();
                const delta = press_time - start_time;

                // Check if timing is within allowed range (100ms)
                if (delta <= ALLOWED_MS) {
                    // Different logic based on weapon choice
                    switch (weapon) {
                        // Lose
                        .Rapier => {
                            try stdout.print("\nYour rapier strikes through the air, but it's too slow! The enemy's bullet finds its mark first.\n", .{});
                        },
                        .Katana => {
                            try stdout.print("\nYour katana strikes through the air, but it's too slow! The enemy's bullet finds its mark first.\n", .{});
                        },
                        // Revolver can win with good timing
                        .Revolver => {
                            try stdout.print("\nPerfect shot! Your revolver fires true!\n", .{});
                            try stdout.print("Reaction time: {d} ms\n", .{delta});
                            try stdout.print("Flag: {s}\n", .{flag});
                        },
                    }
                } else {
                    try stdout.print("\nToo slow! Bad hacker...", .{});
                }
                break;
            } else {
                try stdout.print("\nYou didn't press the enter...bad hacker\n", .{});
                break;
            }
        }

        // Timeout after 5 seconds of waiting for input
        if (elapsed > ALLOWED_MS) {
            try stdout.print("Bang! You're too slow, so you got shot by the enemy before you moved...bad hacker\n", .{});
            break;
        }
    }
}

pub fn main() !void {
    const flag = try readFlag();
    defer allocator.free(flag);

    try printIntro();
    const weapon = try chooseWeapon();
    try duel(weapon, flag);
}

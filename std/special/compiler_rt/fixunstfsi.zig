const fixuint = @import("fixuint.zig").fixuint;

export fn __fixunstfsi(a: f128) -> u32 {
    @setGlobalLinkage(__fixunstfsi, @import("builtin").GlobalLinkage.LinkOnce);
    return fixuint(f128, u32, a);
}

test "import fixunstfsi" {
    _ = @import("fixunstfsi_test.zig");
}

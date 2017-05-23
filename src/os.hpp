/*
 * Copyright (c) 2015 Andrew Kelley
 *
 * This file is part of zig, which is MIT licensed.
 * See http://opensource.org/licenses/MIT
 */

#ifndef ZIG_OS_HPP
#define ZIG_OS_HPP

#include "list.hpp"
#include "buffer.hpp"
#include "error.hpp"

#include <stdio.h>

enum TerminationId {
    TerminationIdClean,
    TerminationIdSignaled,
    TerminationIdStopped,
    TerminationIdUnknown,
};

struct Termination {
    TerminationId how;
    int code;
};


void os_init(void);
void os_spawn_process(const char *exe, ZigList<const char *> &args, Termination *term);
int os_exec_process(const char *exe, ZigList<const char *> &args,
        Termination *term, Buf *out_stderr, Buf *out_stdout);

void os_path_dirname(Buf *full_path, Buf *out_dirname);
void os_path_split(Buf *full_path, Buf *out_dirname, Buf *out_basename);
void os_path_extname(Buf *full_path, Buf *out_basename, Buf *out_extname);
void os_path_join(Buf *dirname, Buf *basename, Buf *out_full_path);
int os_path_real(Buf *rel_path, Buf *out_abs_path);
void os_path_resolve(Buf *ref_path, Buf *target_path, Buf *out_abs_path);
bool os_path_is_absolute(Buf *path);

int os_make_path(Buf *path);
int os_make_dir(Buf *path);

void os_write_file(Buf *full_path, Buf *contents);
int os_copy_file(Buf *src_path, Buf *dest_path);

int os_fetch_file(FILE *file, Buf *out_contents);
int os_fetch_file_path(Buf *full_path, Buf *out_contents);

int os_get_cwd(Buf *out_cwd);

bool os_stderr_tty(void);

int os_buf_to_tmp_file(Buf *contents, Buf *suffix, Buf *out_tmp_path);
int os_delete_file(Buf *path);

int os_file_exists(Buf *full_path, bool *result);

int os_rename(Buf *src_path, Buf *dest_path);
double os_get_time(void);

bool os_is_sep(uint8_t c);

#if defined(__APPLE__)
#define ZIG_OS_DARWIN
#elif defined(_WIN32)
#define ZIG_OS_WINDOWS
#elif defined(__linux__)
#define ZIG_OS_LINUX
#else
#define ZIG_OS_UNKNOWN
#endif

#if defined(__x86_64__)
#define ZIG_ARCH_X86_64
#else
#define ZIG_ARCH_UNKNOWN
#endif

#if defined(ZIG_OS_WINDOWS)
#define ZIG_PRI_usize "Iu"
#define ZIG_PRI_u64 "I64u"
#define ZIG_PRI_llu "I64u"
#define ZIG_PRI_x64 "I64x"
#else
#define ZIG_PRI_usize "zu"
#define ZIG_PRI_u64 PRIu64
#define ZIG_PRI_llu "llu"
#define ZIG_PRI_x64 PRIx64
#endif

#endif

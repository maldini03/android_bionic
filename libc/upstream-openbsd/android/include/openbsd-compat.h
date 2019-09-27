/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _BIONIC_OPENBSD_COMPAT_H_included
#define _BIONIC_OPENBSD_COMPAT_H_included

#define _BSD_SOURCE
#include <sys/cdefs.h>

#include <stddef.h> // For size_t.

// TODO: libandroid_support uses this file, so we need to wait for
// <sys/random.h> to be in the NDK headers before we can lose this declaration.
//#include <sys/random.h> // For getentropy.
int getentropy(void*, size_t);

#define __BEGIN_HIDDEN_DECLS _Pragma("GCC visibility push(hidden)")
#define __END_HIDDEN_DECLS _Pragma("GCC visibility pop")

extern const char* __progname;

/* Redirect internal C library calls to the public function. */
#define _err err
#define _errx errx
#define _verr verr
#define _verrx verrx
#define _vwarn vwarn
#define _vwarnx vwarnx
#define _warn warn
#define _warnx warnx

/* Ignore all DEF_STRONG/DEF_WEAK in OpenBSD. */
#define DEF_STRONG(sym)
#define DEF_WEAK(sym)
#define __weak_alias __strong_alias

/* Ignore all __warn_references in OpenBSD. */
#define __warn_references(sym,msg)

/* OpenBSD's <ctype.h> uses these names, which conflicted with stlport.
 * Additionally, we changed the numeric/digit type from N to D for libcxx.
 */
#define _U _CTYPE_U
#define _L _CTYPE_L
#define _N _CTYPE_D
#define _S _CTYPE_S
#define _P _CTYPE_P
#define _C _CTYPE_C
#define _X _CTYPE_X
#define _B _CTYPE_B

/* OpenBSD has this, but we can't really implement it correctly on Linux. */
#define issetugid() 0

#define explicit_bzero(p, s) memset(p, 0, s)

/* OpenBSD has these in <sys/param.h>, but "ALIGN" isn't something we want to reserve. */
#define ALIGNBYTES (sizeof(uintptr_t) - 1)
#define ALIGN(p) (((uintptr_t)(p) + ALIGNBYTES) &~ ALIGNBYTES)

/* OpenBSD has this in paths.h. But this directory doesn't normally exist.
 * Even when it does exist, only the 'shell' user has permissions.
 */
#define _PATH_TMP "/data/local/tmp/"

/* Use appropriate shell depending on process's executable. */
__LIBC_HIDDEN__ extern const char* __bionic_get_shell_path();
#define _PATH_BSHELL __bionic_get_shell_path()

__LIBC_HIDDEN__ extern char* __findenv(const char*, int, int*);
__LIBC_HIDDEN__ extern char* _mktemp(char*);

#endif

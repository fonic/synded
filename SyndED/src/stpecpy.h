/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - stpecpy, strtcpy                                       *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/19/25                                                 *
 *                                                                            *
 ******************************************************************************/

#ifndef STRECPY_H
#define STRECPY_H

// Needed for strnlen + stpcpy, affects '#include <string.h>'
#if defined(__GNUC__) && ! defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif

// Needed for mempcpy, affects '#include <stdio.h>'
#if defined(__GNUC__) && ! defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif

#include <stddef.h>     // size_t
#include <sys/types.h>  // ssize_t

char*   stpecpy(char *dst, const char *dstend, const char *restrict src);
ssize_t strtcpy(char *restrict dst, const char *restrict src, size_t dsize);

#endif // STRECPY_H

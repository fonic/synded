/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - asprintf, vasprintf, vscprintf                         *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/14/25                                                 *
 *                                                                            *
 ******************************************************************************/

#ifndef ASPRINTF_H
#define ASPRINTF_H

/* Needed for asprintf/vasprintf, affects '#include <stdio.h>' (GNU only) */
#if defined(__GNUC__) && ! defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif

#include <stdio.h>		// asprintf (GNU only), vasprintf (GNU only), _vscprintf (MSVC only), vsnprintf
#include <stdarg.h>		// va_list, va_copy, va_end

/*
 * vscprintf - determine number of characters in resulting formatted string
 *
 * MSVC already defines/implements this as '_vscprintf', thus we simply
 * symlink it here using a define
 *
 * GNU-C-compatible compilers do not implement this, thus we define it
 * here and implement it in 'asprintf.c'
 */
#ifdef _MSC_VER
#define vscprintf _vscprintf
#endif

#ifdef __GNUC__
int vscprintf(const char *fmt, va_list ap);
#endif

/*
 * asprintf, vasprintf - print to allocated string
 *
 * MSVC does not define/implement these, thus we define them here and
 * implement them in 'asprintf.c'
 *
 * GNU-C-compatible compilers define/implement these with the same names,
 * thus we don't have to do anything
 */
#ifdef _MSC_VER
int vasprintf(char **strp, const char *fmt, va_list ap);
int asprintf(char **strp, const char *fmt, ...);
#endif

#endif // ASPRINTF_H

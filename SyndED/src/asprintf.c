/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - asprintf, vasprintf, vscprintf                         *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/14/25                                                 *
 *                                                                            *
 ******************************************************************************/


/**************************************
 *                                    *
 *  Includes                          *
 *                                    *
 **************************************/

#include "asprintf.h"  // related header

#include <stdlib.h>    // malloc, free
#include <errno.h>     // errno, EINVAL


/**************************************
 *                                    *
 *  Functions                         *
 *                                    *
 **************************************/

#ifdef __GNUC__
/* Modeled after MSVC counterpart: */
/* https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vscprintf-vscprintf-l-vscwprintf-vscwprintf-l?view=vs-2019 */
int vscprintf(const char *fmt, va_list ap)
{
	if (fmt == NULL) {
		errno = EINVAL;
		return -1;
	}
	va_list ap_copy;
	va_copy(ap_copy, ap);
	int result = vsnprintf(NULL, 0, fmt, ap_copy);
	va_end(ap_copy);
	return (result < 0 ? -1 : result);
}
#endif

#ifdef _MSC_VER
/* Modeled after 'man 3 (v)asprintf', e.g.: */
/* http://man7.org/linux/man-pages/man3/asprintf.3.html */
int vasprintf(char **strp, const char *fmt, va_list ap)
{
	int len = vscprintf(fmt, ap);
	if (len == -1)
		return -1;
	char *str = (char*)malloc((size_t) len + 1);
	if (str == NULL)
		return -1;
	va_list ap_copy;
	va_copy(ap_copy, ap);
	int result = vsnprintf(str, len + 1, fmt, ap_copy);
	va_end(ap_copy);
	if (result == -1) {
		free(str);
		return -1;
	}
	*strp = str;
	return result;
}

int asprintf(char **strp, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int result = vasprintf(strp, fmt, ap);
	va_end(ap);
	return result;
}
#endif

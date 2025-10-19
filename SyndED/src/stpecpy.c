/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - stpecpy, strtcpy                                       *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/19/25                                                 *
 *                                                                            *
 ******************************************************************************/

#include "stpecpy.h"  // related header

#include <string.h>   // strnlen
#include <stdbool.h>  // bool
#include <errno.h>    // errno, ENOBUFS, E2BIG

// Reference implementation from 'man string_copying'
char* stpecpy(char *dst, const char *dstend, const char *restrict src) {
	ssize_t  dlen;

	if (dst == NULL)
		return NULL;

	dlen = strtcpy(dst, src, dstend - dst);
	return (dlen == -1) ? NULL : dst + dlen;
}

// Reference implementation from 'man string_copying'
ssize_t strtcpy(char *restrict dst, const char *restrict src, size_t dsize) {
	bool    trunc;
	size_t  dlen, slen;

	if (dsize == 0) {
		errno = ENOBUFS;
		return -1;
	}

	slen = strnlen(src, dsize);
	trunc = (slen == dsize);
	dlen = slen - trunc;

	stpcpy(mempcpy(dst, src, dlen), "");
	if (trunc)
		errno = E2BIG;
	return trunc ? -1 : (ssize_t)slen;
}

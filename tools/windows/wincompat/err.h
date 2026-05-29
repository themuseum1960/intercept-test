/* wincompat: BSD <err.h> shim for mingw.
 *
 * acarsdec/dumpvdl2 use err()/errx()/warn()/warnx(). mingw ships no <err.h>,
 * so this is the only header by that name on the include path. The helpers are
 * static + unused-attributed so each translation unit that includes this gets
 * its own copy without "defined but not used" warnings. Inert off-Windows.
 */
#ifndef WINCOMPAT_ERR_H
#define WINCOMPAT_ERR_H

#ifdef _WIN32
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void __attribute__((unused)) warnx(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "acarsdec: ");
	if (fmt)
		vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
}

static void __attribute__((unused)) warn(const char *fmt, ...)
{
	int e = errno;
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "acarsdec: ");
	if (fmt) {
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, ": ");
	}
	va_end(ap);
	fprintf(stderr, "%s\n", strerror(e));
}

static void __attribute__((unused, noreturn)) errx(int eval, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "acarsdec: ");
	if (fmt)
		vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(eval);
}

static void __attribute__((unused, noreturn)) err(int eval, const char *fmt, ...)
{
	int e = errno;
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "acarsdec: ");
	if (fmt) {
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, ": ");
	}
	va_end(ap);
	fprintf(stderr, "%s\n", strerror(e));
	exit(eval);
}
#endif /* _WIN32 */

#endif /* WINCOMPAT_ERR_H */

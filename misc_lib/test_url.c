/******************************************************************************
 *
 *    test_url.c
 *
 *    Test for parse_url in url.c. Added 2026.
 *
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "misc_lib.h"

static int fail;

static void
expect(const char *what, const char *got, const char *want)
{
	if (strcmp(got, want) != 0) {
		fprintf(stderr, "FAIL %s: got \"%s\" want \"%s\"\n",
			what, got, want);
		fail++;
	}
}

int
main(void)
{
	url u;

	/*
	 * Fill with a non-NUL pattern so a missing terminator on port
	 * shows up as a string other than "0".
	 */
	memset(&u, 'X', sizeof u);
	parse_url("http://example.com/index.html", &u);
	expect("service", u.service, "http");
	expect("server", u.server, "example.com");
	expect("port (no port in URL)", u.port, "0");
	expect("program", u.program, "index");
	expect("extension", u.extension, "html");

	memset(&u, 'X', sizeof u);
	parse_url("http://example.com:8080/index.html", &u);
	expect("port (explicit)", u.port, "8080");
	expect("server (with port)", u.server, "example.com");

	if (fail) {
		fprintf(stderr, "%d check(s) failed\n", fail);
		return 1;
	}
	printf("ok\n");
	return 0;
}

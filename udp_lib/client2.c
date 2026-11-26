/******************************************************************************
 *
 *    client2.c
 *
 *    A UDP protocol daytime service (port 13) client to test the udp_lib
 *
 *    Copyright (C) 2005  Chris Nystrom
 *
 *    This program is pulbic domain.
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 */

#include "udp_lib.h"

#define SIZE (1400)
#define TIME_PORT (13)
#define STDOUT  (1)
#define HOSTNAME_SIZE  (128)

int main(int argc, char *argv[])
{
	int nread;
	char hostname[HOSTNAME_SIZE];
	char buf[SIZE] = "";

	if (argc != 2) {
		fprintf(stderr, "usage: %s <hostname>\n", argv[0]);
		exit(1);
	}

	strncpy(hostname, argv[1], HOSTNAME_SIZE);

	init_udp_client(hostname, TIME_PORT);

	write_udp(buf, 1);

	nread = read_udp(buf, SIZE);

	if (nread > 0) {
		write(STDOUT, buf, nread);
	} else {
		fprintf(stderr, "client2: read error\n");
	}

	close_udp();

	exit(0);
}

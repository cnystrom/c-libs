/******************************************************************************
 *
 *    udp_lib.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lessor General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/lessor.html
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

PRIVATE int sockid;

PRIVATE struct sockaddr_in client_addr;
PRIVATE struct sockaddr_in server_addr;

PUBLIC int init_udp_server(int port)
{
//      printf("init_udp_server(): creating socket\n");

	if ((sockid = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "init_udp_server(): socket error: %d\n",
			errno);
		exit(-1);
	}
//      printf("init_udp_server(): binding to local socket\n");

	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port);

	if ((bind(sockid, (struct sockaddr *) &server_addr,
		  sizeof(server_addr)) < 0)) {
		fprintf(stderr, "init_udp_server(): bind failed: %d\n",
			errno);
		exit(-2);
	}

	return (0);
}

PUBLIC int init_udp_client(const char *hostname, int port)
{
	struct hostent *hp;

	hp = gethostbyname(hostname);

	if (hp == NULL) {
		return (-1);
	}

	printf("init_udp_client(): creating addr structure for server\n");

	bzero((char *) &server_addr, sizeof(server_addr));
	memcpy((char *) &server_addr.sin_addr, hp->h_addr, hp->h_length);
	server_addr.sin_family = hp->h_addrtype;
//      server_addr.sin_family = AF_INET;
//      server_addr.sin_addr.s_addr = inet_addr(address);
	server_addr.sin_port = htons(port);

	printf("init_udp_client(): creating socket\n");

	if ((sockid = socket(hp->h_addrtype, SOCK_DGRAM, 0)) < 0) {
//      if ((sockid = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "init_udp_client(): socket failed: %d\n",
			errno);
		return (-1);
	}

	printf("init_udp_client(): binding to local socket\n");

	bzero((char *) &client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	client_addr.sin_port = htons(0);

	if ((bind(sockid, (struct sockaddr *) &client_addr,
		  sizeof(client_addr)) < 0)) {
		fprintf(stderr, "init_udp_client(): bind failed: %d\n",
			errno);
		return (-2);
	}

	return (0);
}

PUBLIC int read_udp(char *msg, int len)
{
	int nread, addrlen;

	addrlen = sizeof(client_addr);

	printf("read_udp(): starting blocking message read\n");

	nread = recvfrom(sockid, msg, len, 0,
			 (struct sockaddr *) &client_addr, &addrlen);

	printf("read_udp(): return code from read is %d\n", nread);

	usleep(0);		// strangly this seems to help...

	return (nread);
}

PUBLIC int write_udp(const char *msg, int len)
{
	int retcode;

	printf("write_udp(): sending message\n");

	retcode =
	    sendto(sockid, msg, len, 0, (struct sockaddr *) &server_addr,
		   sizeof(server_addr));

	if (retcode <= -1) {
		fprintf(stderr, "write_udp(): sendto failed: %d\n", errno);
		return (-1);
	}

	return (retcode);
}

PUBLIC void close_udp(void)
{
	/* close socket */
	close(sockid);
}

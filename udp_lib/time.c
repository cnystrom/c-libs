
/* UDP client for time */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#ifndef PRIVATE
#define PRIVATE static
#endif

#ifndef PUBLIC
#define PUBLIC
#endif

PRIVATE int sockfd;

PRIVATE struct sockaddr_in serv_addr;
PRIVATE struct sockaddr_in client_addr;

PUBLIC int init_udp(const char *address, int port)
{
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror(NULL);
		return (-2);
	}

	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	client_addr.sin_port = htons(0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(address);
	serv_addr.sin_port = htons(port);

	if (bind(sockfd, &client_addr, sizeof(client_addr)) < 0) {
		perror(NULL);
		close(sockfd);
		return (-3);
	}
}

PUBLIC int write_udp(const char *buf, int len)
{
	int ret;

	ret = sendto(sockfd, buf, len, 0, &serv_addr, sizeof(serv_addr));

	return (ret);
}

PUBLIC int read_udp(char *buf, int max)
{
	int ret;
	int len;

	len = sizeof(client_addr);

	ret = recvfrom(sockfd, buf, max, 0, &client_addr, &len);

	return (ret);
}

PUBLIC void close_udp(void)
{
	close(sockfd);
}

#define SIZE (1400)
#define TIME_PORT (13)
#define STDOUT  (1)

int main(int argc, char *argv[])
{
	int nread;
	char address[16];
	char buf[SIZE] = "";

	if (argc != 2) {
		fprintf(stderr, "usage: %s IPaddr\n", argv[0]);
		exit(1);
	}

	strncpy(address, argv[1], 16);

	init_udp(address, TIME_PORT);

	write_udp(buf, 1);

	nread = read_udp(buf, SIZE);

	write(STDOUT, buf, nread);

	close_udp();

	exit(0);
}

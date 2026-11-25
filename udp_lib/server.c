
/* server.c */

#include "udp_lib.h"

#define PORT  (6090)
#define MAX_SIZE     (50)

int main()
{
	int ret;
	char message[MAX_SIZE];

	init_udp_server(PORT);

	ret = read_udp(message, MAX_SIZE);

	if (ret > 0) {
		printf("server: message is |%s|\n", message);
	} else {
		printf("server: error. nothing read\n");
	}

	close_udp();

	exit(0);
}

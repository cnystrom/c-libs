
/* client.c */

#include <string.h>
#include "udp_lib.h"

#define SERVER  "localhost"
#define PORT  (6090)

int main()
{
	int ret;
	char message[12] = "Hello world";

	init_udp_client(SERVER, PORT);

	ret = write_udp(message, (strlen(message) + 1));

	printf("client: %d bytes written\n", ret);

	close_udp();

	exit(0);
}

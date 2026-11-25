/*
 * server.c
 */

#include <stdio.h>
#include "new_rpc.h"
#include "example.h"

#define STR_LEN		(128)

int
main(void)
{
  char hostname[HOSTNAME_LEN];
  char welcome[STR_LEN];
  char str[] = "This is a test of a very long string!\n";

  gethostname(hostname, HOSTNAME_LEN);

  snprintf(welcome, STR_LEN, "NRPC Test Server 0.1 (%s)", hostname);

//  nrpc_init_server(PORTNUM);
  nrpc_init_server();

  nrpc_welcome(welcome);

  test_send_int(INT_MAX);

  test_send_int(INT_MIN);

  test_send_string(str);

  test_combo(3, "The is a test string.\n");

  nrpc_reverse();
  echo_data();

  nrpc_exit();
  nrpc_close();
  exit(0);
}


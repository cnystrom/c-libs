/*
 * server.c
 */

#include "example.h"
#include "rand.h"

void echo_data(void);

int
main(void)
{
  randomize();
  nrpc_init_server(PORTNUM);
  nrpc_welcome("New RPC Example Server 0.1 (CHANGEME)");
  echo_data();
  nrpc_close();
  exit(0);
}

void
echo_data(void)
{
  for (;;)
  {
    int func_num, ret;
    char str[MSG_MAX_LEN];

    func_num = nrpc_get_function();

    if (func_num == NRPC_EXIT)
    {
      printf("Exit command rcvd.\n");
      nrpc_close();
      exit(0);
    }
    if (func_num == NRPC_REVERSE)
    {
      int i;
      double d;

      printf("Reverse command rcvd.\n");
      printf("-------------------------------------------------------------\n");

      printf("Sending: This is another very, very long test!\n");
      send_string("This is another very, very long test!");
      printf("-------------------------------------------------------------\n");

      i = rand_int(1000);
      printf("Sending: %d\n", i);
      send_int(i);
      printf("-------------------------------------------------------------\n");

      d = rand_double();
      printf("Sending: %lf\n", d);
      send_double(d);
      printf("-------------------------------------------------------------\n");

      printf("Sending exit command.\n");

      nrpc_exit();
      nrpc_close();
      exit(0);
    }
    else if (func_num == SEND_STRING)
    {
      int i;

      msg_get_string(str);
      i = test_string(str);

      /* Send response */

      msg_reset();
      msg_put_int(i);
      nrpc_send_response();
    }
    else if (func_num == SEND_INT)
    {
      ret = msg_get_int();
      printf("RCVD INT = %d\n", ret);

      /* Send response */

      msg_reset();
      msg_put_int(1);
      msg_put_string("It worked!");
      nrpc_send_response();
    }
    else if (func_num == SEND_DOUBLE)
    {
      double dret;

      dret = msg_get_double();
      printf("RCVD DOUBLE = %lf\n", dret);

      /* Send response */

      msg_reset();
      msg_put_int(1);
      nrpc_send_response();
    }
    else
    {
      printf("bad function number = %d\n", func_num);
    }

    printf("-------------------------------------------------------------\n");

  }
}


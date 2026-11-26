/*
 * client.c
 */

#include "example.h"
#include "rand.h"

void echo_data(void);

int
main(void)
{
  int i;
  double d;

  randomize();
  nrpc_init_client("localhost", PORTNUM);

  printf("Sending: This is a very, very long test string!\n");
  send_string("This is a very, very long test string!");
  printf("-------------------------------------------------------------\n");

  i = rand_int(1000);
  printf("Sending: %d\n", i);
  send_int(i);
  printf("-------------------------------------------------------------\n");

  d = rand_double();
  printf("Sending: %lf\n", d);
  send_double(d);
  printf("-------------------------------------------------------------\n");

  printf("Reversing...\n");
  nrpc_reverse();
  printf("-------------------------------------------------------------\n");

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
    else if (func_num == SEND_STRING)
    {
      int i;

      msg_get_string(str);

      /* call function and send parameter back */

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
      /* Note: for this function the response is an int, and a string */

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
      /* Note: for this function the response is an int */

      msg_reset();
      msg_put_int(1);
      nrpc_send_response();
    }
    else
    {
      printf("bad function number = %d!\n", func_num);
    }

    printf("---------------------------------------------------------------\n");

  }
}


/*
 * example.c
 */

#include "example.h"

/* sends an int and gets an int and a string back */

int
send_int(int i)
{
  int ret_code;
  char ret_str[MSG_MAX_LEN];

  nrpc_set_function(SEND_INT);
  msg_put_int(i);
  nrpc_send_message();
  ret_code = msg_get_int();
  msg_get_string(ret_str);

#ifdef DEBUG
  printf("send_int() return code: %d\n", ret_code);
  printf("send_int() return string: %s\n", ret_str);
#endif

  return(ret_code);
}

/* sends a float and gets an int back */

int
send_double(double d)
{
  int ret_code;

  nrpc_set_function(SEND_DOUBLE);
  msg_put_double(d);
  nrpc_send_message();
  ret_code = msg_get_int();

#ifdef DEBUG
  printf("send_double() return code: %d\n", ret_code);
#endif

  return(ret_code);
}

/* sends string and gets an int back */

int
send_string(char *s)
{
  int i;

  nrpc_set_function(SEND_STRING);
  msg_put_string(s);
  nrpc_send_message();
  i = msg_get_int();

#ifdef DEBUG
  printf("send_string() return code: %d\n", i);
#endif

  return(i);
}

int
test_string(char *s)
{
  printf("String RCVD = %s\n", s);
  return(0);
}


/*
 * example.c
 */

#include <stdio.h>
#include "types.h"
#include "buffer.h"
#include "example.h"

void
echo_data(void)
{
  for (;;)
  {
    int i, func_num, ret;
//    char str[MSG_MAX_LEN];

    func_num = nrpc_get_function();

    if (func_num == NRPC_EXIT) {
      nrpc_close();
      exit(0);
    }
    if (func_num == NRPC_REVERSE) {
      test_send_int(512);
      test_send_string("This test is another very long string!");

      nrpc_exit();
      nrpc_close();
      exit(0);
    }
    else if (func_num == SEND_INT) {
      ret = unpack_int32();
      nrpc_std_response();
    }
    else if (func_num == SEND_STR) {
      char str[BUF_SIZE];

      unpack_string(str);
      i = test_string(str);

      reset_buf();
      pack_int32(i);
      nrpc_send_response();
    }
    else if (func_num == COMBO) {
      char str[BUF_SIZE];

      i = unpack_int32();
      unpack_string(str);

//      printf("combo(): i = %d\n", i);
//      printf("combo(): str = %ls\n", str);

      do_combo(i, str);

      nrpc_std_response();
    }
    else {
      exit(-1);
    }
  }
}

int
test_string(char *s)
{
  return(0);
}

int
do_combo(int i, char *s)
{
//  int j;

//  printf("do_combo(): s = %s\n", s);

//  for (j = 0; j < i; j++)
//    printf("%s\n", s);
  
  return(0);
}

int
test_send_int(int i)
{
  int ret_code;

//  printf("test_send_int(): i = %d\n", i);

//  wprintf(L"nrpc_set_function(SEND_INT)...\n");
  nrpc_set_function(SEND_INT);

//  wprintf(L"pack_int32()...\n");
  pack_int32(i);

//  wprintf(L"nrpc_send_message()...\n");
  nrpc_send_message();

//  wprintf(L"unpack_int32()...\n");
  ret_code = unpack_int8();

//  wprintf(L"Return Code: %d\n", ret_code);

  return(ret_code);
}

int
test_send_string(char *s)
{
  int ret_code;

  nrpc_set_function(SEND_STR);
  pack_string(s);
  nrpc_send_message();
  ret_code = unpack_int8();

//  printf("Return Code: %d\n", i);

  return(ret_code);
}

int
test_combo(int i, char *s)
{
  int ret_code;

//  printf("test_combo(): s = %s\n", s);

  nrpc_set_function(COMBO);
  pack_int32(i);
  pack_string(s);
  nrpc_send_message();
  ret_code = unpack_int8();

//  printf("Return Code: %d\n", ret_code);

  return(ret_code);
}


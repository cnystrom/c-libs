/*
 *    new_rpc.c
 *
 *    Copyright (C) 2002  <Chris Nystrom>
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    Soli Deo Gloria
 *
 */

#include "sock_lib.h"
#include "types.h"
#include "buffer.h"
#include "new_rpc.h"

int  get_buffer(void);
void send_buffer(void);

static SOCKET s;
static SOCKET s_tmp;

static int nrpc_server = FALSE;

byte *bp;

void
nrpc_init_server(int port_num)
{
  s_tmp = open_socket(port_num);

  printf("Waiting for connections...\n");

  s = accept_socket(s_tmp);
  nrpc_server = TRUE;

  bp = get_buf();
}

int
nrpc_init_client(char *server, int port_num)
{
  int len;

  bp = get_buf();

  s = call_socket(server, port_num);

  printf("Socket initialized...\n");

  /* Get welcome message */

  len = read_socket(s, bp, BUF_SIZE);

  printf("Socket read...\n");

  if (len == 0)
  {
    printf("new_rpc initialize_client error: login failed\n");
    close_socket(s);
    return(-1);
  }

//  printf("wlecome = |%s|\n", bp); // welcome message

  return(0);
}

void
nrpc_welcome(char *str)
{
  int len = strlen(str);

  write_socket(s, str, len);
}

void
nrpc_send_message(void)
{
  usleep(1);

  // Send message...
  send_buffer();

  //  Get response...
  get_buffer();
}

void
nrpc_send_response(void)
{
  send_buffer();
}

void
nrpc_reverse(void)
{
  write_socket(s, "reverse", 7);
}

void
nrpc_exit(void)
{
  write_socket(s, "exit", 4);
}

void
nrpc_close(void)
{
  close_socket(s);

  if (nrpc_server)
    close_socket(s_tmp);
}

void
nrpc_set_function(Sint16 func_num)
{
  reset_buf();
  pack_int16(func_num);
}

Sint16
nrpc_get_function(void)
{
  Sint16 func_num;

  if (get_buffer() < 0) {
    return(NRPC_FAILED);
  }

  if (strncmp(bp, "exit", 4) == 0) {
    return(NRPC_EXIT);
  }

  if (strncmp(bp, "reverse", 7) == 0) {
    return(NRPC_REVERSE);
  }

  func_num = unpack_int16();

//  printf("nrpc_get_function(): func_num = %d\n", func_num);

  return(func_num);
}

void
nrpc_std_response(void)
{
  reset_buf();

  pack_int8(0);

  nrpc_send_response();
}

void
nrpc_wait_for_reverse(void)
{
  for (;;)
  {
    Sint16 func_num;

    func_num = nrpc_get_function();

    if (func_num == NRPC_EXIT) {
//      printf("Exit command rcvd.\n");
      nrpc_close();
      exit(0);
    }
    else if (func_num == NRPC_REVERSE) {
//      printf("Reverse command rcvd.\n");
      break;
    }
    else {
//      printf("bad function number!\n");
    }
  }
}

int
get_buffer(void)
{
  int len;

  reset_buf();

  len = read_socket(s, bp, BUF_SIZE);

  if (len <= 0) {
    fprintf(stderr, "get_buffer(): read error\n");
    return -1;
  }

  set_buf_index(len);

  return 0;
}

void
send_buffer(void)
{
  int i, len;

  len = get_buf_index();

  i = write_socket(s, bp, len);

  if (i != len) {
    fprintf(stderr, "send_buffer(): write error\n");
  }
}


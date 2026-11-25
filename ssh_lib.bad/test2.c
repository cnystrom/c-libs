//
//    test2.c
//
//    02/02/05 - Chris Nystrom <cnystrom@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../misc_lib/uio.h"
#include "../misc_lib/wlog.h"
#include "../misc_lib/tty_echo.h"
#include "ssh_lib.h"

int test2(char *username, char *hostname, char *command, char *passwd);
int main_loop(void);


int
main(void)
{
  int ret;
  char password[10] = "CHANGEME";

  echo_off();

  wlog_init_file("test2.log");
  wlog("Starting test2...\n");

  printf("\nLoading server on shuttle...\n\n");

  ret = test2("cnystrom", "macmini.newio.org", "src/ssh_lib/test2b", password);
//  ret = test2("cnystrom", "shuttle.newio.org", "src/ssh_lib/test2b", password);
//  ret = test2("cnystrom", "shuttle.newio.org", "src/nio/new_rpc/server", password);

  printf("\nFinished loading server on shuttle...\n\n");

  if (ret < 0) {
    printf("ssh failed\n");
  }

  printf("\n");
  wlog_close();
  echo_on();
  exit(0);
}

int
test2(char *username, char *hostname, char *command, char *passwd)
{
  int ret;

  printf("call_ssh()...\n");

  ret = call_ssh(username, hostname, command);

  printf("back from call_ssh()...\n");

  if (ret < 0)
    return (ret);

  ret = verify_passwd(passwd);

  printf("back from verify_passwd()...\n");

  if (ret < 0)
    return (ret);

  return(main_loop());
}

int
main_loop(void)
{
  int cc;        // char count
  int flag = 1;  // Flag to keep track of first line read
  int ret;       
  char buf[BUFSIZ];

  printf("in main_loop()...\n");

  cc = read_ssh_s(buf, BUFSIZ, USE_UIO);

  printf("back from read_ssh()...\n");

  printf("ssh cc # = %d\n", cc);

  while(cc > 0) {
    while (cc <= 2) {
      printf("cc <= 2. Bad packet.\n");
      write_ssh("\n");
      printf("Re-reading...\n");
      cc = read_ssh(buf, BUFSIZ, USE_UIO);
      printf("Re-read.\n");
    }

    buf[cc] = 0;

    printf("server -> client: |%s|\n", buf);

    if (flag) {
      ret = check_login(buf);

      if (ret == LOGIN_BAD) {
        printf("login or password bad. Sorry!\n");
        done_ssh();
        return (-1);
      }
      else if (ret == NO_PROG) {
        printf("Program not available. Sorry!\n");
        done_ssh();
        return (-1);
      }
      else {
        flag = 0;
      }
    }

    if (strncmp(buf, "exit", 4) == 0) {
      printf("normal exit.\n");
      done_ssh();
      return 0;
    }

    write_ssh("ACK");

    printf("client -> server: ACK\n");
    printf("---------------------\n");

    cc = read_ssh(buf, BUFSIZ, USE_UIO);
  }

  printf("exiting ssh_rpc()\n");
  done_ssh();
  return (-1);
}


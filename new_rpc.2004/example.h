/*
 * example.h
 */

#include "new_rpc.h"

#define PORTNUM   32662

/* Function numbers */

#define SEND_INT       0
#define SEND_DOUBLE    1 
#define SEND_STRING    2

int send_int(int i);
int send_double(double d);
int send_string(char *s);
int test_string(char *s);


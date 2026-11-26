#
CC =  gcc
BIN = server client
# Older Unix systems needed -lnsl (and sometimes -lsocket).
LIB =
CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX

all: $(BIN)

server:		server.o example.o rand.o new_rpc.a
		$(CC) -o $@ server.o example.o rand.o new_rpc.o msg_lib.o sock_lib.o $(LIB)

client:		client.o example.o rand.o new_rpc.a
		$(CC) -o $@ client.o example.o rand.o new_rpc.o msg_lib.o  sock_lib.o $(LIB)

new_rpc.a:	new_rpc.o msg_lib.o sock_lib.o
		ar rcs new_rpc.a new_rpc.o sock_lib.o msg_lib.o
		ranlib new_rpc.a

sock_lib.o:	sock_lib.c sock_lib.h
		$(CC) $(CFLAGS) -c sock_lib.c

msg_lib.o:	msg_lib.c msg_lib.h
		$(CC) $(CFLAGS) -c msg_lib.c

new_rpc.o:	new_rpc.c new_rpc.h msg_lib.h sock_lib.h
		$(CC) $(CFLAGS) -c new_rpc.c

server.o:	server.c example.h example.c rand.h rand.c new_rpc.h sock_lib.h
		$(CC) $(CFLAGS) -c server.c

client.o:	client.c example.h example.c rand.h rand.c new_rpc.h sock_lib.h
		$(CC) $(CFLAGS) -c client.c

example.o:	example.h example.c new_rpc.h msg_lib.h
		$(CC) $(CFLAGS) -c example.c

rand.o:		rand.h rand.c
		$(CC) $(CFLAGS) -c rand.c

install:
		cp *.a ..

clean:
		rm -f *.o *.a $(BIN) core


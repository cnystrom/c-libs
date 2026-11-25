#
CC =  gcc
BIN = server client client2
#BIN = udp_lib.a
LIB = -lnsl  # Linux
#LIB = -lnsl -lsocket # Solaris

CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX

all: $(BIN)

server:		server.o udp_lib.a
		$(CC) -o $@ server.o udp_lib.a

client:		client.o udp_lib.a
		$(CC) -o $@ client.o udp_lib.a

client2:	client2.o udp_lib.a
		$(CC) -o $@ client2.o udp_lib.a

udp_lib.a:	udp_lib.o
		ar rcs udp_lib.a udp_lib.o
		ranlib udp_lib.a

udp_lib.o:	udp_lib.c udp_lib.h
		$(CC) $(CFLAGS) -c udp_lib.c

indent:
		indent -kr -i8 *.h *.c

install:
		cp *.a ..

new:		clean all

clean:
		rm -f *.o *.a a.out buffer $(BIN) core .*.swp *~


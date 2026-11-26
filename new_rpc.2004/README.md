# new_rpc.2004

A dated snapshot of Chris Nystrom's New RPC library (copyright 2002,
source mailed to himself in January 2004). It is a small RPC-over-sockets
library with example `client` and `server` programs, and is an ancestor
of NewIO.

This tree is older than `new_rpc.bad` in this repo, but it is a complete
working package: it builds and the example client and server run together.
`new_rpc.bad` is a later, unfinished snapshot and does not.

## Build

```sh
make
```

The original Makefile linked with `-lnsl`, a library from older Unix
that is not needed on current Linux, so that flag was dropped.

## Test

Start the server, then in another window run the client. They exchange a
string, an int, and a double, reverse roles, and exit. The default port
is 32662 on localhost.

```sh
./server
./client
```

## License

GNU GPL version 2 or later. See the file headers and the `COPYING` file
in the repo root.

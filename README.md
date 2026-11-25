# c-libs

A bundle of Chris Nystrom's small C libraries from the mid-2000s:

- **misc_lib** — the newest snapshot (helpers for I/O, netstrings, URLs,
  tty echo, logging). Older snapshots `.019` and `.010` were not included.
- **udp_lib** — a small UDP client/server library, with example
  `client`, `client2`, and `server` programs.
- **file_xfr_lib** — `ftpget.c` and `ftpupload.c` (libcurl-based).
- **ssh_lib.bad** — a PTY-based SSH helper library (12 Mar 2004). The
  directory name is original.
- **new_rpc.bad** — an RPC-over-sockets library. The `.bad` tree is the
  slightly newer of the two snapshots; `.old` was not included.

## Origin

From Chris Nystrom's personal source archive (the hallie tree), posted
publicly at his request. Headers are typically copyright 2002 and 2005
(ssh_lib: 2004).

## Pages

Chris's old programs page is at https://nystrom.family/chris/old/programs.html.
All of Chris's code: https://nystrom.family/chris/code/

## License

Chris's files are typically under the GNU LGPL 2.1 or GPL 2; see each
header. `ssh_lib.bad/ssh_lib.c` has a short author header without a
license paragraph.

## Third-party files removed

`misc_lib/strlcat.c` and `misc_lib/strlcpy.c` (Todd C. Miller, 1998).
Compiled test binaries in `udp_lib`, `file_xfr_lib`, and `ssh_lib.bad`
were stripped.

## Build

- **udp_lib**: `make` succeeded here with gcc (a signedness warning in
  `recvfrom`).
- **misc_lib**: `make` fails because the Makefile still lists the
  removed Todd Miller sources. Some remaining files also fail on a
  modern `mkdir()` (two-argument) if compiled directly.
- **new_rpc.bad**: the `.a` library built; linking the sample `server`
  failed on `-lnsl` (a library from older Unix, not present here).
- **ssh_lib.bad**: the tests include `../misc_lib/uio.h` and did not
  build standalone from this directory.
- **file_xfr_lib**: needs `<curl/curl.h>`; not compiled here.

A hardcoded test-login credential in `file_xfr_lib/ftpupload.c` and in `ssh_lib.bad/test1.c` and `test2.c` was replaced with the placeholder CHANGEME. No other source was modified.

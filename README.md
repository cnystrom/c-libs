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

The GNU LGPL 2.1 (or later) text is in LICENSE; the GNU GPL 2 (or later) text is in COPYING.

## Third-party files removed

`misc_lib/strlcat.c` and `misc_lib/strlcpy.c` (Todd C. Miller, 1998).
Compiled test binaries in `udp_lib`, `file_xfr_lib`, and `ssh_lib.bad`
were stripped.

## Build

- **misc_lib**: `make` builds the library. A new original `strlcpy`/`strlcat`
  (2026) was added so the Makefile can build it. The 2026.1 release fixes
  a bug in `url.c`: when a URL had no port, the port string was left
  without a terminating NUL. `misc_lib/test_url.c` checks that case.
  Some remaining files also fail on a modern `mkdir()` (two-argument) if
  compiled directly. `misc_lib.h` declares `basename`, which can clash
  with glibc when `_GNU_SOURCE` is set.
- **udp_lib**: `make` builds the library and the example `client`,
  `client2`, and `server` programs (a signedness warning in `recvfrom`).
  `time.c` may need `<arpa/inet.h>` for `inet_addr` on some systems.
- **new_rpc.bad**: the `.a` library built; linking the sample `server`
  failed on `-lnsl` (a library from older Unix, not present here).
  `new_rpc_s.c` is also missing `<stdio.h>`, and `new_rpc_c.c` has a
  conflicting prototype for `nrpc_init_server`.
- **ssh_lib.bad**: the sources include `../misc_lib/uio.h`, which is not
  in this tree, so they did not build standalone from this directory.
- **file_xfr_lib**: needs libcurl. `ftpget.c` includes `<curl/types.h>`,
  which was removed from current libcurl, so this did not compile here.
  `ftpupload.c` is also missing `<unistd.h>` for `close`.

A hardcoded test-login credential in `file_xfr_lib/ftpupload.c` and in `ssh_lib.bad/test1.c` and `test2.c` was replaced with the placeholder CHANGEME. No other source was modified.

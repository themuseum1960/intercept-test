# wincompat — POSIX-on-Windows shim headers

Tiny compatibility headers used **only** when cross-building the aviation
decoders (acarsdec, dumpvdl2) for Windows with mingw-w64 in CI
(`.github/workflows/build-decoders-windows.yml`).

These decoders are Linux-first and `#include` a handful of POSIX headers that
mingw simply doesn't ship (`<sys/socket.h>`, `<netdb.h>`, `<err.h>`,
`<sysexits.h>`). Because mingw has no header by those names, putting these
shims on the compiler's include path (`-I`) satisfies the `#include` lines
without any source edits and without shadowing any real system header.

| Shim | Maps to | Why |
|---|---|---|
| `sys/socket.h` | `<winsock2.h>` + `<ws2tcpip.h>` + a `WSAStartup` constructor | UDP output (`netout.c`, `statsd.c`) uses BSD sockets |
| `netdb.h` | `<winsock2.h>` + `<ws2tcpip.h>` | `getaddrinfo`/`gai_strerror` live here on Windows |
| `err.h` | local `err`/`errx`/`warn`/`warnx` | BSD error helpers; not in mingw |
| `sysexits.h` | `EX_*` constants | BSD exit codes; not in mingw |

Plus the workflow passes `-Dffs=__builtin_ffs` (POSIX `ffs` → GCC builtin) and
links `-lws2_32`.

These are guarded with `#ifdef _WIN32` so they're inert anywhere else. They are
NOT used by the INTERCEPT Python app at all.

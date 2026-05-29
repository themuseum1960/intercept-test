/* wincompat: satisfy <sys/socket.h> on mingw by mapping to Winsock.
 *
 * mingw ships no <sys/socket.h>, so this shim is the only header by that name
 * on the include path — it cannot shadow a real system header. Used when
 * cross-building acarsdec / dumpvdl2 for Windows in CI. Inert off-Windows.
 */
#ifndef WINCOMPAT_SYS_SOCKET_H
#define WINCOMPAT_SYS_SOCKET_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

/* The decoders never call WSAStartup() themselves (they assume BSD sockets are
 * always ready). Initialise Winsock once at process start via a constructor so
 * socket()/getaddrinfo() work if the user ever enables UDP/StatsD output.
 * Winsock is refcounted, so the duplicate calls across translation units that
 * include this header are harmless. */
static void __attribute__((constructor, used)) _wincompat_wsa_init(void)
{
	WSADATA _wincompat_wsadata;
	WSAStartup(MAKEWORD(2, 2), &_wincompat_wsadata);
}
#endif /* _WIN32 */

#endif /* WINCOMPAT_SYS_SOCKET_H */

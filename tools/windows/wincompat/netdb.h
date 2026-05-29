/* wincompat: satisfy <netdb.h> on mingw by mapping to Winsock.
 *
 * getaddrinfo/freeaddrinfo/gai_strerror and struct addrinfo live in
 * <ws2tcpip.h> on Windows. mingw ships no <netdb.h>, so this is the only
 * header by that name on the include path. Inert off-Windows.
 */
#ifndef WINCOMPAT_NETDB_H
#define WINCOMPAT_NETDB_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#endif /* WINCOMPAT_NETDB_H */

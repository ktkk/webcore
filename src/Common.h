#pragma once

#include <sstream>
#include <cstring>
#include <string>
#include <iostream>

#ifdef INCLUDE_SOCKET_HEADERS

#if defined(linux)

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <asm-generic/socket.h>

#endif // defined(linux)

#if defined(_WIN32) || defined(WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>

#endif // defined(_WIN32) || defined(WIN32)

#endif // INCLUDE_SOCKET_HEADERS
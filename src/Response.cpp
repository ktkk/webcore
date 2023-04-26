#include <WebCore/Response.h>

#include <iostream>

#if defined(linux)

#include <asm-generic/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#endif

#if defined(_WIN32) || defined(WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>

#endif

#define CRLF "\r\n"

using namespace WebCore;

void Response::flush()
{
    send(m_client_socket, m_buffer.c_str(), m_buffer.size(), 0);

    m_buffer.clear();
}

std::string Response::to_string()
{
    std::string server = "WebCore v0.1";

    std::string response;

    response += "HTTP/1.1 ";
    response += std::to_string(m_status.get_number()) + " " + m_status.get_reason_phrase() + CRLF;

    return response;
}

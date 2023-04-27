#include "Common.h"

#if defined(linux)
#include <sys/socket.h>
#endif // defined(linux)

#if defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#endif // defined(_WIN32) || defined(WIN32)

#include <WebCore/Response.h>

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

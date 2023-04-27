#include "Common.h"
#include <sstream>

#if defined(linux)
#include <sys/socket.h>
#endif // defined(linux)

#if defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#endif // defined(_WIN32) || defined(WIN32)

#include <WebCore/Response.h>

#define CRLF "\r\n"

using namespace WebCore;

void Response::add_headers(const std::vector<HttpHeader>& headers)
{
    for (auto header : headers) {
        m_headers.push_back(header);
    }
}

void Response::flush()
{
    send(m_client_socket, m_buffer.c_str(), m_buffer.size(), 0);

    m_buffer.clear();
}

std::string Response::to_string()
{
    std::string server = "WebCore v0.1";

    std::stringstream response;

    response << "HTTP/1.1 ";
    response << std::to_string(m_status.get_number()) + " " + m_status.get_reason_phrase() + CRLF;

    for (auto& header : m_headers) {
        response << header.name << ": " << header.value << CRLF;
    }

    response << m_buffer;

    return response.str();
}

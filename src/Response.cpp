#include "Common.h"

#if defined(linux)
#include <sys/socket.h>
#endif // defined(linux)

#if defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#endif // defined(_WIN32) || defined(WIN32)

#include <sstream>

#include <WebCore/Response.h>

static constexpr auto CRLF = "\r\n";

using namespace WebCore;

void Response::add_headers(const std::initializer_list<HttpHeader>& headers)
{
    m_headers.insert(m_headers.end(), headers.begin(), headers.end());
}

void Response::flush()
{
    send(m_client_socket, m_buffer.c_str(), static_cast<int>(m_buffer.size()), 0);

    m_buffer.clear();
}

std::string Response::to_string()
{
    std::string server = "WebCore v0.1";

    std::stringstream response;

    response << "HTTP/1.1 ";
    response << std::to_string(m_status.get_number()) + " " + m_status.get_reason_phrase() + CRLF;

    for (const auto& header : m_headers) {
        response << header.name << ": " << header.value << CRLF;
    }

    response << m_buffer;

    return response.str();
}

#include <WebCore/Response.h>

#include <iostream>

#define CRLF "\r\n"

using namespace WebCore;

// TODO: Create a cmake config header that defines macros for version

std::string Response::to_string()
{
    std::string server = "WebCore v0.1";

    std::string response;

    response += "HTTP/1.1 ";
    response += std::to_string(m_status.get_number()) + " " + m_status.get_reason_phrase() + CRLF;
    response += "Server: " + server + CRLF;
    response += "Content-Type: " + m_type + CRLF;

    response += CRLF;
    response += m_body + CRLF;

    return response;
}

#pragma once

#include <array>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(WIN32)

#include <winsock2.h>

#endif

#include "HttpHeader.h"
#include "HttpStatus.h"

namespace WebCore {

class App;

class Response {
public:
    void set_status(const HttpStatus& status) { m_status = status; }
    void add_header(const HttpHeader& header) { m_headers.push_back(header); }
    void add_headers(const std::vector<HttpHeader>& headers);

    void write(const std::string& data) { m_buffer += data; }
    void flush();

private:
#if defined(_WIN32) || defined(WIN32)
    using Socket = SOCKET;
#else
    using Socket = int;
#endif

private:
#if defined(_WIN32) || defined(WIN32)
    Socket m_client_socket = INVALID_SOCKET;
#else
    Socket m_client_socket = -1;
#endif

    void set_client_socket(const Socket client_socket)
    {
        m_client_socket = client_socket;
    }

    std::string to_string();

private:
    friend App;

    HttpStatus m_status = HttpStatus::Ok;
    std::string m_buffer = "";
    std::vector<HttpHeader> m_headers;
};

}

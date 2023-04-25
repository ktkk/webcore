#pragma once

#include <string>

namespace WebCore {

class HttpMethod {
public:
    enum HttpMethodValue : int;

    constexpr HttpMethod(HttpMethodValue value)
        : m_value(value)
    {
    }

    constexpr operator HttpMethodValue() const { return m_value; }
    explicit operator bool() const = delete;

    std::string get_method_string() const;
    static HttpMethod from_method_string(std::string method_string);

private:
    HttpMethodValue m_value;

    static std::pair<HttpMethodValue, std::string> m_method_strings[];
};

enum HttpMethod::HttpMethodValue : int {
    Get,
    Head,
    Post,
    Put,
    Delete,
    Connect,
    Options,
    Trace,
    Patch,
    NonStandard,
};

#define GET HttpMethod::Get
#define HEAD HttpMethod::Head
#define POST HttpMethod::Post
#define PUT HttpMethod::Put
#define DELETE HttpMethod::Delete
#define CONNECT HttpMethod::Connect
#define OPTIONS HttpMethod::Options
#define TRACE HttpMethod::Trace
#define PATCH HttpMethod::Patch

}

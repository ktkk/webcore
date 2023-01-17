#pragma once

#include <map>
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

private:
    HttpMethodValue m_value;

    static std::map<HttpMethodValue, std::string> m_method_strings;
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
};

}

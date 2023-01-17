#include <WebCore/HttpMethod.h>

#include <iostream>

using namespace WebCore;

std::pair<HttpMethod::HttpMethodValue, std::string> HttpMethod::m_method_strings[] {
    { HttpMethod::Get, "GET" },
    { HttpMethod::Head, "HEAD" },
    { HttpMethod::Post, "POST" },
    { HttpMethod::Put, "PUT" },
    { HttpMethod::Delete, "DELETE" },
    { HttpMethod::Connect, "CONNECT" },
    { HttpMethod::Options, "OPTIONS" },
    { HttpMethod::Trace, "TRACE" },
    { HttpMethod::Patch, "PATCH" },
};

std::string HttpMethod::get_method_string() const
{
    for (const auto& pair : m_method_strings) {
        if (pair.first == m_value) {
            return pair.second;
        }
    }

    std::cerr << "Unreachable";
    return "";
}

HttpMethod HttpMethod::from_method_string(std::string method_string)
{
    for (const auto& pair : m_method_strings) {
        if (pair.second == method_string) {
            return pair.first;
        }
    }

    std::cerr << "Unreachable";
    return HttpMethod::Get;
}

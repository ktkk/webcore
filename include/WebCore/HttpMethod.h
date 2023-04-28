#pragma once

#include <string>

namespace WebCore {

class HttpMethod {
public:
    enum HttpMethodValue : int;

public:
    constexpr HttpMethod(const HttpMethodValue& value)
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

static constexpr HttpMethod GET = HttpMethod::Get;
static constexpr HttpMethod HEAD = HttpMethod::Head;
static constexpr HttpMethod POST = HttpMethod::Post;
static constexpr HttpMethod PUT = HttpMethod::Put;
#ifndef DELETE // winnt.h
static constexpr HttpMethod DELETE = HttpMethod::Delete;
#endif
static constexpr HttpMethod CONNECT = HttpMethod::Connect;
static constexpr HttpMethod OPTIONS = HttpMethod::Options;
static constexpr HttpMethod TRACE = HttpMethod::Trace;
static constexpr HttpMethod PATCH = HttpMethod::Patch;

}

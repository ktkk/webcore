#include <WebCore/HttpMethod.h>

using namespace WebCore;

std::map<HttpMethod::HttpMethodValue, std::string> HttpMethod::m_method_strings {
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

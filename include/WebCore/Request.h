#pragma once

#include <map>
#include <string>

#include "WebCore/HttpMethod.h"

namespace WebCore {

class Request {
public:
    static Request parse_request(char buffer[], long buffer_length);

    HttpMethod get_method() const { return m_method; }
    std::string get_path() const { return m_path; }
    std::map<std::string, std::string> get_params() const { return m_params; }

private:
    void set_method(const HttpMethod& method) { m_method = method; }
    void set_path(const std::string& path) { m_path = path; }

private:
    HttpMethod m_method = HttpMethod::Get;
    std::string m_path = "";
    std::map<std::string, std::string> m_params {};
};

}

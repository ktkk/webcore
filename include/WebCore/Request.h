#pragma once

#include <map>
#include <string>

#include "WebCore/HttpMethod.h"

namespace WebCore {

class Request {
public:
    static Request parse_request(char buffer[]);

    HttpMethod get_method() { return m_method; }
    std::string get_path() { return m_path; }
    std::map<std::string, std::string> get_params() { return m_params; }

private:
    HttpMethod m_method = HttpMethod::Get;
    std::string m_path = "";
    std::map<std::string, std::string> m_params {};
};

}

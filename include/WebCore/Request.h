#pragma once

#include <map>
#include <string>

namespace WebCore {

class Request {
public:
    std::string get_method() { return m_method; }
    std::string get_path() { return m_path; }
    std::map<std::string, std::string> get_params() { return m_params; }

private:
    std::string m_method;
    std::string m_path;
    std::map<std::string, std::string> m_params;
};

}
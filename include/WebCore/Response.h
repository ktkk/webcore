#pragma once

#include <string>

#include "HttpStatus.h"

namespace WebCore {

class App;

class Response {
public:
    void set_status(HttpStatus status) { m_status = status; }
    void set_type(std::string type) { m_type = type; }
    void set_body(std::string body) { m_body = body; }

private:
    friend App;

    HttpStatus m_status = HttpStatus::Ok;
    std::string m_type = "";
    std::string m_body = "";

    std::string to_string();
};

}

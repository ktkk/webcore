#pragma once

#include <string>

#include "HttpStatus.h"

class Response {
public:
    void set_status(HttpStatus status) { m_status = status; }
    void set_body(std::string body) { m_body = body; }

private:
    HttpStatus m_status;
    std::string m_body;
};

#pragma once

#include <string>

namespace WebCore {

class HttpStatus {
public:
    enum HttpStatusValue : int;

    constexpr HttpStatus(HttpStatusValue value)
        : m_value(value)
    {
    }

    constexpr operator HttpStatusValue() const { return m_value; }
    explicit operator bool() const = delete;

    constexpr int get_number() const { return (int)m_value; }

    std::string get_reason_phrase() const;
    static HttpStatus from_reason_phrase(std::string reason_phrase);

private:
    HttpStatusValue m_value;

    static std::pair<HttpStatusValue, std::string> m_reason_phrases[];
};

enum HttpStatus::HttpStatusValue : int {
    Ok = 200,
    NotFound = 404,
};

}

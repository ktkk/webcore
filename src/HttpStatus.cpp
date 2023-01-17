#include <WebCore/HttpStatus.h>

#include <iostream>

using namespace WebCore;

std::pair<HttpStatus::HttpStatusValue, std::string> HttpStatus::m_reason_phrases[] {
    { HttpStatus::Ok, "OK" },
    { HttpStatus::NotFound, "NOT FOUND" },
};

std::string
HttpStatus::get_reason_phrase() const
{
    for (const auto& pair : m_reason_phrases) {
        if (pair.first == m_value) {
            return pair.second;
        }
    }

    std::cerr << "Unreachable";
    return "";
}

HttpStatus HttpStatus::from_reason_phrase(std::string reason_phrase)
{
    for (const auto& pair : m_reason_phrases) {
        if (pair.second == reason_phrase) {
            return pair.first;
        }
    }

    std::cerr << "Unreachable";
    return HttpStatus::NotFound;
}

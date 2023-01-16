#include <WebCore/HttpStatus.h>

using namespace WebCore;

std::map<HttpStatus::HttpStatusValue, std::string> HttpStatus::m_reason_phrases {
    { HttpStatus::Ok, "OK" },
    { HttpStatus::NotFound, "NOT FOUND" },
};

std::string
HttpStatus::get_reason_phrase() const
{
    return m_reason_phrases[m_value];
}

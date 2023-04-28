#include "Common.h"

#include <locale>
#include <chrono>
#include <iomanip>

#include <WebCore/Utils/Logger.h>

using namespace WebCore;
using namespace Utils;

#define BRACED(text) "[" << text << "]"
#define COLORED(color, text) "\033[" << std::to_string((int)color) << "m" << text << "\033[39m"
#define BOLD(text) "\033[1m" << text << "\033[0m"

#define PREFIX(color, prefix, date) BOLD(BRACED(COLORED(color, prefix) << " " << date))

static inline std::string trim(const std::string& s)
{
    // skip leading whitespace
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        ++start;
    }

    // skip trailing whitespace
    auto end = s.end();
    do {
        --end;
    } while (end != start && std::isspace(*end));

    return std::string { start, end + 1 };
}

static std::string get_current_time_localized(const std::string& locale)
{
    std::string time;

    using namespace std::chrono;

    const auto now = system_clock::now();
    const auto time_point = zoned_time(std::chrono::current_zone(), now);
    const auto local_now = floor<minutes>(time_point.get_local_time());

    std::stringstream ss;
    ss.imbue(std::locale(locale));
    ss << local_now;

    return trim(time);
}

void Logger::info(const Logger::Message& message) const
{
    std::stringstream full_message;
    full_message << PREFIX(m_info_color, "INFO", get_current_time_localized(m_locale));
    full_message << " " << message;

    m_info_outstream << full_message.rdbuf() << std::endl;
}

void Logger::warn(const Logger::Message& message, int severity) const
{
    (void)severity;

    std::stringstream full_message;
    full_message << PREFIX(m_warn_color, "WARN", get_current_time_localized(m_locale));
    full_message << " " << message;

    m_warn_outstream << full_message.rdbuf() << std::endl;
}

void Logger::error(const Logger::Message& message, int severity) const
{
    (void)severity;

    std::stringstream full_message;
    full_message << PREFIX(m_error_color, "ERROR", get_current_time_localized(m_locale));
    full_message << " " << message;

    m_error_outstream << full_message.rdbuf() << std::endl;
}

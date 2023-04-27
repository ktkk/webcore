#include "Common.h"

#include <clocale>
#include <ctime>
#include <locale>

#include <WebCore/Utils/Logger.h>

using namespace WebCore;
using namespace Utils;

#define BRACED(text) "[" << text << "]"
#define COLORED(color, text) "\033[" << std::to_string((int)color) << "m" << text << "\033[39m"
#define BOLD(text) "\033[1m" << text << "\033[0m"

#define PREFIX(color, prefix, date) BOLD(BRACED(COLORED(color, prefix) << " " << date))

void Logger::info(Logger::Message message)
{
    std::stringstream full_message;
    full_message << PREFIX(m_info_color, "INFO", get_current_time_localized());
    full_message << " " << message;

    m_info_outstream << full_message.rdbuf() << std::endl;
}

void Logger::warn(Logger::Message message, int severity)
{
    (void)severity;

    std::stringstream full_message;
    full_message << PREFIX(m_warn_color, "WARN", get_current_time_localized());
    full_message << " " << message;

    m_warn_outstream << full_message.rdbuf() << std::endl;
}

void Logger::error(Logger::Message message, int severity)
{
    (void)severity;

    std::stringstream full_message;
    full_message << PREFIX(m_error_color, "ERROR", get_current_time_localized());
    full_message << " " << message;

    m_error_outstream << full_message.rdbuf() << std::endl;
}

std::string trim(std::string s)
{
    auto start = s.begin();

    while (start != s.end() && std::isspace(*start)) {
        ++start; // skip leading whitespace
    }

    auto end = s.end();

    do {
        --end; // skip trailing whitespace
    } while (end != start && std::isspace(*end));

    return std::string(start, end + 1);
}

std::string Logger::get_current_time_localized()
{
    std::string previous_locale = std::setlocale(LC_ALL, nullptr);

    std::string time;

    const std::time_t now = std::time(nullptr);

    std::setlocale(LC_TIME, m_locale.c_str());
    time = std::asctime(std::localtime(&now));

    std::setlocale(LC_ALL, previous_locale.c_str());

    return trim(time);
}

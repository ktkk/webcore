#pragma once

#include <iostream>
#include <string>

namespace WebCore {

namespace Utils {

class Logger {
public:
    using Message = std::string;

    void info(Message message);
    void warn(Message message, int severity = 1);
    void error(Message message, int severity = 2);

    enum class TermColor : int {
        Black = 30,
        Red = 31,
        Green = 32,
        Yellow = 33,
        Blue = 34,
        Magenta = 35,
        LightBlue = 36,
        White = 37,
    };

    void set_info_color(TermColor color = TermColor::LightBlue) { m_info_color = color; }
    void set_warn_color(TermColor color = TermColor::Yellow) { m_warn_color = color; }
    void set_error_color(TermColor color = TermColor::Red) { m_error_color = color; }

private:
    bool m_colors_enabled = true;
    bool m_colors_muted = false;

    std::string m_locale = "en_US.utf-8";

    TermColor m_info_color = TermColor::LightBlue;
    TermColor m_warn_color = TermColor::Yellow;
    TermColor m_error_color = TermColor::Red;

    std::ostream& m_info_outstream = std::clog;
    std::ostream& m_warn_outstream = std::cerr;
    std::ostream& m_error_outstream = std::cerr;

    std::string get_current_time_localized();
};

}

}

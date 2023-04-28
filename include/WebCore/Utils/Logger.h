#pragma once

#include <iostream>
#include <string>

namespace WebCore {

namespace Utils {

class Logger {
public:
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

    using Message = std::string;

public:

    void info(const Message& message) const;
    void warn(const Message& message, int severity = 1) const;
    void error(const Message& message, int severity = 2) const;

    void set_info_color(TermColor color = TermColor::LightBlue) { m_info_color = color; }
    void set_warn_color(TermColor color = TermColor::Yellow) { m_warn_color = color; }
    void set_error_color(TermColor color = TermColor::Red) { m_error_color = color; }
    
    void set_locale(const std::string& locale) { m_locale = locale; }

private:
    //bool m_colors_enabled = true;
    //bool m_colors_muted = false;

    std::string m_locale = "en_US.utf-8";

    TermColor m_info_color = TermColor::LightBlue;
    TermColor m_warn_color = TermColor::Yellow;
    TermColor m_error_color = TermColor::Red;

    std::ostream& m_info_outstream = std::clog;
    std::ostream& m_warn_outstream = std::cerr;
    std::ostream& m_error_outstream = std::cerr;
};

}

}

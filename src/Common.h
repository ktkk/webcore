#pragma once

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

static inline void left_trim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

static inline void right_trim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(),
        s.end());
}

static inline void trim(std::string& s)
{
    right_trim(s);
    left_trim(s);
}

static inline std::string left_trim_copy(std::string s)
{
    left_trim(s);

    return s;
}

static inline std::string right_trim_copy(std::string s)
{
    right_trim(s);

    return s;
}

static inline std::string trim_copy(std::string s)
{
    trim(s);

    return s;
}
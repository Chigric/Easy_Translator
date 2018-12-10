#pragma once

#include <string>

class Logger
{
    unsigned int lineno;
    unsigned int charno;

public:
    Logger();
    ~Logger();

    inline void nextChar() {++charno;}
    void newLine();

    void log(const std::string&);
    void warning(const std::string&, const std::string&);
    void error(const std::string&, const std::string&, const int);
};

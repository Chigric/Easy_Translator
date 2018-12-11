#pragma once

#include <string>

class Logger
{
    unsigned int lineno;
    unsigned int charno;
    bool logStatus;

public:

    inline void nextChar() {++charno;}
    void newLine();

    void setPrintStatus(const bool);
    void log(const std::string&);
    void log(const std::string&, const int);

    void warning(const std::string&, const std::string&, const int = 0);
    void error(const std::string&, const std::string&, const int);

    Logger();
    ~Logger();
};

#pragma once

#include <fstream>

class Parser
{
private:
    //id of symbols
    enum TYPES {NUM = 256};

    std::ifstream* iStream;

    unsigned int lineno;
    int lookahead;

    bool printStatus;

    void printToken();
    const int lexan();
public:
    Parser();
    ~Parser();

    void parse(const char*);
};

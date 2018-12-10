#pragma once

#include <fstream>
#include <string>

#include "global.h"
#include "logger.h"

class Lexer
{
private:
    std::ifstream* iStream;
    Logger* logger;

    //Lexer
    void nextChar(char&);
public:
    Lexer(std::ifstream* __iStream);
    ~Lexer();

    const int lexan(SyntacticWord*);
};

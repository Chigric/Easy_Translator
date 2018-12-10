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

    void commentLine();
    void number(SyntacticWord*, char);
    void readString(SyntacticWord*, char);
    //Lexer
    void nextChar(char&);
public:
    Lexer(std::ifstream* __iStream);
    ~Lexer();

    const int lexan(SyntacticWord*);
};

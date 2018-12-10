#pragma once

#include <fstream>
#include <string>

#include "lexer.h"

class Parser
{
private:
    //id of symbols
    enum TYPES {NONE = -1, NUM = 256, IF, ELSE, PRINT, LESS, COMPARE, DONE};

    //constants
    static const char EOS = '\0';

    struct Variable {
        int token_id;
        std::string lexbuf;

        void clear() {
            token_id = TYPES::NONE;
            lexbuf.clear();
        }

        Variable& operator = (const Variable& ptr) {
            this->token_id = ptr.token_id;

            this->lexbuf.clear();
            this->lexbuf = ptr.lexbuf;
            return *this;
        }
    };

    Variable* curToken;
    std::ifstream* iStream;

    unsigned int lineno;
    unsigned int charno;
    int lookahead;

    bool printStatus;

    //Lexer
    void printToken();
    const int lexan();
    void nextChar(char&);

    //Error(logger)
    void warning(const std::string&, const std::string&);
    void error(const std::string&, const std::string&, const int);

    //Grammar
    void expr();
    int logic();
    void match(int);
public:
    Parser();
    ~Parser();

    void parse(const char*);
};

#pragma once

#include <fstream>
#include <string>

class Parser
{
private:
    //id of symbols
    enum TYPES {NONE = -1, NUM = 256, STRING, LESS, COMPARE, DONE};

    //constants
    static const char EOS = '\0';
    // static const int BSIZE = 128;

    struct Variable {
        int token_id;
        int value;
        std::string lexbuf;

        void clear() {
            token_id = 0;
            value = 0;
            lexbuf.clear();
        }
    };

    Variable* curToken;
    std::ifstream* iStream;

    unsigned int lineno;
    unsigned int charno;
    int lookahead;

    bool printStatus;

    void printToken();
    const int lexan();
    void nextChar(char&);
public:
    Parser();
    ~Parser();

    void parse(const char*);
};

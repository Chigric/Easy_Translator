#pragma once

#include <string>

//id of symbols
enum TYPES {NONE = -1, NUM = 256, IF, ELSE, PRINT, LESS, COMPARE, DONE};

//constants
static const char EOS = '\0';

static bool printStatus = true;

struct SyntacticWord {
    int token_id;
    std::string lexbuf;

    void clear() {
        token_id = TYPES::NONE;
        lexbuf.clear();
    }

    SyntacticWord& operator = (const SyntacticWord& ptr) {
        this->token_id = ptr.token_id;

        this->lexbuf.clear();
        this->lexbuf = ptr.lexbuf;
        return *this;
    }
};

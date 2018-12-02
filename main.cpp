#include <iostream>
#include <fstream>
#include <string>

#include "ctype.h"

using namespace std;

void lexan(char symbol)
{
    unsigned int lineno = 0;

    if (isdigit(symbol)) { //symbol - numeral
        cerr << symbol << endl;
    } else if (isalpha(symbol)) {
        // *some code*
    } else switch (symbol) {
        case '+':
            cerr << '+' << endl;
            break;
        case '\n':
            ++lineno;
            cerr << "lineno = " << lineno << endl;
            break;
        case ' ':
        case '\t':
        default:
            break;
    }
}

int main(int argc, char const *argv[]) {
    ifstream ifs;
    ifs.open(argv[1], ifstream::in);
    // cout << endl;

    char c;
    while (ifs.get(c)) {
        // cout << ' ' << c;
        lexan(c);
    }

    ifs.close();
    return 0;
}

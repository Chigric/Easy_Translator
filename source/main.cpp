#include <iostream>
#include <fstream>
#include <string>

#include "stdio.h"
#include "ctype.h"

#include "parser.h"

using namespace std;

static const unsigned int MAX_BUF = 256;

int lexan(char symbol)
{
    unsigned int lineno = 0;

    if (isdigit(symbol)) {          //symbol - numeral
        cerr << symbol << endl;
    } else if (isalpha(symbol)) {   //symbol - char
        cerr << symbol << endl;
    } else switch (symbol) {
        case '#':
            return '#';
        case '+':
            cerr << '+' << endl;
            break;
        case '\n':
            ++lineno;
            cerr << "lineno = " << lineno << endl;
            return '\n';
        case ' ':
        case '\t':
        default:
            return -1;
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    ifstream ifs;
    ifs.open(argv[1], ifstream::in);
    // cout << endl;

    char c;
    while (ifs.get(c)) {
        // cout << ' ' << c;
        int token = lexan(c);
        if (token == '#') {
            do {
                printf("%d\n", token);
                ifs.get(c);
                token = lexan(c);
            } while (c == '\n');
            printf("exit from do while()\n");
        }
    }

    parser();

    ifs.close();
    return 0;
}

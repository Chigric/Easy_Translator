#include "parser.h"

// #include <stdio.h>

using namespace std;

int main(int argc, char const *argv[]) {
    Parser* pars = new Parser;
    pars->parse(argv[1]);

    delete pars;

    return 0;
}

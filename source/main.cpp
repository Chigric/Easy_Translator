#include "parser.h"

// #include <stdio.h>

using namespace std;

int main(int argc, char const *argv[]) {
    Parser pars;
    pars.parse(argv[1]);
    return 0;
}

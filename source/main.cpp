#include "parser.h"
#include "logger.h"

#include <stdio.h>

using namespace std;

Logger* logger = new Logger;

int main(int argc, char const *argv[]) {
    Parser* pars = new Parser;
    pars->parse(argv[1]);

    delete pars;
    delete logger;

    return 0;
}

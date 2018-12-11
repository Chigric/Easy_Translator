#include "parser.h"
#include "logger.h"

#include <stdio.h>

using namespace std;

Logger* logger = new Logger;

int main(int argc, char const *argv[]) {
    logger->setPrintStatus(false);

    Parser* pars = new Parser;
    pars->parse(argv[1]);

    delete pars;
    delete logger;

    return 0;
}

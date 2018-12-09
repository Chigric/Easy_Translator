#include <iostream>

#include "stdio.h"
#include "ctype.h"

#include "parser.h"

using namespace std;

Parser::Parser()
{
	printStatus = true;
	lineno = 0;
	lookahead = -1;

	iStream = nullptr;

	std::cout << "I'am parser" << std::endl;
}

Parser::~Parser()
{
	if (iStream != nullptr)
		delete iStream;
}

void Parser::parse(const char* fileName)
{
	iStream = new ifstream;
    iStream->open(fileName, ifstream::in);

    lookahead = this->lexan();
	this->printToken();

    iStream->close();
}

void Parser::printToken()
{
	if (printStatus == true && lookahead != -1)
		printf("print %d\n", lookahead);
}

const int Parser::lexan()
{
	if (iStream == nullptr)
		return -1;

	while (true) {
		char symbol;
		iStream->get(symbol);

	    if (isdigit(symbol)) {          //symbol - numeral
	        // cerr << symbol << endl;
	    } else if (isalpha(symbol)) {   //symbol - char
	        // cerr << symbol << endl;
	    } else switch (symbol) {
	        case '#':
				printStatus = false;
	            break;
	        case '+':
	            // std::cerr << '+' << std::endl;
	            break;
	        case '\n':
				if (printStatus == false)
					printStatus = true;

	            std::cerr << "lineno = " << ++lineno << std::endl;
	            return '\n';
	        case ' ':
	        case '\t':
	        default:
	            return 0;
	    }
	}
    return 0;
}

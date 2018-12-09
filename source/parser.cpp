#include <iostream>

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "parser.h"

using namespace std;

Parser::Parser()
{
	printStatus = true;
	lineno = 0;
	charno = 0;

	curToken = new Variable;
	iStream = nullptr;

	std::cout << "I'am parser" << std::endl;
}

Parser::~Parser()
{
	if (iStream != nullptr)
		delete iStream;

	if (curToken != nullptr)
		delete curToken;
}

void Parser::parse(const char* fileName)
{
	iStream = new ifstream;
    iStream->open(fileName, ifstream::in);

	if (this->lexan() == NONE) {
		std::cerr << "ERROR 0x3: some problem with lexan\n";
		return;
	}
	this->printToken();

    iStream->close();
}

void Parser::printToken()
{
	if (printStatus == true || curToken->token_id != NONE)
		std::cout << curToken->lexbuf << std::endl;
}

const int Parser::lexan()
{
	curToken->clear();

	if (iStream == nullptr)
		return -1;

	char symbol;
	while (true) {
		nextChar(symbol);

		std::cout << "lexan " << symbol << std::endl;

		if (symbol == ' ' || symbol == '\t')	//symbol - nothing
			continue;
		else if (symbol == '#') {
			printStatus = false;
			iStream->unget();
			getline(static_cast<std::istream&>(*iStream), curToken->lexbuf);
			std::cout << "\tlexan (comment line) " <<
			 	curToken->lexbuf << std::endl;
			curToken->clear();

			continue;
		} else if (symbol == '\n') {	//symbol - new line
			if (printStatus == false)
				printStatus = true;
			charno = 0;
	        std::cout << "\tlexan (№ lineno) = " << ++lineno << std::endl;

			continue;
		} else if (isdigit(symbol)) {	//symbol - numeral
	        std::cout << "\tlexan (digit) " << symbol << std::endl;
			curToken->token_id = NUM;

			while (isdigit(symbol)) {
				curToken->lexbuf.push_back(symbol);
				nextChar(symbol);
			}
			iStream->unget();
			std::cout << "\tlexan (full number) " <<
				curToken->lexbuf << std::endl;
			return 0;

	    } else if (isalpha(symbol) || symbol == '_') {   //symbol - char
	        std::cout << "\tlexan (alpha) " << symbol << std::endl;
			curToken->token_id = STRING;

			while (isalnum(symbol)) {
				curToken->lexbuf.push_back(symbol);
				nextChar(symbol);
			}
			iStream->unget();
			return 0;

	    } else if (symbol == '<') { 	//symbol - operator '<'
			std::cout << "\tlexan (LESS) " << symbol << std::endl;

			return LESS;
		} else if (symbol == '=') {		//symbol = operator '='
		 nextChar(symbol);
			if (symbol == '=')			//symbol = operator "=="
				return NONE;
			else
				return -1;
		} else if (iStream->eof()) {
			curToken->token_id = NONE;
			return NONE;
		} else {
			curToken->token_id = DONE;
			return DONE;
		}
	}
	return -1;
}


void Parser::nextChar(char& _c)
{
	if (iStream == nullptr) {
		std::cerr << "ERROR 0x2: in nextChar():" <<
			"(" << lineno << ":" << charno << ") " <<
			"ты совсем ку-ку,\niStream = nullptr\n";
		return;
	}
	iStream->get(_c);
	++charno;
}

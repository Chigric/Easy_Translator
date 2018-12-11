#include <iostream>

#include "lexer.h"

Lexer::Lexer(std::ifstream* __iStream)
{
    this->iStream = __iStream;
}

Lexer::~Lexer()
{}

void Lexer::commentLine()
{
    std::string tmp;

    printStatus = false;
    iStream->unget();
    getline(static_cast<std::istream&>(*iStream), tmp);
    iStream->unget();

    std::cout << "\tlexan (comment line) " << tmp << std::endl;
}

void Lexer::number(SyntacticWord* curToken, char symbol)
{
    curToken->token_id = NUM;

    while (isdigit(symbol)) {
        curToken->lexbuf.push_back(symbol);
        nextChar(symbol);
    }
    iStream->unget();
    std::cout << "\tlexan (full number) " <<
        curToken->lexbuf << std::endl;
}

void Lexer::readString(SyntacticWord* curToken, char symbol)
{
	while (isalnum(symbol) || symbol == '_') {
		curToken->lexbuf.push_back(symbol);
		nextChar(symbol);
	}
	iStream->unget();
}

const int Lexer::lexan(SyntacticWord* curToken)
{
	curToken->clear();

	if (iStream == nullptr)
		return -1;

	char symbol;
	while (!(iStream->eof())) {
		nextChar(symbol);

		std::cout << "lexan " << symbol << std::endl;

		if (symbol == ' ' || symbol == '\t')	//symbol - nothing
			continue;
		else if (symbol == '#') {
            commentLine();
			continue;
		} else if (symbol == '\n') {	//symbol - new line
			if (printStatus == false)
				printStatus = true;
            logger->newLine();
			continue;
		} else if (isdigit(symbol)) {	//symbol - numeral
	        std::cout << "\tlexan (digit) " << symbol << std::endl;
            number(curToken, symbol);
			return NUM;

	    } else if (isalpha(symbol) || symbol == '_') {   //symbol - char
	        std::cout << "\tlexan (alpha) " << symbol << std::endl;
            readString(curToken, symbol);
        	if (curToken->lexbuf == "if") {
        		return IF;
        	} else if (curToken->lexbuf == "else") {
        		return ELSE;
        	} else {
        		logger->warning(__func__,
                    "Unkown word: " + curToken->lexbuf,
                    curToken->lexbuf.size());
        		return NONE;
        	}

	    } else if (symbol == '<') { 	//symbol - operator '<'
			std::cout << "\tlexan (LESS) " << symbol << std::endl;
			return LESS;
		} else if (symbol == '=') {		//symbol = operator '='
		 nextChar(symbol);
			if (symbol == '=') {		//symbol = operator "=="
				std::cout << "\tlexan (COMPARE) " << symbol << std::endl;
				return COMPARE;
			}
			else
				return NONE;
		} else if (iStream->eof()) {
			curToken->token_id = DONE;
			return DONE;
		} else {
			return symbol;
		}
	}
	return DONE;
}

void Lexer::nextChar(char& _c)
{
	if (iStream == nullptr)
		logger->error(__func__, "ты совсем ку-ку,\niStream = nullptr", 0x2);

	iStream->get(_c);
	logger->nextChar();
}

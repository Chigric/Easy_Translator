#include <iostream>

#include "lexer.h"

Lexer::Lexer(std::ifstream* __iStream)
{
    this->iStream = __iStream;

    this->logger = new Logger;
}

Lexer::~Lexer()
{
    if (logger != nullptr)
        delete logger;
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
			printStatus = false;
			iStream->unget();
			getline(static_cast<std::istream&>(*iStream), curToken->lexbuf);
			iStream->unget();

			std::cout << "\tlexan (comment line) " <<
			 	curToken->lexbuf << std::endl;
			curToken->clear();

			continue;
		} else if (symbol == '\n') {	//symbol - new line
			if (printStatus == false)
				printStatus = true;
            logger->newLine();
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
			return NUM;

	    } else if (isalpha(symbol) || symbol == '_') {   //symbol - char
	        std::cout << "\tlexan (alpha) " << symbol << std::endl;

			while (isalnum(symbol)) {
				curToken->lexbuf.push_back(symbol);
				nextChar(symbol);
			}
			iStream->unget();

			if (curToken->lexbuf == "if") {
				curToken->token_id = IF;
				return IF;
			} else if (curToken->lexbuf == "else") {
				curToken->token_id = ELSE;
				return ELSE;
			} else {
				logger->warning(__func__, "Unkown word: " + curToken->lexbuf);
				return NONE;
			}

	    } else if (symbol == '<') { 	//symbol - operator '<'
			std::cout << "\tlexan (LESS) " << symbol << std::endl;
			curToken->lexbuf.push_back(symbol);
			curToken->token_id = LESS;

			return LESS;
		} else if (symbol == '=') {		//symbol = operator '='
		 nextChar(symbol);
		 curToken->lexbuf.push_back(symbol);

			if (symbol == '=') {		//symbol = operator "=="
				std::cout << "\tlexan (COMPARE) " << symbol << std::endl;
				curToken->lexbuf.push_back(symbol);
				curToken->token_id = LESS;
				return COMPARE;
			}
			else
				return NONE;
		} else if (iStream->eof()) {
			curToken->token_id = DONE;
			return DONE;
		} else {
			curToken->token_id = NONE;
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

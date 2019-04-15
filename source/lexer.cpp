#include <iostream>
#include <string>

#include <stdlib.h>

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

	logger->log("\tlexan (comment line) " + tmp);
}

void Lexer::number(SyntacticWord* curToken, char symbol)
{
	curToken->token_id = NUM;

	while (isdigit(symbol)) {
		curToken->lexbuf.push_back(symbol);
		nextChar(symbol);
	}
	iStream->unget();
	logger->log("\tlexan (full number) " + curToken->lexbuf);
}

void Lexer::readString(SyntacticWord* curToken, char symbol)
{
	while (isalnum(symbol) || symbol == '_') {
		curToken->lexbuf.push_back(symbol);
		nextChar(symbol);
	}
	iStream->unget();
	logger->log("\tlexan (full string) " + curToken->lexbuf);
}

void Lexer::newLine()
{
	if (printStatus == false)
		printStatus = true;
	logger->newLine();
}

const int Lexer::keyWords(SyntacticWord* curToken, char symbol)
{
	logger->log("lexan (char) " + symbol);
	readString(curToken, symbol);

	if (curToken->lexbuf == "if") {
		return IF;
	} else if (curToken->lexbuf == "else") {
		return ELSE;
	} else if (curToken->lexbuf == "print") {
		return PRINT;
	} else {
		logger->warning(__func__,
			"Unkown word: " + curToken->lexbuf,
			curToken->lexbuf.size());
		return NONE;
	}
}

const int Lexer::operators(SyntacticWord* curToken, char symbol)
{
	switch (symbol) {	//symbol - operator
		case '<':		//symbol - operator '<'
			logger->log("lexan (LESS) <");
			return LESS;
		case '=': 		//symbol = operator '='
			nextChar(symbol);
			if (symbol == '=') {	//symbol = operator "=="
				logger->log("lexan (COMPARE) ==");
				return COMPARE;
			} else
				return NONE;
		default:
			if (iStream->eof()) {
				curToken->token_id = DONE;
				return DONE;
			} else {
				return symbol;
			}
	}
}

const int Lexer::meaningTerm(SyntacticWord* curToken, char symbol)
{
	if (isdigit(symbol)) {	//symbol - numeral
	   number(curToken, symbol);
	   return NUM;
	} else if (isalpha(symbol) || symbol == '_') {   //symbol - char
		keyWords(curToken, symbol);
	} else {
		operators(curToken, symbol);
	}
}

const int Lexer::lexan(SyntacticWord* curToken)
{
	curToken->clear();

	if (iStream == nullptr)
		return -1;

	char symbol;
	while (!(iStream->eof())) {
		nextChar(symbol);

		switch (symbol) {
			case ' ':	//symbol - nothing
			case '\t':
				continue;
			case '#':	//symbol - comment line
				commentLine();
				continue;
			case '\n':	//symbol - new line
				this->newLine();
				continue;
			default:
				meaningTerm(curToken, symbol);
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

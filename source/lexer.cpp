#include <iostream>
#include <string>

#include <stdlib.h>

#include "lexer.h"

Lexer::Lexer(std::ifstream* __iStream)
{
	this->iStream = __iStream;

	isCreating = false;
	idTypeVar = NONE;
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

	while (isdigit(symbol) || symbol == '.') {
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

void Lexer::chooseTypeVar(std::string& str)
{
	if (str == "bool")
		idTypeVar = BOOL;
	if (str == "int")
		idTypeVar = INT;
	if (str == "real")
		idTypeVar = REAL;
	if (str == "string")
		idTypeVar = STRING;
}

int Lexer::keyWords(SyntacticWord* curToken, char symbol)
{
	logger->log("lexan (char) " + (std::string) &symbol);
	readString(curToken, symbol);

	if (curToken->lexbuf == "if") {
		return IF;
	} else if (curToken->lexbuf == "else") {
		return ELSE;
	} else if (curToken->lexbuf == "print") {
		return PRINT;
	} else if (curToken->lexbuf == "bool" ||
				curToken->lexbuf == "int" ||
				curToken->lexbuf == "real" ||
				curToken->lexbuf == "string")
	{
		chooseTypeVar(curToken->lexbuf);
		return VAR;
	} else {
		if (!isCreating) {
			logger->warning(__func__,
					"Unkown word: " + curToken->lexbuf,
					curToken->lexbuf.size());
		}
		return NONE;
	}
}

void Lexer::stringLine(SyntacticWord* curToken)
{
	std::string strWord;
	do {
		std::getline((std::istream&)*iStream, strWord, '\"');
		curToken->lexbuf += strWord;
	} while (strWord == "\"");

	logger->log("lexan (string) " + curToken->lexbuf);
}

int Lexer::operators(SyntacticWord* curToken, char symbol)
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
				return ASSIGN;
		case '"':
			stringLine(curToken);
			return STRING;
		default:
			if (iStream->eof()) {
				curToken->token_id = DONE;
				return DONE;
			} else {
				return symbol;
			}
	}
}

int Lexer::meaningTerm(SyntacticWord* curToken, char symbol)
{
	if (isdigit(symbol)) {	//symbol - numeral
	   number(curToken, symbol);
	   return NUM;
	} else if (isalpha(symbol) || symbol == '_') {   //symbol - char
		return keyWords(curToken, symbol);
	} else {
		return operators(curToken, symbol);
	}
}

int Lexer::lexan(SyntacticWord* curToken)
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
				return meaningTerm(curToken, symbol);
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

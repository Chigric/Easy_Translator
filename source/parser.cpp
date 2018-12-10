#include <iostream>
//#include <iomanip>

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "parser.h"

Parser::Parser()
{
	printStatus = true;
	lookahead = NONE;

	curToken = new SyntacticWord;
	logger = new Logger;
	iStream = nullptr;
	lexer = nullptr;

	std::cout << "I'am parser" << std::endl;
}

Parser::~Parser()
{
	if (curToken != nullptr)
		delete curToken;
	if (lexer != nullptr)
		delete lexer;
	if (logger != nullptr)
		delete logger;
	if (iStream != nullptr)
		delete iStream;
}

void Parser::parse(const char* fileName)
{
	iStream = new std::ifstream;
    iStream->open(fileName, std::ifstream::in);

	lexer = new Lexer(iStream);

	if ((lookahead = lexer->lexan(curToken)) == DONE) {
		logger->error(__func__, "some problem with lexan", 0x3);
		exit(0x3);
	}
	expr();
	// this->printToken();

    iStream->close();
}

void Parser::printToken()
{
	if (printStatus == true || lookahead != DONE)
		std::cout << curToken->lexbuf << std::endl;
}

void Parser::expr()
{
	while (lookahead != DONE) {
		std::cout << "> expr:\t" << logic() << std::endl;
		match(';');
	}
}

int Parser::logic()
{
	SyntacticWord ptr = (*curToken);
	match(NUM);
	switch (lookahead) {
		int tmp1, tmp2, answer;
		case LESS:
			match(LESS);
			if (ptr.token_id == (*curToken).token_id) {
				tmp1 = stoi(ptr.lexbuf);
				tmp2 = stoi((*curToken).lexbuf);
				answer = (tmp1 < tmp2);
			} else
				logger->error(__func__, "Syntex error", 0x6);

			match(NUM);
			return answer;
		case COMPARE:
			match(COMPARE);
			if (ptr.token_id == (*curToken).token_id) {
				tmp1 = stoi(ptr.lexbuf);
				tmp2 = stoi((*curToken).lexbuf);
				answer = (tmp1 == tmp2);
			} else
				logger->error(__func__, "Syntex error", 0x7);

			match(NUM);
			return answer;
		default:
			break;
	}
	return ptr.token_id;
}

void Parser::match(int token)
{
	if (lookahead == token)
		lookahead = lexer->lexan(curToken);
	else
		logger->error(__func__, "Syntex error", 0x5);
}

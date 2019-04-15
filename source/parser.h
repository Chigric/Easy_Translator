#pragma once

#include <fstream>
#include <string>

#include "global.h"
#include "logger.h"
#include "lexer.h"

class Parser
{
private:
	SyntacticWord* curToken;
	std::ifstream* iStream;
	//Lexer
	Lexer* lexer;

	int lookahead;

	void printToken();

	//Grammar
	void expr();
	void statement(const bool);
	int logic();
	void match(const int);
public:
	Parser();
	~Parser();

	void parse(const char*);
};

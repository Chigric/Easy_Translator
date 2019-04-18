#pragma once

#include <fstream>
#include <string>
#include <set>

#include "global.h"
#include "logger.h"
#include "lexer.h"

class Lexer;

class Parser
{
private:
	std::set <Variable*>* varTable;

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
	//Variables
	void create(std::string&);
	void assign(std::string&);
public:
	Parser();
	~Parser();

	void parse(const char*);
};

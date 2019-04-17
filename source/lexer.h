#pragma once

#include <fstream>
#include <string>

#include "global.h"
#include "logger.h"

class Lexer
{
private:
	std::ifstream* iStream;

	void commentLine();
	void newLine();

	int meaningTerm(SyntacticWord*, char);
	int keyWords(SyntacticWord*, char);
	int operators(SyntacticWord*, char);
	void number(SyntacticWord*, char);
	void readString(SyntacticWord*, char);
	//Lexer
	void nextChar(char&);
public:
	Lexer(std::ifstream* __iStream);
	~Lexer();

	int lexan(SyntacticWord*);
};

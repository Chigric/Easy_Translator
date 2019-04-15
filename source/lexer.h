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

	const int meaningTerm(SyntacticWord*, char);
	const int keyWords(SyntacticWord*, char);
	const int operators(SyntacticWord*, char);
	void number(SyntacticWord*, char);
	void readString(SyntacticWord*, char);
	//Lexer
	void nextChar(char&);
public:
	Lexer(std::ifstream* __iStream);
	~Lexer();

	const int lexan(SyntacticWord*);
};

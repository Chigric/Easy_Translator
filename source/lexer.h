#pragma once

#include <fstream>
#include <string>

#include "global.h"
#include "logger.h"
#include "parser.h"

class Lexer
{
private:
	std::ifstream* iStream;

	friend class Parser;
	bool isCreating;
	int idTypeVar;

	void commentLine();
	void newLine();

	//lexan (private)
	int meaningTerm(SyntacticWord*, char);
	int keyWords(SyntacticWord*, char);
	int operators(SyntacticWord*, char);
	void number(SyntacticWord*, char);
	void readString(SyntacticWord*, char);
	//Variable
	void chooseTypeVar(std::string&);
	void stringLine(SyntacticWord*);
	//Lexer
	void nextChar(char&);
public:
	Lexer(std::ifstream* __iStream);
	~Lexer();

	int lexan(SyntacticWord*);
};

#include <iostream>
//#include <iomanip>

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "parser.h"

Parser::Parser()
{
	printStatus = true;
	lineno = 0;
	charno = 0;
	lookahead = NONE;

	curToken = new Variable;
	iStream = nullptr;

	std::cout << "I'am parser" << std::endl;
}

Parser::~Parser()
{
	if (iStream != nullptr)
		delete iStream;

	if (curToken != nullptr)
		delete curToken;
}

void Parser::parse(const char* fileName)
{
	iStream = new std::ifstream;
    iStream->open(fileName, std::ifstream::in);

	if ((lookahead = this->lexan()) == DONE) {
		this->error(__func__, "some problem with lexan", 0x3);
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

const int Parser::lexan()
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
			charno = 0;
	        std::cout << "\tlexan (№ lineno) = " << ++lineno << std::endl;

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
				this->warning(__func__, "Unkown word: " + curToken->lexbuf);
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


void Parser::nextChar(char& _c)
{
	if (iStream == nullptr)
		this->error(__func__, "ты совсем ку-ку,\niStream = nullptr", 0x2);

	iStream->get(_c);
	++charno;
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
	Variable ptr = (*curToken);
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
				this->error(__func__, "Syntex error", 0x6);

			match(NUM);
			return answer;
		case COMPARE:
			match(COMPARE);
			if (ptr.token_id == (*curToken).token_id) {
				tmp1 = stoi(ptr.lexbuf);
				tmp2 = stoi((*curToken).lexbuf);
				answer = (tmp1 == tmp2);
			} else
				this->error(__func__, "Syntex error", 0x7);

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
		lookahead = lexan();
	else
		this->error(__func__, "Syntex error", 0x5);
}

void Parser::warning(const std::string &nameFunc,
						const std::string &text)
{
	std::cerr << "WARNING: in " << nameFunc <<
		" (" << lineno << ":" << charno << ") " <<
		text << std::endl;
}

void Parser::error(const std::string &nameFunc,
					const std::string &text,
					int numError)
{
	std::cerr << "ERROR " << std::hex << numError <<
	 	": in " << nameFunc <<
		" (" << lineno << ":" << charno << ") " <<
		text << std::endl;
	exit(numError);
}

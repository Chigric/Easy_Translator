#pragma once

#include <string>
#include "logger.h"

//id of symbols
enum K_WORDS {NONE = -1, NUM = 256, STRING, IF, ELSE, PRINT, LESS, COMPARE, ASSIGN, DONE, VAR, BOOL, INT, REAL, NAME};

//constants
static const char EOS = '\0';

static bool printStatus = true;

union Types {
	bool Bool;
	int Int;
	double Double;
	std::string String;
};

struct Variable {
	int token_id;
	Types* value;
	std::string name;

	Variable()
	{
		this->token_id = NONE;
		this->value = nullptr;
		this->name = "";
	}

	Variable(std::string& str__,
				int id__ = NONE,
				Types* val__ = nullptr)
	{
		this->token_id = id__;
		this->value = val__;
		this->name = str__;
	}

	/*Variable(SyntacticWord* ptr, Types* val__ = nullptr)
	{
		this->value = val__;

		this->token_id = ptr.token_id;
		this->name.clear();
		this->name = ptr.name;
	}*/

	Variable& operator = (const Variable& ptr)
	{
		this->token_id = ptr.token_id;
		this->value = ptr.value;
		this->name.clear();
		this->name = ptr.name;

		return *this;
	}
};

struct SyntacticWord {
	int token_id;
	std::string lexbuf;

	SyntacticWord()
	{
		token_id = K_WORDS::NONE;
		lexbuf = "";
	}

	SyntacticWord(int type, std::string& str)
	{
		token_id = type;
		lexbuf = str;
	}

	void clear()
	{
		token_id = K_WORDS::NONE;
		lexbuf.clear();
	}

	SyntacticWord& operator = (const SyntacticWord& ptr)
	{
		this->token_id = ptr.token_id;

		this->lexbuf.clear();
		this->lexbuf = ptr.lexbuf;
		return *this;
	}
};

extern Logger* logger;

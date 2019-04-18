#include <iostream>

#include "logger.h"

Logger::Logger () : lineno(1), charno(1), logStatus(true)
{}

Logger::~Logger ()
{}

void Logger::setPrintStatus(const bool _b)
{
	this->logStatus = _b;
}

void Logger::newLine()
{
	charno = 0;
	this->log("\tlexan (№ lineno) = ", lineno++);
}

void Logger::log(const std::string& text)
{
	if (logStatus)
		std::cout << text << std::endl;
}

void Logger::log(const std::string& text, const int num)
{
	if (logStatus)
		std::cout << text << num << std::endl;
}

void Logger::warning(const std::string &nameFunc,
						const std::string &text,
						const int charMinus)
{
	std::cerr << "WARNING: in " << nameFunc <<
		" (" << lineno << ":" << charno - charMinus - 2 << ") " <<
		text << std::endl;
}

void Logger::error(const std::string &nameFunc,
					const std::string &text,
					int numError)
{
	std::cerr << "ERROR " << numError <<
		": in " << nameFunc <<
		" (" << lineno << ":" << charno << ") " <<
		text << std::endl;
	exit(numError);
}

#include <iostream>

#include "logger.h"

Logger::Logger () : lineno(0), charno(0)
{}

Logger::~Logger ()
{}

void Logger::newLine()
{
    charno = 0;
    std::cout << "\tlexan (№ lineno) = " << ++lineno << std::endl;
}

void Logger::log(const std::string& text)
{
    std::cout << text << std::endl;
}

void Logger::warning(const std::string &nameFunc,
						const std::string &text)
{
	std::cerr << "WARNING: in " << nameFunc <<
		" (" << lineno << ":" << charno << ") " <<
		text << std::endl;
}

void Logger::error(const std::string &nameFunc,
					const std::string &text,
					int numError)
{
	std::cerr << "ERROR " << std::hex << numError <<
	 	": in " << nameFunc <<
		" (" << lineno << ":" << charno << ") " <<
		text << std::endl;
	exit(numError);
}

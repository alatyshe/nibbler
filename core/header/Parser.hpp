#ifndef PARSER_H
# define PARSER_H

#include "../header/Info.hpp"
#include "../header/Exception.hpp"

class Parser {

public:
	Parser();
	~Parser();

	int		static parseNumber(std::string &str);
	
private:
	Parser	&operator=(const Parser& src);
	Parser(const Parser &src);
};

#endif

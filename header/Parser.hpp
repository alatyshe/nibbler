#ifndef PARSER_H
# define PARSER_H

#include "../header/Exception.hpp"
#include "../header/Game.hpp"

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

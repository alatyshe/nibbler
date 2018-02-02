#include "../../header/Parser.hpp"

Parser::Parser() { ; }
Parser::~Parser() { ; }

int				Parser::parseNumber(std::string &str) {
	if(!std::regex_match(str, std::regex(INTEGER)))
		throw Exception("Line Error");
	return std::stold(str);
}


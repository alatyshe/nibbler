#include "../header/Parser.hpp"

Parser::Parser() { ; }
Parser::~Parser() { ; }

int       Parser::parseNumber(std::string &str) {
  int     num;

  if(!std::regex_match(str, std::regex(INTEGER))) {
    throw Exception("Wrong params");
  }

  num = std::stold(str);
  if (num > MAX_SIZE) {
    throw Exception(std::to_string(num) + 
        " > min board size(" 
        + std::to_string(MAX_SIZE)
        + ") ");
  } else if (num < MIN_SIZE) {
    throw Exception(std::to_string(num) 
        + " < max board size(" 
        + std::to_string(MIN_SIZE)
        + ") ");
  }
  return num;
}


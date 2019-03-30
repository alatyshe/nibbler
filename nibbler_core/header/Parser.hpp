#pragma once

#include "../header/Info.hpp"
#include "../header/Exception.hpp"

class Parser {

public:
  Parser();
  ~Parser();

  int   static parseNumber(std::string &str);
  
private:
  Parser  &operator=(Parser const & src) = delete;
  Parser(Parser const &src) = delete;
};

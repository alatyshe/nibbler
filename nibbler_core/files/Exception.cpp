# include "../header/Exception.hpp"

Exception::Exception() : _error("") { ; };
Exception::~Exception() throw () { ; };

Exception::Exception(std::string const &error) : _error(error) { 
  std::stringstream error_res;

  error_res << "\033[1;31mERROR \033[0;0m: ";
  error_res << error;
  this->_error = error_res.str();
}

char const        *Exception::what(void) const throw() { 
  return this->_error.c_str();
}
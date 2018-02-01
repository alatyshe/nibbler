# include "../header/Exception.hpp"

Exception::Exception() : _error("") { ; };
Exception::~Exception() throw () { ; };

Exception::Exception(std::string const &error) : _error(error) { ; }

Exception::Exception(std::string const &error, int line = 0) { 
	std::stringstream	error_res;

	if (line != 0)
		error_res << "Line " << line << " : ";
	error_res << "\033[1;31mERROR \033[0;0m: ";
	error_res << error << std::endl;
	this->_error = error_res.str();
};

char const				*Exception::what(void) const throw() { 
	return this->_error.c_str();
}
#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <exception>
# include <string>
# include <sstream>

class					Exception: public std::exception {

private:
	std::string		_error;

	const Exception& operator=(const Exception &);
public:
	Exception(void);
	Exception(const Exception &src);
	Exception(std::string const &error);
	Exception(std::string const &error, int line);
	~Exception(void) throw();

	char const		*what(void) const throw();
};

#endif 
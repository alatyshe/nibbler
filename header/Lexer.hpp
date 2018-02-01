#ifndef LEXER_H
# define LEXER_H

# include <string>

class Lexer {

public:
	Lexer();
	~Lexer();

private:
	Lexer	&operator=(const Lexer& src);
	Lexer(const Lexer &src);
};

#endif

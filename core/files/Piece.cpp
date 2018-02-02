#include "../../header/Piece.hpp"
#include "../../header/Game.hpp"
#include "../../header/Exception.hpp"

//	Construct
Piece::Piece() : 
	_x(0),
	_y(0)
{ ; }

Piece::Piece(int x, int y) :
	_x(x),
	_y(y)
{ ; }

// Destruct
Piece::~Piece() { ; }

//	Getters
int			Piece::GetX() const { return (this->_x); }
int			Piece::GetY() const { return (this->_y); }

//	Setters
void		Piece::SetX(int x) { this->_x = x; }
void		Piece::SetY(int y) { this->_y = y; }
void		Piece::MovePiece(int x, int y){ this->_x += x; this->_y += y; }

std::ostream&	operator<<(std::ostream& os, const Piece& df)
{
	os << RED << "=================================" << RESET << std::endl;
	os << "X : " << df.GetX() << std::endl;
	os << "Y : " << df.GetY() << std::endl;
	os << GREEN << "=================================" << RESET << std::endl;
	return (os);  
}
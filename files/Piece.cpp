#include "../header/Piece.hpp"
#include "../header/Game.hpp"
#include "../header/Exception.hpp"

//	Construct
Piece::Piece() : 
	_x(0),
	_y(0),
	_type(0)
{ ; }

Piece::Piece(int x, int y, int type) :
	_x(x),
	_y(y),
	_type(type)
{ ; }

// Destruct
Piece::~Piece() { ; }

//	Getters
int			Piece::GetX() const { return (this->_x); }
int			Piece::GetY() const { return (this->_y); }
int			Piece::GetType() const { return (this->_type); }

//	Setters
void		Piece::SetX(int x) { this->_x = x; }
void		Piece::SetY(int y) { this->_y = y; }
void		Piece::SetType(int type) { this->_type = type; }
void		Piece::MovePiece(int x, int y){ this->_x += x; this->_y += y; }

std::ostream&	operator<<(std::ostream& os, const Piece& df)
{
	// os << RED << "=================================" << RESET << std::endl;
	// os << "X : " << df.GetX() << std::endl;
	// os << "Y : " << df.GetY() << std::endl;
	os << "| " << df.GetType() << " |";
	// os << "| " << df.GetType() << " |" << std::endl;
	// os << GREEN << "=================================" << RESET << std::endl;
	return (os);  
}
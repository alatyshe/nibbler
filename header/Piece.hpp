#ifndef PIECE_H
# define PIECE_H

# include <string>

// _type - 1(змея) 2(препятствие) 3(яблоко)

class Piece {
	int		_x;
	int		_y;
	int		_type;

public:
	
//	Construct
	Piece();
	Piece(int x, int y, int type);
	
// Destruct
	~Piece();

//	Getters
	int				GetX() const;
	int				GetY() const;
	int				GetType() const;

//	Setters
	void			SetX(int x);
	void			SetY(int y);
	void			SetType(int type);
	void			MovePiece(int x, int y);

private:
	Piece	&operator=(const Piece& src);
	Piece(const Piece &src);

};


std::ostream&	operator<<(std::ostream& os, const Piece& df);


#endif

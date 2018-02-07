#ifndef PLAYER_H
# define PLAYER_H

# include "../header/Game.hpp"

class Player {
	//	Information about game
	int		_score;
	int		_lives;

	//	Next coord for piece(snake body). Can have any integer
	int		_next_x;
	int 	_next_y;

	//	Where move snake head at the moment(). Can have -1 0 1
	int		_head_move_x;
	int		_head_move_y;

	std::vector<Piece *>	_snake;

public:
	
//	Construct
	Player();
	Player(int x, int y);
	
// Destruct
	~Player();
	void				addPieceToSnake();
	void				moveSnakeBody();
	int					putSnakeOnMap();
	void				setHeadMoveXY(int x, int y);

private:
	Player	&operator=(const Player& src);
	Player(const Player &src);

};


std::ostream&	operator<<(std::ostream& os, const Player& df);


#endif

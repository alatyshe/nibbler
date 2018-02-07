# include "../../header/Player.hpp"

Player::Player() { ; }
Player::~Player() { ; }

Player::Player(int x, int y) {

	//	Information about Player
	this->_score = 0;
	this->_lives = 3;

	//	Next move for body
	this->_next_x = 0;
	this->_next_y = 0;

	//	Where move snake head at the moment(). Can have -1 0 1
	this->_head_move_x = 1; // 1(right) or 0(middle) or -1(left)
	this->_head_move_y = 0; // 1(up) or 0(middle) or -1(down)

	//	Create snake
	for (int i = 0; i < SNAKE_LENGTH; i++)
		this->_snake.insert(this->_snake.begin(), new Piece(x + i, y));
}

/*
**	Getters
*/

void 		Player::moveSnakeBody() {
	int			x;
	int			y;
	std::vector<Piece *>::iterator i;

	i = this->_snake.begin();
	while (i != _snake.end()) {

		x = (*i)->GetX();
		y = (*i)->GetY();

		if (i == this->_snake.begin()) {
			(*i)->SetX(x + this->_head_move_x);
			(*i)->SetY(y + this->_head_move_y);
		} else {
			(*i)->SetX(this->_next_x);
			(*i)->SetY(this->_next_y);
		}

		this->_next_x = x;
		this->_next_y = y;
		i++;
	}
	this->_next_x = 0;
	this->_next_y = 0;
}

int 		Player::putSnakeOnMap() {
	// int			x;
	// int			y;
	// int			piece;
	// std::vector<Piece *>::iterator i;

	// i = this->_snake.begin();
	// piece = 0;
	// while (i != this->_snake.end()) {

	// 	x = (*i)->GetX();
	// 	y = (*i)->GetY();
	// 	if (x < 0 || y < 0 || x >= this->_width || y >= this->_height)
	// 	{
	// 		std::cout << x << std::endl;
	// 		return(y);
	// 	}
	// 	else if (this->_map[y][x] == SNAKE_HEAD 
	// 		|| this->_map[y][x] == SNAKE_BODY
	// 		|| this->_map[y][x] == WALL
	// 		)
	// 		return(2);
	// 	else if (this->_map[y][x] == APPLE)
	// 	{
	// 		this->_map[y][x] = SNAKE_HEAD;
	// 		this->putAppleOnMap();
	// 		piece = 1;
	// 	}
	// 	else
	// 	{
	// 		if (i == this->_snake.begin())
	// 			this->_map[y][x] = SNAKE_HEAD;
	// 		else
	// 			this->_map[y][x] = SNAKE_BODY;
	// 	}
	// 	i++;
	// }
	// if (piece == 1)
	// {
	// 	this->_score += 100;
	// 	this->_snake.push_back(new Piece(1, 15));
	// }
	return(0);
}

void		Player::setHeadMoveXY(int x, int y) {
	if (x != 0)
	{
		if (this->_head_move_x != 1 && this->_head_move_x != -1)
		{
			this->_head_move_x = x;
			this->_head_move_y = 0;
		}
	}
	if (y != 0)
	{
		if (this->_head_move_y != 1 && this->_head_move_y != -1)
		{
			this->_head_move_y = y;
			this->_head_move_x = 0;
		}
	}
}

# include "../../header/Game.hpp"

Game::Game() { ; }
Game::~Game() { ; }

Game::Game(int width, int height) {
	//	Create and Null Map
	this->_map = new char*[height];
	for (int i = 0; i < height; i++)
	{
		int j;
		this->_map[i] = new char[width + 1];
		for (j = 0; j < width; j++)
			this->_map[i][j] = 0;
		this->_map[i][j] = '\0';
	}
	this->_width = width;
	this->_height = height;

	//	Information about game
	this->_score = 0;
	this->_level = 2;
	this->_difficult = 1;

	//	Type of visualisation
	this->_visual_type = NCURSES;

	//	Next move for body
	this->_next_x = 0;
	this->_next_y = 0;

	//	Where move snake head at the moment(). Can have -1 0 1
	this->_head_move_x = 1; // 1(right) or 0(middle) or -1(left)
	this->_head_move_y = 0; // 1(up) or 0(middle) or -1(down)

	putWallsOnMap();
	putAppleOnMap();

	//	Create snake
	for (int i = 0; i < SNAKE_LENGTH; i++)
		this->_snake.insert(this->_snake.begin(), new Piece(width / 2 + i - 3, height / 2));
}

/*
**	Getters
*/

int			Game::getScore()		{ return(this->_score); }
int			Game::getLevel()		{ return(this->_level); }
int			Game::getDifficult()	{ return(this->_difficult); }
int			Game::getWidth()		{ return(this->_width); }
int			Game::getHeight()		{ return(this->_height); }
char		**Game::getMap()		{ return(this->_map); }

int 		Game::putSnakeOnMap() {
	int			x;
	int			y;
	bool		apple;
	std::vector<Piece *>::iterator i;

	i = this->_snake.begin();
	apple = false;
	while (i != this->_snake.end()) {

		x = (*i)->GetX();
		y = (*i)->GetY();
		if (x < 0 || y < 0 || x >= this->_width || y >= this->_height)
		{
			std::cout << x << std::endl;
			return(y);
		}
		else if (this->_map[y][x] == SNAKE_HEAD 
			|| this->_map[y][x] == SNAKE_BODY
			|| this->_map[y][x] == WALL
			)
			return(2);
		else if (this->_map[y][x] == APPLE)
		{
			this->_map[y][x] = SNAKE_HEAD;
			apple = true;
		}
		else
		{
			if (i == this->_snake.begin())
				this->_map[y][x] = SNAKE_HEAD;
			else
				this->_map[y][x] = SNAKE_BODY;
		}
		i++;
	}
	if (apple)
	{
		this->_score += 100;
		this->putAppleOnMap();
		this->_snake.push_back(new Piece());
	}
	return(0);
}
void		Game::putWallsOnMap() {
	int 	total_walls;
	int		y;
	int		x;

	srand(time(NULL));   
	total_walls = this->_width * this->_height / 100 * this->_difficult;
	while (total_walls > 0)
	{
		x = rand() % this->_width;
		y = rand() % this->_height;
		if (y != this->_height / 2 && this->_map[y][x] != WALL)
			this->_map[y][x] = WALL;
		total_walls--;
	}
}
void		Game::putAppleOnMap() {
	int		y;
	int		x;

	while (true)
	{
		x = rand() % this->_width;
		y = rand() % this->_height;
		if (this->_map[y][x] != WALL)
		{
			this->_map[y][x] = APPLE;
			break;
		}
	}
}
void		Game::setHeadMoveXY(int x, int y) {
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
void 		Game::moveSnakeBody() {
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
void 		Game::cleanMapFromSnake() {
	for (int i = 0; i < this->_height; i++)
	{
		for (int j = 0; j < this->_width; j++)
		{
			if (this->_map[i][j] == SNAKE_BODY
				|| this->_map[i][j] == SNAKE_HEAD)
				this->_map[i][j] = EMPTY;
		}
	}
}
// void		Game::changeLib() { }

void		Game::runGame()
{
	int		i;

	while(true)
	{
		i = putSnakeOnMap();
		//	PUT HERE VISUAL
		if (this->_visual_type == NCURSES)
			n_curses_visual(this, 0);
		
		if (i != 3 && i != 0)
		{
			if (this->_visual_type == NCURSES)
			{
				n_curses_visual(this, 1);
				endwin();
			}
			break ;
		}
		cleanMapFromSnake();
		moveSnakeBody();
		std::this_thread::sleep_for(std::chrono::milliseconds(260 / this->_level));
	}
	std::cout << i << std::endl;
	std::cout << "Game Over" << std::endl;
}
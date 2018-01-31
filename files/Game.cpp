# include "../header/Game.hpp"

// Construct
Game::Game() { ; }
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

	for (int i = 0; i < 3; i++) {
		this->_snake.insert(this->_snake.begin(), new Piece(width / 2 + i - 3, height / 2, 1));
		// std::cout << *(*this->_snake.begin()) << std::endl;
	}

	this->_score = 0;
	this->_level = 1;
	this->_difficult = 1;
	this->_visual_type = NCURSES;

	this->_width = width;
	this->_height = height;

	this->_next_x = 0;
	this->_next_y = 0;

	this->_head_move_x = 1; // 1(right) or 0(middle) or -1(left)
	this->_head_move_y = 0; // 1(right) or 0(middle) or -1(left)
}

// Destruct
Game::~Game() { ; }

void 		Game::moveSnake() {
	int			temp_x;
	int			temp_y;
	std::vector<Piece *>::iterator i;

	i = this->_snake.begin();
	while (i != _snake.end()) {

		temp_x = (*i)->GetX();
		temp_y = (*i)->GetY();

		if (i == this->_snake.begin()) {
			(*i)->SetX(temp_x + this->_head_move_x);
			(*i)->SetY(temp_y + this->_head_move_y);
		} else {
			(*i)->SetX(this->_next_x);
			(*i)->SetY(this->_next_y);
		}
		
		this->_next_x = temp_x;
		this->_next_y = temp_y;
		i++;
	}
	this->_next_x = 0;
	this->_next_y = 0;
}

int 		Game::putSnakeOnMap() {
	int			temp_x;
	int			temp_y;
	std::vector<Piece *>::iterator i;

	i = this->_snake.begin();
	while (i != this->_snake.end()) {
		temp_x = (*i)->GetX();
		temp_y = (*i)->GetY();
		if (temp_x > this->_width || temp_y > this->_height)
			return (2);
		if (this->_map[temp_y][temp_x] == 1 || this->_map[temp_y][temp_x] == 2)
			return (2);
		else
			this->_map[temp_y][temp_x] = 1;
		i++;
	}
	return (0);
}

void 		Game::cleanMapFromSnake() {
	for (int i = 0; i < this->_height; i++)
	{
		for (int j = 0; j < this->_width; j++)
		{
			if (this->_map[i][j] == 1)
				this->_map[i][j] = 0;
		}
	}
}

int					Game::getScore() { return (this->_score); }
int					Game::getLevel() { return (this->_level); }
int					Game::getDifficult() { return (this->_difficult); }
int					Game::getWidth() { return(this->_width); };
int					Game::getHeight() { return(this->_height); };
char				**Game::getMap() { return (this->_map); }





void		n_curses_visual(Game *g)
{
	char		**map;
	int			score;
	int			level;
	int			difficult;
	int			width;
	int			height;

	static int 	haha;

	if (!haha)
	{
		haha = 1;
		initscr();                   // Переход в curses-режим
		curs_set(0);
		cbreak();
	}


	map = g->getMap();
	score = g->getScore();
	level = g->getLevel();
	difficult = g->getDifficult();
	width = g->getWidth();
	height = g->getHeight();


    start_color();

    init_pair(1, 11, COLOR_BLACK);		//	цвет змейки
    init_pair(2, 9, COLOR_BLACK);		//	цвет препятствия
    init_pair(3, 1, COLOR_BLACK);		//	цвет яблока
    init_pair(4, 8, COLOR_BLACK);		//	серый
    init_pair(5, 15, COLOR_BLACK);		//	сброс цвета

    // timeout(-1);
    // cbreak
    int c = getch();
    c = 2;
	move(0 , 0);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] == 1)
			{
				attron(COLOR_PAIR(1));
				printw("*");
			}
			else if (map[i][j] == 2)
			{
				attron(COLOR_PAIR(2));
				printw("#");
			}
			else if (map[i][j] == 3)
			{
				attron(COLOR_PAIR(3));
				printw("O");
			}
			else
			{
				attron(COLOR_PAIR(4));
				printw(".");
			}
		}
		attron(COLOR_PAIR(4));
		printw("\n");
	}
	attron(COLOR_PAIR(5) | WA_BOLD);
	printw("Score : %d\n" ,score);
	printw("Level : %d\n" ,level);
	printw("Difficult : %d\n", difficult);
	refresh();                   // Вывод приветствия на настоящий экран
}












void		Game::runGame()
{
	int		i;

	while(true)
	{
		moveSnake();
		i = putSnakeOnMap();
		if (i != 3 && i != 0)
		{
			if (this->_visual_type == NCURSES)
				endwin();	// Выход из curses-режима. Обязательная команда.
			break ;
		}

		//	PUT HERE VISUAL
		if (this->_visual_type == NCURSES)
			n_curses_visual(this);
		// printMap();


		cleanMapFromSnake();
		std::this_thread::sleep_for(std::chrono::milliseconds(110 / this->_level));
	}
	std::cout << i << std::endl;
	std::cout << "Game Over" << std::endl;
}



void 		Game::printMap() {
	std::cout << "\033[0;0H";
	for (int i = 0; i < this->_height; i++)
	{
		for (int j = 0; j < this->_width; j++)
		{
			if (this->_map[i][j] == 1)
				std::cout << MAGENTA << '*' << RESET;
			else if (this->_map[i][j] == 2)
				std::cout << RED << '#' << RESET;
			else if (this->_map[i][j] == 3)
				std::cout << RED << 'O' << RESET;
			else
				std::cout << '.';
		}
		std::cout << std::endl;
	}
	std::cout << GREEN << "Score : " << this->_score << std::endl;
	std::cout << "Level : " << this->_level << std::endl;
	std::cout << "Difficult : " << this->_difficult << RESET << std::endl;
}
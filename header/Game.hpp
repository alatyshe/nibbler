#ifndef GAME_H
# define GAME_H

# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define YELLOW				"\x1b[33m"
# define BLUE				"\x1b[34m"
# define MAGENTA			"\x1b[35m"
# define CYAN				"\x1b[36m"
# define BLACK				"\x1b[37m"
# define RESET				"\x1b[0m"

# define INTEGER			"([0-9]+)"

# include <regex>
# include <vector>
# include <string>
# include <iostream>

// SLEEP
# include <chrono>
# include <thread>

# include <ncurses.h>

# include "../header/Piece.hpp"

enum Visual{
	NCURSES
};

class Game {

protected:
	//	Поле

	char	**_map;
	int		_width;
	int		_height;

	int		_score;
	int		_level;
	int		_difficult;

	Visual	_visual_type;

	//	Следующий ход для змейки
	int		_next_x;
	int 	_next_y;

	//	Куда двигается  голова
	int		_head_move_x;
	int		_head_move_y;

	//	Змейка
	std::vector<Piece *>	_snake;

public:
	//	Construct
	Game();
	Game(int width, int height);
	//	Destruct
	~Game();

	// int					checkLive();
	int					putSnakeOnMap();
	void				moveSnake();
	
	void				printMap();

	void 				cleanMapFromSnake();
	void				runGame();

	int					getWidth();
	int					getHeight();
	int					getScore();
	int					getLevel();
	int					getDifficult();
	char				**getMap();

private:
	//	Construct
	Game(const Game &src);
	//	Copy
	Game&				operator=(const Game &src);

};

#endif

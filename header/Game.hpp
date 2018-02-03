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

# define SNAKE_LENGTH		4

//	Defines for map filling 
# define EMPTY				0
# define SNAKE_BODY			1
# define SNAKE_HEAD			2
# define WALL				3
# define APPLE				4

# define MAX_HEIGHT			101
# define MAX_WIDTH			101
# define SCORE_HEIGHT		4
# define BORDERS			2


# include <regex>
# include <vector>
# include <string>
# include <iostream>

# include <fstream>

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
	//	Map information
	char	**_map;
	int		_width;
	int		_height;

	//	Information about game
	int		_score;
	int		_level;
	int		_difficult;

	//	Type of visualisation
	Visual	_visual_type;

	//	Next coord for piece(snake body). Can have any integer
	int		_next_x;
	int 	_next_y;

	//	Where move snake head at the moment(). Can have -1 0 1
	int		_head_move_x;
	int		_head_move_y;

	//	Snake
	std::vector<Piece *>	_snake;

public:

	//	Construct
	Game();
	Game(int width, int height);

	//	Destruct
	~Game();

	int					putSnakeOnMap();
	void				putWallsOnMap();
	void				putAppleOnMap();
	void				addPieceToSnake();
	void				moveSnakeBody();

	void				setHeadMoveXY(int x, int y);


	void 				cleanMapFromSnake();
	void				runGame();

	int					getWidth();
	int					getHeight();
	int					getScore();
	int					getLevel();
	int					getDifficult();
	char				**getMap();

	void				printMap();

private:
	//	Construct
	Game(const Game &src);
	//	Copy
	Game&				operator=(const Game &src);

};


void		n_curses_visual(Game *g);

#endif

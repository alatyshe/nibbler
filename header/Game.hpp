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

# define PLAY				0
# define RESET_GAME			1
# define GAME_OVER			2
# define MAIN_MENU			3
# define PAUSE_MENU			4
# define SMALL_SCREEN		5
# define EXIT				6

# define SNAKE_LENGTH		4

//	Defines for map fill
# define EMPTY				0
# define SNAKE_BODY			1
# define SNAKE_HEAD			2
# define WALL				3
# define APPLE				4

//	Defines for map sizes
# define MAX_HEIGHT			101
# define MAX_WIDTH			101
# define MIN_HEIGHT			20
# define MIN_WIDTH			20
# define SCORE_HEIGHT		4
# define BORDERS			2


//	ReadInput KEYS
# define UP					1
# define LEFT				2
# define RIGHT				3
# define DOWN				4

# define NCURSES 			5
# define QT					6
# define SDL2				7

# define MENU				8
# define RETURN				9
// # define SFML				6
// # define GLFW				7




# include <regex>
# include <vector>
# include <string>
# include <iostream>

# include <fstream>

// SLEEP
# include <chrono>
# include <thread>
extern "C" {
	# include <ncurses.h>
	# include <dlfcn.h>
}

# include "../header/Piece.hpp"

class IVisual;

typedef struct	s_info {
	//	Map information
	char	**map;
	int		width;
	int		height;

	//	Information about game
	int		score;
	int		level;
	int		difficult;

	int		library;
	int		status;
}				t_info;

class Game {

protected:

	//	Visual
	void	*_handle;		//	Указатель на открытую либу
	IVisual *_visual;		//	сам движок визуализации
	t_info	*_info;			//	вся инфа о карте и прочего для отображения внизу


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

	//	Map
	void				createMap();
	void 				createSnake();
	//	Snake
	void				putSnakeOnMap();
	void				moveSnakeBody();
	void 				cleanMapFromSnake();
	//	Apple
	void				createFruit();
	void				addPieceToSnake();
	//	Keys
	void				keyParser(int key);
	//	Library
	void				libManipulation(int library);
	//	Main func
	void				runGame();
	//	Getters
	t_info				*getInfo();

private:
	//	Construct
	Game(const Game &src);
	//	Copy
	Game&				operator=(const Game &src);

};

# include "../header/IVisual.hpp"

#endif

#ifndef NCURSES_CLASS_HPP
# define NCURSES_CLASS_HPP

# include "../../header/Game.hpp"
# include <ncurses.h>


extern "C" class Ncurses
{
public:
	Ncurses();
	~Ncurses();
	Ncurses(Game *g);
	
	// void	Setup(WINDOW *screen, WINDOW *score);
	void	Input(Game *g);
	void	Map(Game *g);
	// void	Map(Game *g);
	void	Score(Game *g);
	void	MainMenu(Game *g);
	void	PauseMenu(Game *g);
	void	GameOver(Game *g);
	void	SmallScreen(Game *g);
	void	n_curses_visual(Game *g, int game_over);

private:
	WINDOW	*screen;
	WINDOW	*score;
};

#endif

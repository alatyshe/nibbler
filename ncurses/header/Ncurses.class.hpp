#ifndef NCURSES_CLASS_HPP
# define NCURSES_CLASS_HPP

# include <ncurses.h>

# include "../../header/Game.hpp"
# include "../../header/IVisual.hpp"

class Game;
class IVisual;

extern "C" class Ncurses: public IVisual {
public:
	Ncurses();
	~Ncurses();
	Ncurses(Game *g);

	//	ReadInput	
	void	Input(Game *g);
	//	Display Game
	void	Map(Game *g);
	void	Score(Game *g);
	//	Display	Other
	void	MainMenu(Game *g);
	void	PauseMenu(Game *g);
	void	GameOver(Game *g);
	void	SmallScreen(Game *g);

	void	Visual(Game *g, int game_over);

private:
	WINDOW	*screen;
	WINDOW	*score;
};

extern "C" IVisual* NewVisual(Game *g);
extern "C" void DeleteVisual(IVisual* instance);

#endif

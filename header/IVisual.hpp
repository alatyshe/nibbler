#ifndef IVISUAL_H
# define IVISUAL_H

# include "Game.hpp"

class Game;

class IVisual {

public:
	


	//	ReadInput
	virtual void	Input(Game *g) = 0;
	//	Display Game
	virtual void	Map(Game *g) = 0;
	virtual void	Score(Game *g) = 0;
	//	Display	Other
	virtual void	MainMenu(Game *g) = 0;
	virtual void	PauseMenu(Game *g) = 0;
	virtual void	GameOver(Game *g) = 0;
	virtual void	SmallScreen(Game *g) = 0;
	//	MainVisual
	virtual	void	Visual(Game *g, int game_over) = 0;

	virtual ~IVisual( void ) { ; };
};

#endif

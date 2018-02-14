#ifndef NCURSES_CLASS_HPP
# define NCURSES_CLASS_HPP

# include <ncurses.h>

# include "../../header/IVisual.hpp"

class Game;
class IVisual;

class Ncurses: public IVisual {
public:
	Ncurses();
	~Ncurses();
	Ncurses(t_info *info);

	void	PrintBorders(t_info *info);
	//	ReadInput	
	int		ReadInput();
	//	Display Game
	void	Map(t_info *info);
	void	Score(t_info *info);
	//	Display	Menu
	void	MainMenu(t_info *info);
	void	PauseMenu(t_info *info);
	void	GameOverMenu(t_info *info);
	//	Screens
	void	GameOverScreen(t_info *info);
	int		SmallScreen(t_info *info);
	//	Main func
	int		Visual(t_info *info);

private:
	WINDOW	*screen;
	WINDOW	*score;
};

extern "C" IVisual* NewVisual(t_info *info);
extern "C" void DeleteVisual(IVisual* instance);

#endif

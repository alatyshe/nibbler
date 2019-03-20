# pragma once

# include <ncurses.h>
# include "../abstract/IVisual.hpp"

class Game;
class IVisual;

class ncurses_lib: public IVisual {
public:
  ncurses_lib() = delete;
  ~ncurses_lib();
  ncurses_lib(t_info *info);
  ncurses_lib& operator=(ncurses_lib const&) = delete;

  //  ReadInput 
  int   ReadInput();
  //  Display Game
  void  Map(t_info *info);
  void  Score(t_info *info);
  //  Display Menu
  void  MainMenu(t_info *info);
  void  PauseMenu(t_info *info);
  void  GameOverMenu(t_info *info);
  //  Main func
  int   Visual(t_info *info);

private:
  //  Screens
  int   SmallScreen(t_info *info);
  void  PrintBorders(t_info *info);

  WINDOW  *screen;
  WINDOW  *score;
};

extern "C" IVisual* NewVisual(t_info *info);
extern "C" void   DeleteVisual(IVisual* instance);

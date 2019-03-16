# pragma once

# include "../nibbler_core/header/Info.hpp"

class Game;

class IVisual {

public:
  //  ReadInput
  virtual int   ReadInput() = 0;
  //  Display Game
  virtual void  Map(t_info *info) = 0;
  virtual void  Score(t_info *info) = 0;
  //  Display Menu
  virtual void  MainMenu(t_info *info) = 0;
  virtual void  PauseMenu(t_info *info) = 0;
  virtual void  GameOverMenu(t_info *info) = 0;
  //  MainVisual
  virtual int   Visual(t_info *info) = 0;

  virtual ~IVisual( void ) { ; };
};

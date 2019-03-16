#pragma once

#include <SFML/Graphics.hpp>
// #include <SFML/Graphics/Color.hpp>

# include "../abstract/IVisual.hpp"

#define CELL_SIZE   35

class Game;
class IVisual;

class sfml_lib: public IVisual {
public:
  sfml_lib() = delete;
  sfml_lib(t_info *info);
  ~sfml_lib();
  sfml_lib& operator=(sfml_lib const&) = delete;
  

  void  PrintBorders(t_info *info);
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
  sf::RenderWindow *window;
  sf::Font font;
  int status;
};

extern "C" IVisual* NewVisual(t_info *info);
extern "C" void   DeleteVisual(IVisual* instance);

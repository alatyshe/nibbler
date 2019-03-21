#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>

# include "../abstract/IVisual.hpp"

#define CELL_SIZE   30

class Game;
class IVisual;

class sdl_lib: public IVisual {
public:
  sdl_lib() = delete;
  sdl_lib(t_info *info);
  ~sdl_lib();
  sdl_lib& operator=(sdl_lib const&) = delete;
  

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
  TTF_Font      *font_head;
  TTF_Font      *font_menu;
  SDL_Window    *window;
  SDL_Renderer  *renderer;
};

extern "C" IVisual* NewVisual(t_info *info);
extern "C" void   DeleteVisual(IVisual* instance);
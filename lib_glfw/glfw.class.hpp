#pragma once

#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include FT_FREETYPE_H

# include "../abstract/IVisual.hpp"

#define CELL_SIZE   30

class glfw_lib: public IVisual {
public:
  glfw_lib();

  ~glfw_lib();
  glfw_lib(t_info *info);
  
  //  ReadInput 
  int   ReadInput();
  //  Display Game
  void  Map(t_info *info);
  void  Score(t_info *info);
  //  Display Menu
  void  MainMenu(t_info *info);
  void  PauseMenu(t_info *info);
  void  GameOverMenu(t_info *info);
  //  Screens
  void  GameOverScreen(t_info *info);
  //  Main func
  int   Visual(t_info *info);


private:
  glfw_lib& operator=(glfw_lib const&) = delete;
  glfw_lib(glfw_lib const & src) = delete;

  GLFWwindow  *window_;
  FTFont      *font_;
  void        DrawSquare(int x, int y);

};

extern "C" IVisual* NewVisual(t_info *info);
extern "C" void DeleteVisual(IVisual* instance);

#pragma once

#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H

# include "../abstract/IVisual.hpp"

#define CELL_SIZE   14

class Glfw: public IVisual {
public:
  Glfw();
  ~Glfw();
  Glfw(t_info *info);

  // void PrintText(t_info *info, const char x, int y);
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
  GLFWwindow* window_;
  void        DrawBackground(t_info *info);
  void        DrawSquare(int x, int y);

};

extern "C" IVisual* NewVisual(t_info *info);
extern "C" void DeleteVisual(IVisual* instance);

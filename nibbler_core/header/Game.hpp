#pragma once

# include <vector>
# include <string>

extern "C" {
  # include <ncurses.h>
  # include <dlfcn.h>
}

# include "Info.hpp"
# include "Piece.hpp"
# include "Exception.hpp"
# include "../../abstract/IVisual.hpp"


class Game {

protected:

  //  Visual
  void      *_handle;   //  Указатель на открытую либу
  IVisual   *_visual;   //  сам движок визуализации
  t_info    *_info;     //  вся инфа о карте и прочего для отображения 
                //  внизу карты

  // INFO FOR SNAKE
  //  Next coord for piece(snake body). Can have any integer
  int   _next_x;
  int   _next_y;
  //  Where move snake head at the moment(). Can have -1 0 1
  int   _head_move_x;
  int   _head_move_y;
  //  Snake
  std::vector<std::unique_ptr<Piece>> _snake;

public:

  //  Construct
  Game();
  Game(int width, int height);

  //  Destruct
  ~Game();

  //  Map
  void        resetGame();
  //  Snake
  void        putSnakeOnMap();
  void        moveSnakeBody();
  void        cleanMapFromSnake();
  //  Apple
  void        putFruitOnMap();
  //  Keys
  void        parseKeyInput(int key);
  //  Library
  void        libManipulation(int library);
  //  Main func
  void        MainLoop();
  //  Getters
  t_info        *getInfo();

private:
  //  Construct
  Game(const Game &src);
  //  Copy
  Game&       operator=(const Game &src);

};

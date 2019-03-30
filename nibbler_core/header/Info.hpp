#pragma once

// SLEEP
# include <chrono>
# include <iostream>
# include <thread>

# include <regex>

# define RED          "\x1b[31m"
# define GREEN        "\x1b[32m"
# define YELLOW       "\x1b[33m"
# define BLUE         "\x1b[34m"
# define MAGENTA      "\x1b[35m"
# define CYAN         "\x1b[36m"
# define BLACK        "\x1b[37m"
# define RESET        "\x1b[0m"

# define INTEGER      "([1-9][0-9]+)"

# define PLAY           0
# define RESET_GAME     1
# define GAME_OVER      2
# define MAIN_MENU      3
# define PAUSE_MENU     4
# define SMALL_SCREEN   5
# define EXIT           6

# define SNAKE_LENGTH   4

//  Defines for map fill
# define EMPTY        0
# define SNAKE_BODY   1
# define SNAKE_HEAD   2
# define WALL         3
# define APPLE        4

//  Defines for map sizes
# define MAX_SIZE     70
# define MIN_SIZE     20

# define SCORE_HEIGHT 4
# define BORDERS      2

//  ReadInput KEYS
# define UP           259
# define LEFT         260
# define RIGHT        261
# define DOWN         258

# define SFML         49
# define SDL2         50
# define GLFW         51

# define ESC          27
# define ENTER        10
# define MENU         113


typedef struct s_piece
{
  int   x;
  int   y;
}       t_piece;

typedef struct  s_info {
  //  Map information
  std::vector<std::vector<int> > map;
  int   width;
  int   height;

  //  Information about game
  int   score;
  int   level;
  int   difficult;

  int   curr_lib;
  int   status;
  int   menu_pos;
}       t_info;

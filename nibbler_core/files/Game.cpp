# include "../header/Game.hpp"

Game::Game() { ; }
Game::~Game() { ; }

Game::Game(int width, int height) {
  //  Information about game
  _info = new t_info();
  for (int i = 0; i < height; i++) {
      _info->map.push_back(std::vector<int>(width, 0));
  }
  _info->width = width;
  _info->height = height;

  _info->score = 0;
  _info->level = 2;
  _info->difficult = 1;

  _info->curr_lib = NCURSES;
  _info->status = MAIN_MENU;
  _info->menu_pos = 1;

  //  Type of visualisation
  _visual = NULL;
  _handle = NULL;
}

t_info      *Game::getInfo() {
  return(_info);
}

void        Game::resetGame() {
  int     total_walls;
  int     y;
  int     x;

  // Reset map
  for (int i = 0; i < _info->height; i++) {
    std::fill(_info->map[i].begin(), _info->map[i].end(), 0);
  }

  //  Fill Map
  srand(time(NULL));
  total_walls = _info->width * _info->height / 100 * _info->difficult;
  for (; total_walls > 0; total_walls--) {
    x = rand() % _info->width;
    y = rand() % _info->height;
    if (y != _info->height / 2 && _info->map[y][x] != WALL)
      _info->map[y][x] = WALL;
  }

  _snake.clear();
  for (int i = 0; i < SNAKE_LENGTH; i++)
    _snake.emplace_back(new Piece(_info->width / 2 + i - 3, _info->height / 2));
  _head_move_x = 1; // 1(right) or 0(middle) or -1(left)
  _head_move_y = 0; // 1(up) or 0(middle) or -1(down)

  putSnakeOnMap();

  putFruitOnMap();
}

void        Game::putFruitOnMap() {
  int     x;
  int     y;

  while (true) {
    x = rand() % (_info->width  - 1);
    y = rand() % (_info->height - 1);
    if (_info->map[y][x] != WALL
        && x > 1 && y > 1) {
      _info->map[y][x] = APPLE;
      break;
    }
  }
}

void        Game::putSnakeOnMap() {
  int         x;
  int         y;
  bool        apple;

  apple = false;
  for(auto &i : _snake) {

    x = i->GetX();
    y = i->GetY();

    if (x < 0 || y < 0 
        || x >= _info->width 
        || y >= _info->height) {
      _info->status = GAME_OVER;
    } else if (_info->map[y][x] == SNAKE_BODY
        || _info->map[y][x] == WALL) {
      _info->status = GAME_OVER;
    } else if (_info->map[y][x] == APPLE) {
      _info->map[y][x] = SNAKE_HEAD;
      apple = true;
    } else {
      if (i == _snake.front())
        _info->map[y][x] = SNAKE_HEAD;
      else
        _info->map[y][x] = SNAKE_BODY;
    }
  }

  if (apple) {
    _info->score += 100;
    putFruitOnMap();
    _snake.emplace_back(new Piece());
  }
}

void        Game::moveSnakeBody() {
  int         x;
  int         y;
  int         next_x;
  int         next_y;

  for(auto &i : _snake) {
    x = i->GetX();
    y = i->GetY();
    if (i == _snake.front()) {
      i->SetX(x - _head_move_x);
      i->SetY(y - _head_move_y);
    } else {
      i->SetX(next_x);
      i->SetY(next_y);
    }
    next_x = x;
    next_y = y;
  }
}

void        Game::cleanMapFromSnake() {
  for (int i = 0; i < _info->height; i++) {
    for (int j = 0; j < _info->width; j++) {
      if (_info->map[i][j] == SNAKE_BODY
          || _info->map[i][j] == SNAKE_HEAD) {
        _info->map[i][j] = EMPTY;
      }
    }
  }
}

void        Game::parseKeyInput(int key) {
  if (key == ESC)
    libManipulation(EXIT);

  if (_info->status == MAIN_MENU 
      || _info->status == PAUSE_MENU 
      || _info->status == GAME_OVER) {
    if (key == UP && _info->menu_pos > 1)
      _info->menu_pos--;
    else if ((_info->status == PAUSE_MENU && key == DOWN && _info->menu_pos < 2)
        || (_info->status == GAME_OVER && key == DOWN && _info->menu_pos < 2)
        || (_info->status == MAIN_MENU && key == DOWN && _info->menu_pos < 3))
      _info->menu_pos++;
    else if (_info->status == MAIN_MENU && key == ENTER) {
        if (_info->menu_pos == 1)
          _info->status = PLAY;
        else if (_info->menu_pos == 2)
          ;// info->status = ;
        else
          libManipulation(EXIT);
        _info->menu_pos = 1;
    }
    else if ((_info->status == PAUSE_MENU || _info->status == GAME_OVER)
        && key == ENTER) {
      if (_info->menu_pos == 1)
        _info->status = PLAY;
      else if (_info->menu_pos == 2)
        _info->status = MAIN_MENU;
      _info->menu_pos = 1;
    }
  }
  else if (key == LEFT || key == RIGHT) {
    if (_head_move_x == 0) {
      if (key == LEFT)
        _head_move_x = 1;
      else if (key == RIGHT)
        _head_move_x = -1;
      _head_move_y = 0;
    }
  } else if (key == UP || key == DOWN) {
    if (_head_move_y == 0) {
      if (key == UP)
        _head_move_y = 1;
      else if (key == DOWN)
        _head_move_y = -1;
      _head_move_x = 0;
    }
  }
  if (key == NCURSES && _info->curr_lib != NCURSES) {
    libManipulation(NCURSES);
  } else if (key == SFML && _info->curr_lib != SFML) {
    libManipulation(SFML);
  } else if (key == SDL2 && _info->curr_lib != SDL2) {
    libManipulation(SDL2);
  } else if (key == MENU && _info->status != MAIN_MENU && _info->status != GAME_OVER) {
    _info->status = PAUSE_MENU;
  }
}

void        Game::libManipulation(int library) {
  IVisual*    (*new_instanse)(t_info *g);         //  указатель на функцию
  void        (*del_instance)(IVisual* instance); //  указатель на функцию

  if (_handle) {
    *(void **) (&del_instance) = dlsym(_handle, "DeleteVisual");
    (*del_instance)(this->_visual);
    dlclose(_handle);
    _visual = NULL;
    _handle = NULL;
  }

  if (library == NCURSES) {
    _handle = dlopen("./lib/libncurses_lib.dylib", RTLD_LAZY);
  } else if (library == SFML) {
    _handle = dlopen("./lib/libsfml_lib.dylib", RTLD_LAZY);
  } else if (library == SDL2) {
    _handle = dlopen("./lib/libsdl2.dylib", RTLD_LAZY);
    // _handle = dlopen("./lib/libsdl2.dylib", RTLD_LAZY);
  } else if (library == EXIT) {
    if (_info) {
      for (int i = 0; i < _info->height; i++)
        _info->map[i].clear();
      _snake.clear();
      delete _info;
    }
    exit(0);
  }
  
  if (!_handle) {
    throw Exception("Missed Library");
  }

  _info->curr_lib = library;
  *(void **) (&new_instanse) = dlsym(_handle, "NewVisual");
  _visual = (*new_instanse)(_info);
  if (_info->status == PLAY)
    _info->status = PAUSE_MENU;
}

void        Game::MainLoop()
{
  int     key_input;

  libManipulation(SFML);
  resetGame();
  _info->status = PLAY;
  while(true) {       
    // Отображаем доску
    key_input = _visual->Visual(_info);
    parseKeyInput(key_input);
    if (_info->status == GAME_OVER 
        || _info->status == MAIN_MENU) {
      resetGame();
    } else if (_info->status == PLAY) {
      cleanMapFromSnake();
      moveSnakeBody();
      putSnakeOnMap();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(260/2));
  }
}




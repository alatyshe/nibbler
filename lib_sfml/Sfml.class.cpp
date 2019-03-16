#include "Sfml.class.hpp"

IVisual*    NewVisual(t_info *info) { 
  // Создаем экземпляр нашей визуализации и возвращаем
  return new sfml_lib(info); 
}

void      DeleteVisual(IVisual* instance){
  // закрываем все что связанно с визуализацией и удаляем экземпляр
  delete instance;
}


sfml_lib::~sfml_lib(void) {
  this->window->close();
}

sfml_lib::sfml_lib(t_info *info) {
  int     board_height; 
  int     board_width;
  int     score_height;

  board_height = info->height * CELL_SIZE + BORDERS * 20;
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;

  this->status = info->status;
  this->window = new sf::RenderWindow(sf::VideoMode(board_width, board_height + score_height), "Nibbler!");
  if (!this->window){
    exit(0);
  }
  if (!this->font.loadFromFile("./lib_sfml/roboto.regular.ttf")) {
    exit(0);
  }

}

int       sfml_lib::ReadInput() {
  int key_;

  key_ = -1;
  sf::Event event;
  while (this->window->pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      key_ = ESC;
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape)
        key_ = ESC;
      if (event.key.code == sf::Keyboard::Q)
        key_ = MENU;
      if (event.key.code == sf::Keyboard::Return)
        key_ = ENTER;
      if (event.key.code == sf::Keyboard::Left) {
        if (this->status != PLAY)
          key_= LEFT;
        else        
          key_ = UP;
      }
      if (event.key.code == sf::Keyboard::Right) {
        if (this->status != PLAY)
          key_= RIGHT;
        else
          key_ = DOWN;
      }
      if (event.key.code == sf::Keyboard::Up) {
        if (this->status != PLAY)
          key_= UP;
        else
          key_ = LEFT;
      }
      if (event.key.code == sf::Keyboard::Down){
        if (this->status != PLAY)
          key_= DOWN;
        else
          key_ = RIGHT;
      }

      if (event.key.code == sf::Keyboard::Num1)
        key_ = NCURSES;
      if (event.key.code == sf::Keyboard::Num2)
        key_ = SFML;
      if (event.key.code == sf::Keyboard::Num3)
        key_ = SDL2;
    }
    else
      break;
  }
  return key_;
}

void      sfml_lib::Map(t_info *info) {
  int border;
 
  border = BORDERS * 20 / 2;
  sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));
  for (int y = 0; y < info->height; y++) {
    for (int x = 0; x < info->width; x++) {
      box.setPosition(y * CELL_SIZE + border, x * CELL_SIZE + border);
      if (info->map[y][x] == SNAKE_BODY) {
        box.setFillColor(sf::Color(134,160,78));
      } else if (info->map[y][x] == SNAKE_HEAD) {
        box.setFillColor(sf::Color(49, 72, 10));
      } else if (info->map[y][x] == WALL) {
        box.setFillColor(sf::Color(95,50,45));
      } else if (info->map[y][x] == APPLE) {
        box.setFillColor(sf::Color(230,27,35));
      } else {
        box.setFillColor(sf::Color(255,255,255));
      }
      this->window->draw(box);
    }
  }
}

void      sfml_lib::Score(t_info *info) {
  sf::Text text;
  int board_height;
  int board_width;
  int score_height;
  std::string to_display;
  int y;
  int x;

  board_height = (info->height * CELL_SIZE + BORDERS * 20);
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;
  y = board_height + 10;
  // select the font
  text.setFont(this->font); // font is a sf::Font
  
  to_display = "Score\t\t: " + std::to_string(info->score);
  text.setString(to_display);
  text.setCharacterSize(30); // in pixels, not points!
  text.setFillColor(sf::Color(255,255,255));
  text.setStyle(sf::Text::Bold);
  text.setPosition(50, y);
  this->window->draw(text);

  to_display = "Level\t\t : " + std::to_string(info->level);
  text.setString(to_display);
  text.setCharacterSize(30); // in pixels, not points!
  text.setFillColor(sf::Color(255,255,255));
  text.setStyle(sf::Text::Bold);
  text.setPosition(50, y + 35);
  this->window->draw(text);

  to_display = "Difficult\t: " + std::to_string(info->difficult);
  text.setString(to_display);
  text.setCharacterSize(30); // in pixels, not points!
  text.setFillColor(sf::Color(255,255,255));
  text.setStyle(sf::Text::Bold);
  text.setPosition(50, y + 70);
  this->window->draw(text);
}


void      sfml_lib::MainMenu(t_info *info) {
  sf::Text text;
  int board_height;
  int board_width;
  int score_height;
  int y;
  int x;


  board_height = (info->height * CELL_SIZE + BORDERS * 20);
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;
  y = (board_height) / 2;
  x = board_width / 3;
  // select the font
  text.setFont(this->font); // font is a sf::Font
  
  text.setString("MAIN MENU");
  text.setCharacterSize(35); // in pixels, not points!
  text.setFillColor(sf::Color(255, 138, 0));
  text.setStyle(sf::Text::Bold);
  text.setPosition(x, y);
  this->window->draw(text);

  text.setString("Single Game");
  text.setCharacterSize(30); // in pixels, not points!
  if (info->menu_pos == 1){
    text.setFillColor(sf::Color(134,160,78));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Bold);
  }
  else {
    text.setFillColor(sf::Color(255,255,255));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Regular);
  }
  text.setPosition(x, y + 45);
  this->window->draw(text);

  text.setString("Player vs Player");
  text.setCharacterSize(30); // in pixels, not points!
  if (info->menu_pos == 2) {
    text.setFillColor(sf::Color(134,160,78));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Bold);
  }
  else {
    text.setFillColor(sf::Color(255,255,255));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Regular);
  }
  text.setPosition(x, y + 80);
  this->window->draw(text);

  text.setString("Exit");
  text.setCharacterSize(30); // in pixels, not points!
  if (info->menu_pos == 3) {
    text.setFillColor(sf::Color(134,160,78));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Bold);
  }
  else {
    text.setFillColor(sf::Color(255,255,255));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Regular);
  }
  text.setPosition(x, y + 110);
  this->window->draw(text);
}

void      sfml_lib::PauseMenu(t_info *info) {
  sf::Text text;
  int board_height;
  int board_width;
  int score_height;
  int y;
  int x;


  board_height = (info->height * CELL_SIZE + BORDERS * 20);
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;
  y = (board_height) / 2;
  x = board_width / 3;
  // select the font
  text.setFont(this->font); // font is a sf::Font

  text.setString("PAUSE MENU");
  text.setCharacterSize(35); // in pixels, not points!
  text.setFillColor(sf::Color(255, 138, 0));
  text.setStyle(sf::Text::Bold);
  text.setPosition(x, y);
  this->window->draw(text);

  text.setString("Continue");
  text.setCharacterSize(30); // in pixels, not points!
  if (info->menu_pos == 1){
    text.setFillColor(sf::Color(134,160,78));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Bold);
  }
  else {
    text.setFillColor(sf::Color(255,255,255));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Regular);
  }
  text.setPosition(x, y + 45);
  this->window->draw(text);

  text.setString("Main Menu");
  text.setCharacterSize(30); // in pixels, not points!  
  if (info->menu_pos == 2) {
    text.setFillColor(sf::Color(134,160,78));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Bold);
  }
  else {
    text.setFillColor(sf::Color(255,255,255));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Regular);
  }
  text.setPosition(x, y + 80);
  this->window->draw(text);
}

void      sfml_lib::GameOverMenu(t_info *info) {
  sf::Text text;
  int board_height;
  int board_width;
  int score_height;
  int y;
  int x;


  board_height = (info->height * CELL_SIZE + BORDERS * 20);
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;
  y = (board_height) / 2;
  x = board_width / 3;
  // select the font
  text.setFont(this->font); // font is a sf::Font
  text.setString("Game Over");
  text.setCharacterSize(35); // in pixels, not points!
  text.setFillColor(sf::Color(255, 138, 0));
  text.setStyle(sf::Text::Bold);
  text.setPosition(x, y);
  this->window->draw(text);

  text.setString("Reset");
  text.setCharacterSize(30); // in pixels, not points!
  if (info->menu_pos == 1){
    text.setFillColor(sf::Color(134,160,78));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Bold);
  }
  else {
    text.setFillColor(sf::Color(255,255,255));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Regular);
  }
  text.setPosition(x, y + 45);
  this->window->draw(text);

  text.setString("Main Menu");
  text.setCharacterSize(30); // in pixels, not points!
  
  if (info->menu_pos == 2) {
    text.setFillColor(sf::Color(134,160,78));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Bold);
  }
  else {
    text.setFillColor(sf::Color(255,255,255));
    text.setCharacterSize(30); // in pixels, not points!
    text.setStyle(sf::Text::Regular);
  }
  text.setPosition(x, y + 80);
  this->window->draw(text);
}


int       sfml_lib::Visual(t_info *info) {
  
  this->window->clear();
  this->status = info->status;

  if (info->status == PAUSE_MENU) {
    this->PauseMenu(info);
  } else if (info->status == GAME_OVER) {
    this->GameOverMenu(info);
  } else if (info->status == MAIN_MENU) {
    this->MainMenu(info);
  } else if (info->status == PLAY) {
    // printf("YEAH\n");
    this->Map(info);
    this->Score(info);
  }
  this->window->display();
  return this->ReadInput();
}


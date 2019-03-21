#include "sdl.class.hpp"

IVisual*  NewVisual(t_info *info) { return new sdl_lib(info); }
void      DeleteVisual(IVisual* instance){ delete instance;}


sdl_lib::~sdl_lib(void) {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  TTF_CloseFont(this->font_head);
  TTF_CloseFont(this->font_menu);
  TTF_Quit();
  SDL_Quit();
}

sdl_lib::sdl_lib(t_info *info) {
  int     board_height; 
  int     board_width;
  int     score_height;

  board_height = info->height * CELL_SIZE + BORDERS * 20;
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    std::cout << "Failed to initialize SDL : " << SDL_GetError() << std::endl;
    exit(0);
  }
  if (TTF_Init() == -1) {
    std::cout << "Failed to initialize TTF" << std::endl;
    exit(0);
  }
  
  this->window = SDL_CreateWindow("SDL Nibbler", 100, 100, board_width, board_height + score_height, 0);
  if (this->window == nullptr) {
    std::cout << "Failed to create window : " << SDL_GetError();
    exit(0);
  }

  this->font_head = TTF_OpenFont("./lib_sdl/roboto.regular.ttf", 24);
  this->font_menu = TTF_OpenFont("./lib_sdl/roboto.regular.ttf", 20);
  if (this->font_head == nullptr || this->font_menu == nullptr) {
    std::cout << "Missed font : " << std::endl;
    exit(0);
  }

  this->renderer = SDL_CreateRenderer(this->window, -1, 0);
  if (this->renderer == nullptr) {
    std::cout << "Failed to create renderer : " << SDL_GetError();
    exit(0);
  }

  // Set size of renderer to the same as window
  SDL_RenderSetLogicalSize(this->renderer, board_width, board_height + score_height);
  // Set color of renderer to black
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
  // put focus on current window
  SDL_RaiseWindow(this->window);
}

int       sdl_lib::ReadInput() {
  int key_;

  key_ = -1;
  SDL_Event event;

  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT) {
    key_ = ESC;
  } else if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_ESCAPE)
      key_ = ESC;
    else if (event.key.keysym.sym == SDLK_q)
      key_ = MENU;
    else if (event.key.keysym.sym == SDLK_RETURN)
      key_ = ENTER;
    else if (event.key.keysym.sym == SDLK_LEFT)
      key_= LEFT;
    else if (event.key.keysym.sym == SDLK_RIGHT)
      key_= RIGHT;
    else if (event.key.keysym.sym == SDLK_UP)
      key_= UP;
    else if (event.key.keysym.sym == SDLK_DOWN)
      key_= DOWN;


    else if (event.key.keysym.sym == SDLK_1)
      key_ = NCURSES;
    else if (event.key.keysym.sym == SDLK_2)
      key_ = SFML;
    else if (event.key.keysym.sym == SDLK_3)
      key_ = SDL2;
    else if (event.key.keysym.sym == SDLK_4)
      key_ = GLFW;
  }
  return key_;
}

void      sdl_lib::Map(t_info *info) {
  int border;
  SDL_Rect playerPos;
 
  
  playerPos.x = 0;
  playerPos.y = 0;
  playerPos.w = CELL_SIZE - 3;
  playerPos.h = CELL_SIZE - 3;
 
  border = BORDERS * 20 / 2;
  for (int y = 0; y < info->height; y++) {
    for (int x = 0; x < info->width; x++) {
      playerPos.x = x * CELL_SIZE + border;
      playerPos.y = y * CELL_SIZE + border;

      if (info->map[y][x] == SNAKE_BODY) {
        SDL_SetRenderDrawColor(renderer,134, 160, 78, 255);
      } else if (info->map[y][x] == SNAKE_HEAD) {
        SDL_SetRenderDrawColor(renderer,49, 72,  10, 255);
      } else if (info->map[y][x] == WALL) {
        SDL_SetRenderDrawColor(renderer,95, 50, 45, 255);
      } else if (info->map[y][x] == APPLE) {
        SDL_SetRenderDrawColor(renderer,230, 27, 35, 255);
      } else {
        SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);
      }
      SDL_RenderFillRect(renderer, &playerPos);
    }
  }
}

void      sdl_lib::Score(t_info *info) {
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect dstrect;
  std::string to_display;
  int board_height;
  int board_width;
  int score_height;
  int texW = 0;
  int texH = 0;
  int y;

  board_height = (info->height * CELL_SIZE + BORDERS * 20);
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;
  y = board_height + 10;
  
  to_display = "Score\t\t: " + std::to_string(info->score);
  surface = TTF_RenderText_Solid(this->font_menu,
    to_display.c_str(), {255, 255, 255});
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {50, y, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  to_display = "Level\t\t : " + std::to_string(info->level);
  surface = TTF_RenderText_Solid(this->font_menu,
    to_display.c_str(), {255, 255, 255});
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {50, y + 35, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  to_display = "Difficult\t: " + std::to_string(info->difficult);
  surface = TTF_RenderText_Solid(this->font_menu,
    to_display.c_str(), {255, 255, 255});
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {50, y + 70, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}


void      sdl_lib::MainMenu(t_info *info) {
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect dstrect;
  int board_height;
  int board_width;
  int score_height;
  int texW = 0;
  int texH = 0;
  int y;
  int x;


  board_height = (info->height * CELL_SIZE + BORDERS * 20);
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;
  y = (board_height) / 2;
  x = board_width / 3;

  surface = TTF_RenderText_Solid(this->font_head,
    "MAIN MENU", {255, 138, 0});
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  if (info->menu_pos == 1){
    surface = TTF_RenderText_Solid(this->font_menu,
    "Single Game", {134, 160, 78});
  } else {
    surface = TTF_RenderText_Solid(this->font_menu,
    "Single Game", {255, 255, 255});
  }
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y + 45, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  if (info->menu_pos == 2){
    surface = TTF_RenderText_Solid(this->font_menu,
    "Player vs Player", {134, 160, 78});
  } else {
    surface = TTF_RenderText_Solid(this->font_menu,
    "Player vs Player", {255, 255, 255});
  }
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y + 80, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  
  if (info->menu_pos == 3){
    surface = TTF_RenderText_Solid(this->font_menu,
    "Exit", {134, 160, 78});
  } else {
    surface = TTF_RenderText_Solid(this->font_menu,
    "Exit", {255, 255, 255});
  }
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y + 110, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void      sdl_lib::PauseMenu(t_info *info) {
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect dstrect;
  int board_height;
  int board_width;
  int score_height;
  int texW = 0;
  int texH = 0;
  int y;
  int x;

  board_height = (info->height * CELL_SIZE + BORDERS * 20);
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;
  y = (board_height) / 2;
  x = board_width / 3;
  surface = TTF_RenderText_Solid(this->font_head,
    "PAUSE MENU", {255, 138, 0});
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  if (info->menu_pos == 1){
    surface = TTF_RenderText_Solid(this->font_menu,
    "Continue", {134, 160, 78});
  } else {
    surface = TTF_RenderText_Solid(this->font_menu,
    "Continue", {255, 255, 255});
  }
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y + 45, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  if (info->menu_pos == 2){
    surface = TTF_RenderText_Solid(this->font_menu,
    "Main Menu", {134, 160, 78});
  } else {
    surface = TTF_RenderText_Solid(this->font_menu,
    "Main Menu", {255, 255, 255});
  }
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y + 80, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void      sdl_lib::GameOverMenu(t_info *info) {
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect dstrect;
  int board_height;
  int board_width;
  int score_height;
  int texW = 0;
  int texH = 0;
  int y;
  int x;

  board_height = (info->height * CELL_SIZE + BORDERS * 20);
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  score_height = SCORE_HEIGHT * 50;
  y = (board_height) / 2;
  x = board_width / 3;
  surface = TTF_RenderText_Solid(this->font_head,
    "GAME OVER", {255, 138, 0});
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  if (info->menu_pos == 1){
    surface = TTF_RenderText_Solid(this->font_menu,
    "Reset", {134, 160, 78});
  } else {
    surface = TTF_RenderText_Solid(this->font_menu,
    "Reset", {255, 255, 255});
  }
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y + 45, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  if (info->menu_pos == 2){
    surface = TTF_RenderText_Solid(this->font_menu,
    "Main Menu", {134, 160, 78});
  } else {
    surface = TTF_RenderText_Solid(this->font_menu,
    "Main Menu", {255, 255, 255});
  }

  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  dstrect = {x, y + 80, texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}


int       sdl_lib::Visual(t_info *info) {

  SDL_RenderClear(renderer);

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
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderPresent(renderer);
  return this->ReadInput();
}


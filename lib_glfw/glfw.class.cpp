#include "glfw.class.hpp"

IVisual*        NewVisual(t_info *info) { return new glfw_lib(info); }
void            DeleteVisual(IVisual* instance){ delete instance; }

extern "C" {
  int             key_;

  void            KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)window;
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      key_ = ESC;
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
      key_ = MENU;

    else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
      key_ = ENTER;
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      key_ = LEFT;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      key_ = RIGHT;
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      key_ = DOWN;
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      key_ = UP;

    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
      key_ = NCURSES;
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
      key_ = SFML;
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
      key_ = SDL2;
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
      key_ = GLFW;
  }
}

glfw_lib::glfw_lib(void) { 
  return ; 
}

glfw_lib::~glfw_lib(void) { 
  glfwDestroyWindow(this->window_);
  glfwTerminate(); 
  delete this->font_;
}

glfw_lib::glfw_lib(t_info *info) {
  int     board_height; 
  int     board_width;
  int     score_height;


  board_height = info->height * CELL_SIZE + BORDERS * 10;
  board_width = info->width * CELL_SIZE + BORDERS * 10;
  score_height = SCORE_HEIGHT * 30;

  if(!glfwInit()) {
    exit(0);
  }
  this->window_ = glfwCreateWindow(board_width,
      board_height + score_height,
      "Nibbler GLFW", NULL, NULL );
  if (!this->window_) {
    glfwTerminate();
    exit(0);
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwMakeContextCurrent(this->window_);
  // set up view
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
  glOrtho(0.0,
    board_width,
    0.0,
    board_height + score_height,
    0.0,
    1.0); // this creates a canvas you can do 2D drawing on
  glfwSetKeyCallback(window_, &KeyCallback);

  // Font
  this->font_ = new FTGLPixmapFont("./lib_glfw/roboto.regular.ttf");
  if(this->font_->Error()) {
    std::cout << "font file missed\n";
    exit(0);
  }
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int             glfw_lib::ReadInput() {
  return -1;
}

void            glfw_lib::Map(t_info *info) {
  // DrawBackground(info);

  for (int y = 0; y < info->height; y++) {
    for (int x = 0; x < info->width; x++) {
      if (info->map[y][x] == SNAKE_BODY) {
        glColor3f(0.0f, 0.80f, 0.0f);
        DrawSquare(x, y);
      } else if (info->map[y][x] == SNAKE_HEAD) {
        glColor3f(0.0f, 1.0f, 0.0f);
        DrawSquare(x, y);
      } else if (info->map[y][x] == WALL) {
        glColor3f(0.2f, 0.2f, 0.2f);
        DrawSquare(x, y);
      } else if (info->map[y][x] == APPLE) {
        glColor3f(0.9f, 0.1f, 0.1f);
        DrawSquare(x, y);
      } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        DrawSquare(x, y);
      }
    }
  }

  return ;
}

void            glfw_lib::Score(t_info *info) {
  std::string to_display;
  int y; 

  y = 0;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
  font_->FaceSize(20);

  to_display = "Score\t\t: " + std::to_string(info->score);
  glColor3f(1, 1, 1);
  glRasterPos2f(50, y + 30);
  font_->Render(to_display.c_str());

  to_display = "Level\t\t : " + std::to_string(info->level);
  glColor3f(1, 1, 1);
  glRasterPos2f(50, y + 60);
  font_->Render(to_display.c_str());

  to_display = "Difficult\t: " + std::to_string(info->difficult);
  glColor3f(1, 1, 1);
  glRasterPos2f(50, y + 90);
  font_->Render(to_display.c_str());
}

void            glfw_lib::MainMenu(t_info *info) {
  int board_height;
  int board_width;
  int y;
  int x;


  board_height = (info->height * CELL_SIZE + BORDERS * 20) + SCORE_HEIGHT * 50;
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  y = board_height / 2;
  x = board_width / 3;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
  font_->FaceSize(30);

  glColor3f(1, .5, .0);
  glRasterPos2f(x, y);
  font_->Render("MAIN MENU");

  font_->FaceSize(20);
  if (info->menu_pos == 1)
    glColor3f(0.53, 0.63, 0.31);
  else
    glColor3f(1, 1, 1);
  glRasterPos2f(x, y - 30);
  font_->Render("Single Game");

  if (info->menu_pos == 2)
    glColor3f(0.53, 0.63, 0.31);
  else
    glColor3f(1, 1, 1);
  glRasterPos2f(x, y - 60);
  font_->Render("Player vs Player");

  if (info->menu_pos == 3)
    glColor3f(0.53, 0.63, 0.31);
  else
    glColor3f(1, 1, 1);
  glRasterPos2f(x, y - 90);
  font_->Render("Exit");
}

void            glfw_lib::PauseMenu(t_info *info) {
  int board_height;
  int board_width;
  int y;
  int x;


  board_height = (info->height * CELL_SIZE + BORDERS * 20) + SCORE_HEIGHT * 50;
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  y = board_height / 2;
  x = board_width / 3;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
  font_->FaceSize(30);

  glColor3f(1, .5, .0);
  glRasterPos2f(x, y);
  font_->Render("PAUSE MENU");

  font_->FaceSize(20);
  if (info->menu_pos == 1)
    glColor3f(0.53, 0.63, 0.31);
  else
    glColor3f(1, 1, 1);
  glRasterPos2f(x, y - 30);
  font_->Render("Continue");

  if (info->menu_pos == 2)
    glColor3f(0.53, 0.63, 0.31);
  else
    glColor3f(1, 1, 1);
  glRasterPos2f(x, y - 60);
  font_->Render("Main Menu");
}

void            glfw_lib::GameOverMenu(t_info *info) {
  int board_height;
  int board_width;
  int y;
  int x;


  board_height = (info->height * CELL_SIZE + BORDERS * 20) + SCORE_HEIGHT * 50;
  board_width = info->width * CELL_SIZE + BORDERS * 20;
  y = board_height / 2;
  x = board_width / 3;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
  font_->FaceSize(30);

  glColor3f(1, .5, .0);
  glRasterPos2f(x, y);
  font_->Render("GAME OVER");

  font_->FaceSize(20);
  if (info->menu_pos == 1)
    glColor3f(0.53, 0.63, 0.31);
  else
    glColor3f(1, 1, 1);
  glRasterPos2f(x, y - 30);
  font_->Render("Reset");

  if (info->menu_pos == 2)
    glColor3f(0.53, 0.63, 0.31);
  else
    glColor3f(1, 1, 1);
  glRasterPos2f(x, y - 60);
  font_->Render("Main Menu");
}

int             glfw_lib::Visual(t_info *info) {
  key_ = -1;

  if (glfwWindowShouldClose(window_)) {
    glfwDestroyWindow(window_);
    glfwTerminate();
    exit(0);
  }
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Draw gears
    if (info->status == PAUSE_MENU) {
      this->PauseMenu(info);
    } else if (info->status == GAME_OVER) {
      this->GameOverMenu(info);
    } else if (info->status == MAIN_MENU) {
      this->MainMenu(info);
    } else if (info->status == PLAY) {
      this->Map(info);
      this->Score(info);
    }
  // Swap buffers
  glfwSwapBuffers(this->window_);
  glfwPollEvents();
  if (info->status != PLAY){
    if (key_ == DOWN)
      key_ = UP;
    else if (key_ == UP)
      key_ = DOWN;
  }
  return key_;
}

void            glfw_lib::DrawSquare(int x, int y) {
  int cell = CELL_SIZE - 1;
  int new_x = 10 + x * cell + x;
  int new_y = 10 + y * cell + y + SCORE_HEIGHT * 30;

  glBegin(GL_QUADS);
    // top left
    glVertex3f(new_x, new_y,  0.0);
    // top right
    glVertex3f(new_x + cell,  new_y,  0.0);
    // bottom right
    glVertex3f(new_x + cell,  new_y + cell, 0.0);
    // bottom left
    glVertex3f(new_x, new_y + cell, 0.0);
  glEnd();
}


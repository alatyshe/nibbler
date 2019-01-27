#include "glfw.class.hpp"

IVisual*        NewVisual(t_info *info) { return new Glfw(info); }
void            DeleteVisual(IVisual* instance){
	delete instance;
}

extern "C" {
	int							key_;

	void						KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		(void)window;
		(void)scancode;
		(void)mods;
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			key_ = ESC;
		if (key == GLFW_KEY_Q && action == GLFW_PRESS)
			key_ = MENU;

		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
			key_ = ENTER;
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
			key_ = LEFT;
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
			key_ = RIGHT;
		if (key == GLFW_KEY_UP && action == GLFW_PRESS)
			key_ = DOWN;
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
			key_ = UP;

		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
			key_ = NCURSES;
		if (key == GLFW_KEY_2 && action == GLFW_PRESS)
			key_ = GLFW;
		if (key == GLFW_KEY_3 && action == GLFW_PRESS)
			key_ = SDL2;
	}
}


void printText() {
	char *string = "HELLO HELLO HELLO";
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(20, 20);
	//get the length of the string to display
	int len = (int) strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str ing[i]);
	}
};

//Constructors and destructor
Glfw::Glfw(void) { return ; }
Glfw::~Glfw(void) { glfwTerminate(); }

Glfw::Glfw(t_info *info) {
	int			board_height; 
	int			board_width;
	int			score_height;
	int			score_width;

	if(!glfwInit()) {
		exit(0);
	}

	board_height = info->height * CELL_SIZE + BORDERS * 10;
	board_width = info->width * CELL_SIZE + BORDERS * 10;
	score_height = SCORE_HEIGHT * 30;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	this->window_ = glfwCreateWindow(board_width,
														board_height + score_height,
														"LearnOpenGL", NULL, NULL );
	if (!this->window_) {
		glfwTerminate();
		exit(0);
	}

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
}

int             Glfw::ReadInput() {
	return -1;
}

void            Glfw::Map(t_info *info) {
	DrawBackground(info);

	for (int y = 0; y < info->height; y++) {
		for (int x = 0; x < info->width; x++) {
			if (info->map[y][x] == SNAKE_BODY) {
				glColor3f(0.0f, 0.85f, 0.0f);
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
				glColor3f(0.5f, 0.5f, 1.0f);
				DrawSquare(x, y);
			}
		}
	}

	return ;
}

void            Glfw::Score(t_info *info) {
	printText();
	return ;
}

void            Glfw::MainMenu(t_info *info) {
	printText();
	return ;
}

void            Glfw::PauseMenu(t_info *info) {
	printText();
	return ;
}

void            Glfw::GameOverMenu(t_info *info) {
	printText();
	return ;
}

int             Glfw::SmallScreen(t_info *info) {
	return(0);
}

int             Glfw::Visual(t_info *info) {
	key_ = -1;

	if (glfwWindowShouldClose(window_)) {
		glfwDestroyWindow(window_);
		glfwTerminate();
		exit(0);
	}
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
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
	
	return key_;
}




void						Glfw::DrawBackground(t_info *info) {
	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_QUADS);
						//  X 			Y
		// top left
		glVertex3f(BORDERS * 5.0,
				info->height * CELL_SIZE + SCORE_HEIGHT * 30 + BORDERS * 5,
				0.0);
		// top right
		glVertex3f(info->width * CELL_SIZE + BORDERS * 5.0 - 1,
				info->height * CELL_SIZE + SCORE_HEIGHT * 30 + BORDERS * 5,
				0.0);
		// bottom right
		glVertex3f(info->width * CELL_SIZE + BORDERS * 5.0 - 1,
				SCORE_HEIGHT * 30.0 + BORDERS * 5 - 1,
				0.0);
		// bottom left
		glVertex3f(BORDERS * 5.0,
				SCORE_HEIGHT * 30.0 + BORDERS * 5 - 1,
				0.0);
	glEnd();
}

void						Glfw::DrawSquare(int x, int y) {
	int cell = CELL_SIZE - 1;
	int new_x = 10 + x * cell + x;
	int new_y = 10 + y * cell + y + SCORE_HEIGHT * 30;

	glBegin(GL_QUADS);
		// top left
		glVertex3f(new_x,	new_y,	0.0);
		// top right
		glVertex3f(new_x + cell,	new_y,	0.0);
		// bottom right
		glVertex3f(new_x + cell,	new_y + cell,	0.0);
		// bottom left
		glVertex3f(new_x,	new_y + cell,	0.0);
	glEnd();
}










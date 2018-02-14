# include "../../header/Game.hpp"

Game::Game() { ; }
Game::~Game() { ; }

Game::Game(int width, int height) {
	//	Create and Null Map
	//	Information about game
	this->_info = new t_info();
	this->_info->map = NULL;
	this->_info->width = width;
	this->_info->height = height;
	this->_info->score = 0;
	this->_info->level = 2;
	this->_info->difficult = 1;
	this->_info->library = NCURSES;
	this->_info->status = MAIN_MENU;

	//	Type of visualisation
	this->_visual = NULL;
	this->_handle = NULL;

	//	Next move for body
	this->_next_x = 0;
	this->_next_y = 0;
}
/*
**	Getters
*/
t_info		*Game::getInfo()		{ return(this->_info); }
/*
**	Others
*/
void		Game::createSnake() {
	this->_snake.clear();

	for (int i = 0; i < SNAKE_LENGTH; i++)
		this->_snake.insert(this->_snake.begin(),
			new Piece(this->_info->width / 2 + i - 3, this->_info->height / 2));
	this->_head_move_x = 1; // 1(right) or 0(middle) or -1(left)
	this->_head_move_y = 0; // 1(up) or 0(middle) or -1(down)
}
void		Game::createMap() {
	int 	total_walls;
	int		y;
	int		x;

	//	Create Map
	this->_info->map = new char*[this->_info->height];
	for (int i = 0; i < this->_info->height; i++)
	{
		int j;
		this->_info->map[i] = new char[this->_info->width + 1];
		for (j = 0; j < this->_info->width; j++)
			this->_info->map[i][j] = 0;
		this->_info->map[i][j] = '\0';
	}
	//	Fill Map
	srand(time(NULL));
	total_walls = this->_info->width * this->_info->height / 100 * this->_info->difficult;
	while (total_walls > 0)
	{
		x = rand() % this->_info->width;
		y = rand() % this->_info->height;
		if (y != this->_info->height / 2 && this->_info->map[y][x] != WALL)
			this->_info->map[y][x] = WALL;
		total_walls--;
	}
	this->createFruit();
	this->createSnake();
}
void		Game::createFruit() {
	int		y;
	int		x;

	while (true)
	{
		x = rand() % (this->_info->width  - 1);
		y = rand() % (this->_info->height - 1);
		if (this->_info->map[y][x] != WALL
			&& x > 1 && y > 1)
		{
			this->_info->map[y][x] = APPLE;
			break;
		}
	}
}


void 		Game::putSnakeOnMap() {
	int			x;
	int			y;
	bool		apple;

	auto i = this->_snake.begin();
	apple = false;
	while (i != this->_snake.end()) {

		x = (*i)->GetX();
		y = (*i)->GetY();
		if (x < 0 || y < 0 || x >= this->_info->width || y >= this->_info->height)
			this->_info->status = GAME_OVER;
		else if (this->_info->map[y][x] == SNAKE_HEAD 
			|| this->_info->map[y][x] == SNAKE_BODY
			|| this->_info->map[y][x] == WALL
			)
			this->_info->status = GAME_OVER;
		else if (this->_info->map[y][x] == APPLE)
		{
			this->_info->map[y][x] = SNAKE_HEAD;
			apple = true;
		}
		else
		{
			if (i == this->_snake.begin())
				this->_info->map[y][x] = SNAKE_HEAD;
			else
				this->_info->map[y][x] = SNAKE_BODY;
		}
		i++;
	}
	if (apple)
	{
		this->_info->score += 100;
		this->createFruit();
		this->_snake.push_back(new Piece());
	}
}
void 		Game::moveSnakeBody() {
	int			x;
	int			y;
	std::vector<Piece *>::iterator i;

	i = this->_snake.begin();
	while (i != _snake.end()) {

		x = (*i)->GetX();
		y = (*i)->GetY();

		if (i == this->_snake.begin()) {
			(*i)->SetX(x + this->_head_move_x);
			(*i)->SetY(y + this->_head_move_y);
		} else {
			(*i)->SetX(this->_next_x);
			(*i)->SetY(this->_next_y);
		}

		this->_next_x = x;
		this->_next_y = y;
		i++;
	}
	this->_next_x = 0;
	this->_next_y = 0;
}
void 		Game::cleanMapFromSnake() {
	for (int i = 0; i < this->_info->height; i++)
	{
		for (int j = 0; j < this->_info->width; j++)
		{
			if (this->_info->map[i][j] == SNAKE_BODY
				|| this->_info->map[i][j] == SNAKE_HEAD)
				this->_info->map[i][j] = EMPTY;
		}
	}
}


void		Game::keyParser(int key) {
	if (key == LEFT || key == RIGHT)
	{
		if (this->_head_move_x == 0)
		{
			if (key == LEFT)
				this->_head_move_x = -1;
			if (key == RIGHT)
				this->_head_move_x = 1;
			this->_head_move_y = 0;
		}
	}
	if (key == UP || key == DOWN)
	{
		if (this->_head_move_y == 0)
		{
			if (key == UP)
				this->_head_move_y = -1;
			if (key == DOWN)
				this->_head_move_y = 1;
			this->_head_move_x = 0;
		}
	}
	if (key == NCURSES)
		this->libManipulation(NCURSES);
	if (key == QT)
		this->libManipulation(QT);
	if (key == SDL2)
		this->libManipulation(SDL2);
}

void		Game::libManipulation(int library) {
	IVisual*	(*new_instanse)(t_info *g);		//	указатель на функцию
	IVisual*	(*del_instance)(t_info *g);		//	указатель на функцию

	std::cout << "AAAA1" << std::endl;
	if (this->_handle)
	{
		std::cout << "AAAA" << std::endl;
		*(void **) (&del_instance) = dlsym(this->_handle, "DeleteVisual");
		std::cout << "AAAA" << std::endl;
		this->_visual = (*del_instance)(this->_info);
		std::cout << "AAAA" << std::endl;
		dlclose(this->_handle);
		std::cout << "AAAA" << std::endl;
		this->_handle = NULL;
	}

	std::cout << "AAAA2" << std::endl;
	if (library == NCURSES)
		this->_handle = dlopen("./libcurses.dylib", RTLD_LAZY);
	else if (library == QT)
		this->_handle = dlopen("./libqt.dylib", RTLD_LAZY);
	else if (library == SDL2)
		this->_handle = dlopen("./libsdl2.dylib", RTLD_LAZY);
	
	if (!this->_handle)
	{
		std::cout << "FUCK" << std::endl;
		return;
	}

	*(void **) (&new_instanse) = dlsym(this->_handle, "NewVisual");
	this->_visual = (*new_instanse)(this->_info);
}

void		Game::runGame()
{
	int		key_input;

	this->libManipulation(NCURSES);
	while(true)
	{
		putSnakeOnMap();
		if (this->_info->status == GAME_OVER || this->_info->status == MAIN_MENU)
			this->createMap();


		key_input = this->_visual->Visual(this->_info);

		this->keyParser(key_input);

		cleanMapFromSnake();

		if (this->_info->status == PLAY)
			moveSnakeBody();
	}
}

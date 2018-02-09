
#include "../header/Ncurses.class.hpp"

//Constructors and destructor

Ncurses::Ncurses(void) {
	return ;
}

Ncurses::~Ncurses(void) {
	return ;
}

Ncurses::Ncurses(Game *g) {
	setlocale(LC_ALL, "");
	initscr();				//  ncurses

	cbreak();				//  ncurses символы из input
	noecho();				//  ncurses
	curs_set(0);			//  ncurses убрать курсор

	// colors
	start_color();
	init_pair(1, 11, COLOR_BLACK);		//	цвет змейки
	init_pair(2, 226, COLOR_BLACK);		//	цвет ГОЛОВУШКИ
	init_pair(6, 9, COLOR_BLACK);		//	цвет препятствия
	init_pair(4, 2, COLOR_BLACK);		//	цвет яблока
	init_pair(5, 8, COLOR_BLACK);		//	серый
	init_pair(6, 15, COLOR_BLACK);		//	сброс цвета	
	init_pair(7, 8, 8);					//	серый фон
	init_pair(8, 9, COLOR_BLACK);		//	Красный	

	std::cin.sync();

	this->screen = newwin(g->getHeight() + BORDERS, g->getWidth() * 2 + BORDERS, 0, 0);
	this->score = newwin(SCORE_HEIGHT + BORDERS, g->getWidth() * 2 + BORDERS, g->getHeight() + BORDERS, 0);
	nodelay(this->screen, TRUE);	//	
	keypad(this->screen, TRUE);	//  для восприятия стрелочек
}

void           Ncurses::Input(Game *g) {
	int ch;

	ch = wgetch(this->screen);
	if (ch == 'q')
	{
		endwin();
		exit(0);
	}
	if (ch == KEY_LEFT)
		g->setHeadMoveXY(-1, 0);
	if (ch == KEY_RIGHT)
		g->setHeadMoveXY(1, 0);
	if (ch == KEY_UP)
		g->setHeadMoveXY(0, -1);
	if (ch == KEY_DOWN)
		g->setHeadMoveXY(0, 1);
}

void			Ncurses::Map(Game *g) {
	char		**map;
	int			width;
	int			height;

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	//	sides
	wattron(this->screen, COLOR_PAIR(7));
	for (int i = 0; i < (height + BORDERS); i++) {
		mvwprintw(this->screen, i, 0, "|");
		mvwprintw(this->screen, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(this->screen, 0, i, "_");
		mvwprintw(this->screen, height + 1, i, "-");
	}
	//	map
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[y][x] == SNAKE_BODY)
			{
				wattron(this->screen, COLOR_PAIR(1));
				mvwprintw(this->screen, y + 1, x * 2 + 1, "◎");
			}
			else if (map[y][x] == SNAKE_HEAD)
			{
				wattron(this->screen, COLOR_PAIR(2));
				mvwprintw(this->screen, y + 1 , x * 2 + 1, "🌞");
			}
			else if (map[y][x] == WALL)
			{
				wattron(this->screen, COLOR_PAIR(5));
				mvwprintw(this->screen, y + 1, x * 2 + 1, "💣");
			}
			else if (map[y][x] == APPLE)
			{
				wattron(this->screen, COLOR_PAIR(4) | WA_BOLD);
				// 🍒🍑🍐🍏🍊🍇🍅🍒💋🍪🔮🚪🏮©¤
				mvwprintw(this->screen, y + 1, x * 2 + 1, "🍒");
			}
			else
			{
				wattron(this->screen, COLOR_PAIR(5));
				mvwprintw(this->screen, y + 1, x * 2 + 1, ".");
			}
			mvwprintw(this->screen, y + 1, x * 2 + 2, " ");
		}
		wattron(this->screen, COLOR_PAIR(6));
	}
}

void			Ncurses::Score(Game *g) {
	int			total_score;
	int			level;
	int			difficult;
	int			width;

	width = g->getWidth();
	total_score = g->getScore();
	level = g->getLevel();
	difficult = g->getDifficult();

	//	information
	wattron(this->score, COLOR_PAIR(6) | WA_BOLD);	// color on
	mvwprintw(this->score, 1, 3,"Score : %d", total_score);
	mvwprintw(this->score, 2, 3,"Level : %d", level);
	mvwprintw(this->score, 3, 3,"Difficult : %d", difficult);
	mvwprintw(this->score, 1, 40, "LIVES : 💖 💖 💖 ");
	wattroff(this->score, COLOR_PAIR(6) | WA_BOLD);	// color off
	//	sides
	wattron(this->score, COLOR_PAIR(7));
	for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
		mvwprintw(this->score, i, 0, "|");
		mvwprintw(this->score, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(this->score, SCORE_HEIGHT + 1, i, "-");
	}
}
void			Ncurses::MainMenu(Game *g) {
	char		**map;
	int			width;
	int			height;

	wclear(this->screen);
	wclear(this->score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();
	//	sides
	wattron(this->screen, COLOR_PAIR(7));
	wattron(this->score, COLOR_PAIR(7));
	for (int i = 0; i < (height + BORDERS); i++) {
		mvwprintw(this->screen, i, 0, "|");
		mvwprintw(this->screen, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(this->screen, 0, i, "_");
	}
	for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
		mvwprintw(this->score, i, 0, "|");
		mvwprintw(this->score, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(this->score, SCORE_HEIGHT + 1, i, "-");
	}

	wattron(this->screen, COLOR_PAIR(1) | WA_BOLD);
	mvwprintw(this->screen, (height + SCORE_HEIGHT) / 2 - 2, width / 2, "MENU");
	
	wattron(this->screen,COLOR_PAIR(2));
	mvwprintw(this->screen, (height + SCORE_HEIGHT) / 2, width / 2, "SINGLE GAME");

	wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, (height + SCORE_HEIGHT) / 2 + 1, width / 2, "PLAYER VS PLAYER");

	wattron(this->screen, COLOR_PAIR(5));
	mvwprintw(this->screen, (height + SCORE_HEIGHT) / 2 + 2, width / 2, "EXIT");
}
void			Ncurses::PauseMenu(Game *g) {
	char		**map;
	int			width;
	int			height;

	wclear(this->screen);
	wclear(this->score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	//	sides
	wattron(this->screen, COLOR_PAIR(7));
	wattron(this->score, COLOR_PAIR(7));
	for (int i = 0; i < (height + BORDERS); i++) {
		mvwprintw(this->screen, i, 0, "|");
		mvwprintw(this->screen, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(this->screen, 0, i, "_");
	}
	for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
		mvwprintw(this->score, i, 0, "|");
		mvwprintw(this->score, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(this->score, SCORE_HEIGHT + 1, i, "-");
	}

	wattron(this->screen, COLOR_PAIR(1) | WA_BOLD);
	mvwprintw(this->screen, (height + SCORE_HEIGHT) / 2 - 2, width / 2, "PAUSE");
	
	wattron(this->screen,COLOR_PAIR(2));
	mvwprintw(this->screen, (height + SCORE_HEIGHT) / 2, width / 2, "CONTINUE");

	wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, (height + SCORE_HEIGHT) / 2 + 1, width / 2, "MAIN MENU");
}
void			Ncurses::GameOver(Game *g) {
	char		**map;
	int			width;
	int			height;

	wclear(this->screen);
	wclear(this->score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	for (int i = 0; i < (height + SCORE_HEIGHT + BORDERS * 2) ;i++)
	{
		wclear(this->screen);
		wclear(this->score);
		//	sides
		wattron(this->screen, COLOR_PAIR(7));
		wattron(this->score, COLOR_PAIR(7));
		for (int i = 0; i < (height + BORDERS); i++) {
			mvwprintw(this->screen, i, 0, "|");
			mvwprintw(this->screen, i, (width * 2) + 1, "|");
		}
		for (int i = 0; i < (width * 2 + BORDERS); i++) {
			mvwprintw(this->screen, 0, i, "_");
		}
		for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
			mvwprintw(this->score, i, 0, "|");
			mvwprintw(this->score, i, (width * 2) + 1, "|");
		}
		for (int i = 0; i < (width * 2 + BORDERS); i++) {
			mvwprintw(this->score, SCORE_HEIGHT + 1, i, "-");
		}

		if (i / 2 > 1)
		{
			wattron(this->screen, COLOR_PAIR(8) | WA_BOLD);
			mvwprintw(this->screen, i / 2 - 1, width / 2, "GAME OVER");
		}
		wattron(this->screen,COLOR_PAIR(4));
		mvwprintw(this->screen, i / 2 + 1, width / 2, "SCORE : %d", g->getScore());

		wrefresh(this->screen);
		wrefresh(this->score);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
void			Ncurses::SmallScreen(Game *g) {
	char		**map;
	int			width;
	int			height;

	wclear(this->screen);
	wclear(score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	wattron(this->screen, COLOR_PAIR(8) | WA_BOLD);
	mvwprintw(this->screen, 10, 10, "ERROR!!!");
	
	wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, 12, 10, "SCREEN TO SMALL. RESIZE OR");

	wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, 13, 10, "USE ANOTHER MAP SIZE TO CONTINUE");
}

void			Ncurses::n_curses_visual(Game *g, int game_over)
{

	// std::cout << "FUCK YEAH!!" << std::endl;
	static int			haha;
	int					screen_width;
	int					screen_height;

	//	Размер окна на текущий момент:
	// int parent_x, parent_y;
	getmaxyx(stdscr, screen_height, screen_width);
	// wclear(stdscr);

	// if (!haha)
	// {
	// 	haha = 1;
	// 	Setup(screen, score);

	// 	screen = newwin(g->getHeight() + BORDERS, g->getWidth() * 2 + BORDERS, 0, 0);
	// 	score = newwin(SCORE_HEIGHT + BORDERS, g->getWidth() * 2 + BORDERS, g->getHeight() + BORDERS, 0);
	// 	nodelay(screen, TRUE);
	// 	keypad(screen, TRUE);	//  для восприятия стрелочек
	// }

	wclear(screen);
	wclear(score);
	
	while (screen_height < g->getHeight() + SCORE_HEIGHT + BORDERS + 2
		|| screen_width < g->getWidth() * 2 + BORDERS)
	{
		wclear(stdscr);
		getmaxyx(stdscr, screen_height, screen_width);
		this->SmallScreen(g);
		wrefresh(screen);
		wrefresh(score);
	}
	// this->MainMenu(g);
	// this->PauseMenu(g);
	if (game_over)
		this->GameOver(g);
	else
	{
		this->Map(g);
		this->Score(g);
	}
	wrefresh(this->screen);
	wrefresh(this->score);
	this->Input(g);
}
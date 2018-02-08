#include "../../header/Game.hpp"
extern "C" {
	#include <ncurses.h>
}

void			Setup(WINDOW *screen, WINDOW *score) {
	setlocale(LC_ALL, "");
	initscr();              //  ncurses
	
	cbreak();               //  ncurses символы из input
	noecho();               //  ncurses
	curs_set(0);            //  ncurses убрать курсор

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
}
void            Input(Game *g, WINDOW *screen) {
	int ch;

	ch = wgetch(screen);
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
void			Map(Game *g, WINDOW *screen) {
	char		**map;
	int			width;
	int			height;

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	//	sides
	wattron(screen, COLOR_PAIR(7));
	for (int i = 0; i < (height + BORDERS); i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(screen, 0, i, "_");
		mvwprintw(screen, height + 1, i, "-");
	}
	//	map
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[y][x] == SNAKE_BODY)
			{
				wattron(screen, COLOR_PAIR(1));
				mvwprintw(screen, y + 1, x * 2 + 1, "◎");
			}
			else if (map[y][x] == SNAKE_HEAD)
			{
				wattron(screen, COLOR_PAIR(2));
				mvwprintw(screen, y + 1 , x * 2 + 1, "🌞");
			}
			else if (map[y][x] == WALL)
			{
				wattron(screen, COLOR_PAIR(5));
				mvwprintw(screen, y + 1, x * 2 + 1, "💣");
			}
			else if (map[y][x] == APPLE)
			{
				wattron(screen, COLOR_PAIR(4) | WA_BOLD);
				// 🍒🍑🍐🍏🍊🍇🍅🍒💋🍪🔮🚪🏮©¤
				mvwprintw(screen, y + 1, x * 2 + 1, "🍒");
			}
			else
			{
				wattron(screen, COLOR_PAIR(5));
				mvwprintw(screen, y + 1, x * 2 + 1, ".");
			}
			mvwprintw(screen, y + 1, x * 2 + 2, " ");
		}
		wattron(screen, COLOR_PAIR(6));
	}
}
void			Score(Game *g, WINDOW *score) {
	int			total_score;
	int			level;
	int			difficult;
	int			width;

	width = g->getWidth();
	total_score = g->getScore();
	level = g->getLevel();
	difficult = g->getDifficult();

	//	information
	wattron(score, COLOR_PAIR(6) | WA_BOLD);	// color on
	mvwprintw(score, 1, 3,"Score : %d", total_score);
	mvwprintw(score, 2, 3,"Level : %d", level);
	mvwprintw(score, 3, 3,"Difficult : %d", difficult);
	mvwprintw(score, 1, 40, "LIVES : 💖 💖 💖 ");
	wattroff(score, COLOR_PAIR(6) | WA_BOLD);	// color off
	//	sides
	wattron(score, COLOR_PAIR(7));
	for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
		mvwprintw(score, i, 0, "|");
		mvwprintw(score, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(score, SCORE_HEIGHT + 1, i, "-");
	}
}
void			MainMenu(Game *g, WINDOW *screen, WINDOW *score) {
	char		**map;
	int			width;
	int			height;

	wclear(screen);
	wclear(score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();
	//	sides
	wattron(screen, COLOR_PAIR(7));
	wattron(score, COLOR_PAIR(7));
	for (int i = 0; i < (height + BORDERS); i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(screen, 0, i, "_");
	}
	for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
		mvwprintw(score, i, 0, "|");
		mvwprintw(score, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(score, SCORE_HEIGHT + 1, i, "-");
	}

	wattron(screen, COLOR_PAIR(1) | WA_BOLD);
	mvwprintw(screen, (height + SCORE_HEIGHT) / 2 - 2, width / 2, "MENU");
	
	wattron(screen,COLOR_PAIR(2));
	mvwprintw(screen, (height + SCORE_HEIGHT) / 2, width / 2, "SINGLE GAME");

	wattron(screen,COLOR_PAIR(5));
	mvwprintw(screen, (height + SCORE_HEIGHT) / 2 + 1, width / 2, "PLAYER VS PLAYER");

	wattron(screen, COLOR_PAIR(5));
	mvwprintw(screen, (height + SCORE_HEIGHT) / 2 + 2, width / 2, "EXIT");
}
void			PauseMenu(Game *g, WINDOW *screen, WINDOW *score) {
	char		**map;
	int			width;
	int			height;

	wclear(screen);
	wclear(score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	//	sides
	wattron(screen, COLOR_PAIR(7));
	wattron(score, COLOR_PAIR(7));
	for (int i = 0; i < (height + BORDERS); i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(screen, 0, i, "_");
	}
	for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
		mvwprintw(score, i, 0, "|");
		mvwprintw(score, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(score, SCORE_HEIGHT + 1, i, "-");
	}

	wattron(screen, COLOR_PAIR(1) | WA_BOLD);
	mvwprintw(screen, (height + SCORE_HEIGHT) / 2 - 2, width / 2, "PAUSE");
	
	wattron(screen,COLOR_PAIR(2));
	mvwprintw(screen, (height + SCORE_HEIGHT) / 2, width / 2, "CONTINUE");

	wattron(screen,COLOR_PAIR(5));
	mvwprintw(screen, (height + SCORE_HEIGHT) / 2 + 1, width / 2, "MAIN MENU");
}
void			GameOver(Game *g, WINDOW *screen, WINDOW *score) {
	char		**map;
	int			width;
	int			height;

	wclear(screen);
	wclear(score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	for (int i = 0; i < (height + SCORE_HEIGHT + BORDERS * 2) ;i++)
	{
		wclear(screen);
		wclear(score);
		//	sides
		wattron(screen, COLOR_PAIR(7));
		wattron(score, COLOR_PAIR(7));
		for (int i = 0; i < (height + BORDERS); i++) {
			mvwprintw(screen, i, 0, "|");
			mvwprintw(screen, i, (width * 2) + 1, "|");
		}
		for (int i = 0; i < (width * 2 + BORDERS); i++) {
			mvwprintw(screen, 0, i, "_");
		}
		for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
			mvwprintw(score, i, 0, "|");
			mvwprintw(score, i, (width * 2) + 1, "|");
		}
		for (int i = 0; i < (width * 2 + BORDERS); i++) {
			mvwprintw(score, SCORE_HEIGHT + 1, i, "-");
		}

		if (i / 2 > 1)
		{
			wattron(screen, COLOR_PAIR(8) | WA_BOLD);
			mvwprintw(screen, i / 2 - 1, width / 2, "GAME OVER");
		}
		wattron(screen,COLOR_PAIR(4));
		mvwprintw(screen, i / 2 + 1, width / 2, "SCORE : %d", g->getScore());

		wrefresh(screen);
		wrefresh(score);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
void			SmallScreen(Game *g, WINDOW *screen, WINDOW *score) {
	char		**map;
	int			width;
	int			height;

	wclear(screen);
	wclear(score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	wattron(screen, COLOR_PAIR(8) | WA_BOLD);
	mvwprintw(screen, 10, 10, "ERROR!!!");
	
	wattron(screen,COLOR_PAIR(5));
	mvwprintw(screen, 12, 10, "SCREEN TO SMALL. RESIZE OR");

	wattron(screen,COLOR_PAIR(5));
	mvwprintw(screen, 13, 10, "USE ANOTHER MAP SIZE TO CONTINUE");
}

void			n_curses_visual(Game *g, int game_over)
{

	std::cout << "FUCK YEAH!!" << std::endl;
	// static int			haha;
	// static WINDOW		*screen;
	// static WINDOW		*score;
	// int					screen_width;
	// int					screen_height;

	// //	Размер окна на текущий момент:
	// // int parent_x, parent_y;
	// getmaxyx(stdscr, screen_height, screen_width);
	// // wclear(stdscr);

	// std::cin.sync();
	// if (!haha)
	// {
	// 	haha = 1;
	// 	Setup(screen, score);

	// 	screen = newwin(g->getHeight() + BORDERS, g->getWidth() * 2 + BORDERS, 0, 0);
	// 	score = newwin(SCORE_HEIGHT + BORDERS, g->getWidth() * 2 + BORDERS, g->getHeight() + BORDERS, 0);
	// 	nodelay(screen, TRUE);
	// 	keypad(screen, TRUE);	//  для восприятия стрелочек
	// }

	// wclear(screen);
	// wclear(score);
	
	// while (screen_height < g->getHeight() + SCORE_HEIGHT + BORDERS + 2
	// 	|| screen_width < g->getWidth() * 2 + BORDERS)
	// {
	// 	wclear(stdscr);
	// 	getmaxyx(stdscr, screen_height, screen_width);
	// 	SmallScreen(g, screen, score);
	// 	wrefresh(screen);
	// 	wrefresh(score);
	// }
	// // Score(g, score);
	// // MainMenu(g, screen, score);
	// // PauseMenu(g, screen, score);
	// if (game_over)
	// 	GameOver(g, screen, score);
	// else {
	// 	// SmallScreen(g, screen, score);
	// 	Map(g, screen);
	// 	Score(g, score);
	// }
	// wrefresh(screen);
	// wrefresh(score);
	// Input(g, screen);
}


extern "C" void			bbbb()
{
	std::cout << "FUCK HAAH!" << std::endl;
}
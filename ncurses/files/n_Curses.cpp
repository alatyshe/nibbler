#include <ncurses.h>
#include "../../header/Game.hpp"

void			GameIntilization(WINDOW *screen, WINDOW *score) {
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
}

void            readInput(Game *g, WINDOW *screen) {
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

	// flushinp();	//	сброс разного дерьма который наклацали
}

void			displayMap(Game *g, WINDOW *screen) {
	char		**map;
	int			width;
	int			height;

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	// sides
	wattron(screen, COLOR_PAIR(7));
	for (int i = 0; i < (height + BORDERS); i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(screen, 0, i, "_");
		mvwprintw(screen, height + 1, i, "-");
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[y][x] == SNAKE_BODY)
			{
				wattron(screen, COLOR_PAIR(1));
				mvwprintw(screen, y + 1, x * 2 + 1, "¤");
			}
			else if (map[y][x] == SNAKE_HEAD)
			{
				wattron(screen, COLOR_PAIR(2));
				mvwprintw(screen, y + 1 , x * 2 + 1, "©");
			}
			else if (map[y][x] == WALL)
			{
				wattron(screen, COLOR_PAIR(5));
				mvwprintw(screen, y + 1, x * 2 + 1, "#");
			}
			else if (map[y][x] == APPLE)
			{
				wattron(screen, COLOR_PAIR(4) | WA_BOLD);
				mvwprintw(screen, y + 1, x * 2 + 1, "@");
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
void			displayScore(Game *g, WINDOW *score) {
	int			total_score;
	int			level;
	int			difficult;
	int			width;

	width = g->getWidth();
	total_score = g->getScore();
	level = g->getLevel();
	difficult = g->getDifficult();

	wattron(score, COLOR_PAIR(6) | WA_BOLD);	// color on
	mvwprintw(score, 1, 3,"Score : %d\n", total_score);
	mvwprintw(score, 2, 3,"Level : %d\n", level);
	mvwprintw(score, 3, 3,"Difficult : %d\n", difficult);
	wattroff(score, COLOR_PAIR(6) | WA_BOLD);	// color off
		// sides
	wattron(score, COLOR_PAIR(7));
	for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
		mvwprintw(score, i, 0, "|");
		mvwprintw(score, i, (width * 2) + 1, "|");
	}
	for (int i = 0; i < (width * 2 + BORDERS); i++) {
		mvwprintw(score, SCORE_HEIGHT + 1, i, "-");
	}
}
void			displayMainMenu(Game *g, WINDOW *screen, WINDOW *score) {
	char		**map;
	int			width;
	int			height;

	wclear(screen);
	wclear(score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	wattron(screen, COLOR_PAIR(1) | WA_BOLD);
	mvwprintw(screen, height / 2 - 2, width / 2, "MENU");
	
	wattron(screen,COLOR_PAIR(2));
	mvwprintw(screen, height / 2, width / 2, "START");

	wattron(screen,COLOR_PAIR(5));
	mvwprintw(screen, height / 2 + 1, width / 2, "CHANGE VISUAL");

	wattron(screen, COLOR_PAIR(5));
	mvwprintw(screen, height / 2 + 2, width / 2, "EXIT");

	wrefresh(screen);	// Вывод приветствия на настоящий экран
	wrefresh(score);	// Вывод приветствия на настоящий экран
}
void			displayPauseMenu(Game *g, WINDOW *screen, WINDOW *score) {
	char		**map;
	int			width;
	int			height;

	wclear(screen);
	wclear(score);

	map = g->getMap();
	width = g->getWidth();
	height = g->getHeight();

	wattron(screen, COLOR_PAIR(1) | WA_BOLD);
	mvwprintw(screen, height / 2 - 2, width / 2, "PAUSE");
	
	wattron(screen,COLOR_PAIR(2));
	mvwprintw(screen, height / 2, width / 2, "CONTINUE");

	wattron(screen,COLOR_PAIR(5));
	mvwprintw(screen, height / 2 + 1, width / 2, "MAIN MENU");

	wrefresh(screen);	// Вывод приветствия на настоящий экран
	wrefresh(score);	// Вывод приветствия на настоящий экран
}

void			n_curses_visual(Game *g)
{
	static int			haha;
	static WINDOW		*screen;
	static WINDOW		*score;

	//	Размер окна на текущий момент:
	// int parent_x, parent_y;
	// getmaxyx(stdscr, parent_y, parent_x);
	// wclear(stdscr);

	std::cin.sync();
	if (!haha)
	{
		haha = 1;
		GameIntilization(screen, score);

		screen = newwin(g->getHeight() + BORDERS, g->getWidth() * 2 + BORDERS, 0, 0);
		score = newwin(SCORE_HEIGHT + BORDERS, g->getWidth() * 2 + BORDERS, g->getHeight() + BORDERS, 0);
		nodelay(screen, TRUE);
		nodelay(score, TRUE);
		keypad(screen, TRUE);    //  для восприятия стрелочек
		keypad(score, TRUE);    //  для восприятия стрелочек
	}


	wclear(screen);
	wclear(score);
	
	// displayMainMenu(g, screen, score);
	// displayPauseMenu(g, screen, score);
	displayMap(g, screen);
	displayScore(g, score);

	wrefresh(screen);                   // Вывод приветствия на настоящий экран
	wrefresh(score);                   // Вывод приветствия на настоящий экран
	readInput(g, screen);
	// while (1);
}


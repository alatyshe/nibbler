#include "../header/Ncurses.class.hpp"

//Constructors and destructor
Ncurses::Ncurses(void) { return ; }
Ncurses::~Ncurses(void) { return ; }
Ncurses::Ncurses(t_info *info) {
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

	this->screen = newwin(info->height + BORDERS, info->width * 2 + BORDERS, 0, 0);
	this->score = newwin(SCORE_HEIGHT + BORDERS, info->width * 2 + BORDERS, info->height + BORDERS, 0);
	nodelay(this->screen, TRUE);	//	
	keypad(this->screen, TRUE);	//  для восприятия стрелочек
}

void			Ncurses::PrintBorders(t_info *info) {
	int			width;
	int			height;

	width = info->width;
	height = info->height;
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
}

int				Ncurses::ReadInput() {
	int ch;

	ch = wgetch(this->screen);
	// std::cout << " HERE : " << ch << std::endl;
	if (ch == 27)
		return ESC;
	if (ch == 10)
		return ENTER;

	if (ch == KEY_UP)
		return UP;
	if (ch == KEY_RIGHT)
		return RIGHT;
	if (ch == KEY_LEFT)
		return LEFT;
	if (ch == KEY_DOWN)
		return DOWN;
		
	if (ch == 50)
		return NCURSES;
	if (ch == 51)
		return QT;
	if (ch == 52)
		return SDL2;
	return (0);
}

void			Ncurses::Map(t_info *info) {
	char		**map;
	int			width;
	int			height;

	map = info->map;
	width = info->width;
	height = info->height;

	wclear(screen);
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
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == SNAKE_BODY) {
				wattron(this->screen, COLOR_PAIR(1));
				mvwprintw(this->screen, y + 1, x * 2 + 1, "◎");
			} else if (map[y][x] == SNAKE_HEAD) {
				wattron(this->screen, COLOR_PAIR(2));
				mvwprintw(this->screen, y + 1 , x * 2 + 1, "🌞");
			} else if (map[y][x] == WALL) {
				wattron(this->screen, COLOR_PAIR(5));
				mvwprintw(this->screen, y + 1, x * 2 + 1, "💣");
			} else if (map[y][x] == APPLE) {
				wattron(this->screen, COLOR_PAIR(4) | WA_BOLD);
				// 🍒🍑🍐🍏🍊🍇🍅🍒💋🍪🔮🚪🏮©¤
				mvwprintw(this->screen, y + 1, x * 2 + 1, "🍒");
			} else {
				wattron(this->screen, COLOR_PAIR(5));
				mvwprintw(this->screen, y + 1, x * 2 + 1, ".");
			}
			mvwprintw(this->screen, y + 1, x * 2 + 2, " ");
		}
		wattron(this->screen, COLOR_PAIR(6));
	}
	wrefresh(this->screen);
}
void			Ncurses::Score(t_info *info) {
	int			total_score;
	int			level;
	int			difficult;
	int			width;

	width = info->width;
	total_score = info->score;
	level = info->level;
	difficult = info->difficult;

	wclear(score);
	//	information
	wattron(this->score, COLOR_PAIR(6) | WA_BOLD);	// color on
	mvwprintw(this->score, 1, 3,"Score : %d", total_score);
	mvwprintw(this->score, 2, 3,"Level : %d", level);
	mvwprintw(this->score, 3, 3,"Difficult : %d", difficult);
	// mvwprintw(this->score, 1, 40, "LIVES : 💖 💖 💖 ");
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
	wrefresh(this->score);
}


void			Ncurses::MainMenu(t_info *info) {
	int			key;
	int			cursor_position;

	key = 0;
	cursor_position = 1;
	while (key != ENTER)
	{
		wclear(this->screen);
		wclear(this->score);

		this->PrintBorders(info);

		wattron(this->screen, COLOR_PAIR(1) | WA_BOLD);
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 - 2, info->width / 2, "MENU");
		cursor_position == 1 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2, info->width / 2, "SINGLE GAME");
		cursor_position == 2 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 + 1, info->width / 2, "PLAYER VS PLAYER");
		cursor_position == 3 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 + 2, info->width / 2, "EXIT");
		
		wrefresh(this->screen);
		wrefresh(this->score);

		key = this->ReadInput();

		if (key == 1 && cursor_position > 1)
			cursor_position--;
		else if (key == 4 && cursor_position < 3)
			cursor_position++;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	if (cursor_position == 1)
		info->status = PLAY;
	else if (cursor_position == 2)
		;// info->status = ;
	else
		info->status = EXIT;
}
void			Ncurses::PauseMenu(t_info *info) {
	int			key;
	int			cursor_position;

	key = 0;
	cursor_position = 1;
	while (key != ENTER)
	{
		wclear(this->screen);
		wclear(this->score);

		this->PrintBorders(info);

		wattron(this->screen, COLOR_PAIR(1) | WA_BOLD);
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 - 2, info->width / 2, "PAUSE");
		cursor_position == 1 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2, info->width / 2, "CONTINUE");
		cursor_position == 2 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 + 1, info->width / 2, "MAIN MENU");

		wrefresh(this->screen);
		wrefresh(this->score);

		key = this->ReadInput();
		if (key == 1 && cursor_position > 1)
			cursor_position--;
		else if (key == 4 && cursor_position < 2)
			cursor_position++;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	if (cursor_position == 1)
		info->status = PLAY;
	else if (cursor_position == 2)
		info->status = MAIN_MENU;
}
void			Ncurses::GameOverMenu(t_info *info) {
	int			key;
	int			cursor_position;

	key = 0;
	cursor_position = 1;
	while (key != ENTER)
	{
		wclear(this->screen);
		wclear(this->score);
		
		this->PrintBorders(info);

		wattron(this->screen, COLOR_PAIR(8) | WA_BOLD);
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 - 2, info->width / 2, "GAME OVER");
		cursor_position == 1 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2, info->width / 2, "RESET");
		cursor_position == 2 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
		mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 + 1, info->width / 2, "MAIN MENU");

		wrefresh(this->screen);
		wrefresh(this->score);

		key = this->ReadInput();

		if (key == 1 && cursor_position > 1)
			cursor_position--;
		else if (key == 4 && cursor_position < 2)
			cursor_position++;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	if (cursor_position == 1)
		info->status = PLAY;
	else if (cursor_position == 2)
		info->status = MAIN_MENU;
}


int				Ncurses::SmallScreen(t_info *info) {
	int					screen_width;
	int					screen_height;

	getmaxyx(stdscr, screen_height, screen_width);
	if (screen_height < info->height + SCORE_HEIGHT + BORDERS + 2
		|| screen_width < info->width * 2 + BORDERS)
	{
		wclear(this->screen);
		wclear(score);

		wattron(this->screen, COLOR_PAIR(8) | WA_BOLD);
		mvwprintw(this->screen, 10, 10, "ERROR!!!");
		wattron(this->screen,COLOR_PAIR(5));
		mvwprintw(this->screen, 12, 10, "SCREEN TO SMALL. RESIZE OR");
		wattron(this->screen,COLOR_PAIR(5));
		mvwprintw(this->screen, 13, 10, "USE ANOTHER MAP SIZE TO CONTINUE");

		wrefresh(screen);
		wrefresh(score);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return (1);
	}
	else
		return(0);
}


int				Ncurses::Visual(t_info *info) {

	int					key;

	if (!this->SmallScreen(info))
	{
		//	Читаем клавиши
		key = this->ReadInput();
		if (key == ESC)
			info->status = PAUSE_MENU;


		if (info->status == PAUSE_MENU) {
			this->PauseMenu(info);
		} else if (info->status == GAME_OVER) {
			this->GameOverScreen(info);
			this->GameOverMenu(info);
		} else if (info->status == MAIN_MENU) {
			this->MainMenu(info);
		} else if (info->status == PLAY) {
			this->Map(info);
			this->Score(info);
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(260 / 2));
	return (key);
}

IVisual*		NewVisual(t_info *info) { return new Ncurses(info); }
void			DeleteVisual(IVisual* instance){
	endwin();
	delete instance;
}




























void			Ncurses::GameOverScreen(t_info *info) {
	int			width;
	int			height;

	wclear(this->screen);
	wclear(this->score);

	width = info->width;
	height = info->height;

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

		if (i / 2 - 2 > 1) {
			wattron(this->screen, COLOR_PAIR(8) | WA_BOLD);
			mvwprintw(this->screen, i / 2 - 3, width / 2, "GAME OVER");
		}
		if (i / 2 > 1) {
			wattron(this->screen,COLOR_PAIR(4));
			mvwprintw(this->screen, i / 2 - 1, width / 2, "SCORE : %d", info->score);
		}

		wrefresh(this->screen);
		wrefresh(this->score);
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
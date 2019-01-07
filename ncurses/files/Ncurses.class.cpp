#include "../header/Ncurses.class.hpp"

IVisual*		NewVisual(t_info *info) { 
	// Создаем экземпляр нашей визуализации и возвращаем
	return new Ncurses(info); 
}

void			DeleteVisual(IVisual* instance){
	// закрываем все что связанно с визуализацией и удаляем экземпляр
	delete instance;
}



//Constructors and destructor
Ncurses::Ncurses(void) { return ; }

Ncurses::~Ncurses(void) {
	refresh();
	wrefresh(this->screen);
	wrefresh(this->score);
	delwin(this->screen);
	delwin(this->score);
	endwin();
}

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
	keypad(this->screen, TRUE);		//  для восприятия стрелочек
}

void			Ncurses::PrintBorders(t_info *info) {
	wattron(this->screen, COLOR_PAIR(7));
	wattron(this->score, COLOR_PAIR(7));
	for (int i = 0; i < (info->height + BORDERS); i++) {
		mvwprintw(this->screen, i, 0, "|");
		mvwprintw(this->screen, i, (info->width * 2) + 1, "|");
	}
	for (int i = 0; i < (info->width * 2 + BORDERS); i++) {
		mvwprintw(this->screen, 0, i, "_");
	}
	for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
		mvwprintw(this->score, i, 0, "|");
		mvwprintw(this->score, i, (info->width * 2) + 1, "|");
	}
	for (int i = 0; i < (info->width * 2 + BORDERS); i++) {
		mvwprintw(this->score, SCORE_HEIGHT + 1, i, "-");
	}
}

int				Ncurses::ReadInput() {
	return wgetch(this->screen);
}

void			Ncurses::Map(t_info *info) {
	wclear(this->screen);
	//	sides
	wattron(this->screen, COLOR_PAIR(7));
	for (int i = 0; i < (info->height + BORDERS); i++) {
		mvwprintw(this->screen, i, 0, "|");
		mvwprintw(this->screen, i, (info->width * 2) + 1, "|");
	}
	for (int i = 0; i < (info->width * 2 + BORDERS); i++) {
		mvwprintw(this->screen, 0, i, "_");
		mvwprintw(this->screen, info->height + 1, i, "-");
	}
	//	map
	for (int y = 0; y < info->height; y++) {
		for (int x = 0; x < info->width; x++) {
			if (info->map[y][x] == SNAKE_BODY) {
				wattron(this->screen, COLOR_PAIR(1));
				mvwprintw(this->screen, y + 1, x * 2 + 1, "◎");
			} else if (info->map[y][x] == SNAKE_HEAD) {
				wattron(this->screen, COLOR_PAIR(2));
				mvwprintw(this->screen, y + 1 , x * 2 + 1, "🌞");
			} else if (info->map[y][x] == WALL) {
				wattron(this->screen, COLOR_PAIR(5));
				mvwprintw(this->screen, y + 1, x * 2 + 1, "💣");
			} else if (info->map[y][x] == APPLE) {
				wattron(this->screen, COLOR_PAIR(4) | WA_BOLD);
				// 🍒🍑🍐🍏🍊🍇🍅🍒💋🍪🔮🚪🏮©¤
				mvwprintw(this->screen, y + 1, x * 2 + 1, "🍒");
			} else {
				wattron(this->screen, COLOR_PAIR(5));
				mvwprintw(this->screen, y + 1, x * 2 + 1, ".");
				mvwprintw(this->screen, y + 1, x * 2 + 2, " ");
			}
			
		}
		wattron(this->screen, COLOR_PAIR(6));
	
	refresh();}
	wrefresh(this->screen);
}
void			Ncurses::Score(t_info *info) {
	wclear(this->score);
	//	information
	wattron(this->score, COLOR_PAIR(6) | WA_BOLD);	// color on
	mvwprintw(this->score, 1, 3,"Score : %d", info->score);
	mvwprintw(this->score, 2, 3,"Level : %d", info->level);
	mvwprintw(this->score, 3, 3,"Difficult : %d", info->difficult);
	// mvwprintw(this->score, 1, 40, "LIVES : 💖 💖 💖 ");
	wattroff(this->score, COLOR_PAIR(6) | WA_BOLD);	// color off
	//	sides
	wattron(this->score, COLOR_PAIR(7));
	for (int i = 0; i < (SCORE_HEIGHT + BORDERS); i++) {
		mvwprintw(this->score, i, 0, "|");
		mvwprintw(this->score, i, (info->width * 2) + 1, "|");
	}
	for (int i = 0; i < (info->width * 2 + BORDERS); i++) {
		mvwprintw(this->score, SCORE_HEIGHT + 1, i, "-");
	}
	wrefresh(this->score);
}


void			Ncurses::MainMenu(t_info *info) {
	wclear(this->screen);
	wclear(this->score);

	this->PrintBorders(info);

	wattron(this->screen, COLOR_PAIR(1) | WA_BOLD);
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 - 2, info->width / 2, "MENU");
	info->menu_pos == 1 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2, info->width / 2, "SINGLE GAME");
	info->menu_pos == 2 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 + 1, info->width / 2, "PLAYER VS PLAYER");
	info->menu_pos == 3 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 + 2, info->width / 2, "EXIT");
	
	refresh();
	wrefresh(this->screen);
	wrefresh(this->score);
}

void			Ncurses::PauseMenu(t_info *info) {
	wclear(this->screen);
	wclear(this->score);

	this->PrintBorders(info);

	wattron(this->screen, COLOR_PAIR(1) | WA_BOLD);
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 - 2, info->width / 2, "PAUSE");
	info->menu_pos == 1 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2, info->width / 2, "CONTINUE");
	info->menu_pos == 2 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 + 1, info->width / 2, "MAIN MENU");
	
	refresh();
	wrefresh(this->screen);
	wrefresh(this->score);
}

void			Ncurses::GameOverMenu(t_info *info) {
	wclear(this->screen);
	wclear(this->score);
	
	this->PrintBorders(info);

	wattron(this->screen, COLOR_PAIR(8) | WA_BOLD);
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 - 2, info->width / 2, "GAME OVER");
	info->menu_pos == 1 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2, info->width / 2, "RESET");
	info->menu_pos == 2 ? wattron(this->screen,COLOR_PAIR(2)) : wattron(this->screen,COLOR_PAIR(5));
	mvwprintw(this->screen, (info->height + SCORE_HEIGHT) / 2 + 1, info->width / 2, "MAIN MENU");
	
	refresh();
	wrefresh(this->screen);
	wrefresh(this->score);
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
	
		refresh();
		wrefresh(this->screen);
		wrefresh(this->score);
		return (1);
	}
	else
		return(0);
}


int				Ncurses::Visual(t_info *info) {
	// endwin();
	if (!this->SmallScreen(info))
	{
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
		
	}
	return this->ReadInput();
}



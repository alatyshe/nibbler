#include "../header/Game.hpp"
#include "../header/Parser.hpp"



// int main()
// {
//     initscr();                   // Переход в curses-режим
//     printw("Hello world!\n");  // Отображение приветствия в буфер
//     refresh();                   // Вывод приветствия на настоящий экран
//     getch();                     // Ожидание нажатия какой-либо клавиши пользователем
//     endwin();                    // Выход из curses-режима. Обязательная команда.
//     return 0;
// }

int				main(int argc, char **argv) {
	int			x;
	int			y;
	Game		*game;

	if (argc == 3) {
		std::string first(argv[1]);
		std::string second(argv[2]);

		x = Parser::parseNumber(first);
		y = Parser::parseNumber(second);
		
		game = new Game(x, y);
		game->runGame();

	} else {
		std::cout << "Usage:" << std::endl;
		std::cout << "\t width height" << std::endl;
	}
	return (0);
}

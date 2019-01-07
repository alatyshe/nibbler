#include "../header/Game.hpp"
#include "../header/Parser.hpp"

// typedef 

std::string			print_usage() {
	std::stringstream	usage;
	usage << "Usage:" << std::endl
			<< "\t width height" << std::endl
			<< "min:" << MIN_SIZE
			<< " max:" << MAX_SIZE;

	return usage.str();
}

int				main(int argc, char **argv) {
	int			x;
	int			y;
	Game		*game;

	// мб добавить выбор библиотеки
	try {
		if (argc == 3) {
			std::string first(argv[1]);
			std::string second(argv[2]);

			x = Parser::parseNumber(first);
			y = Parser::parseNumber(second);

			game = new Game(x, y);
			game->MainLoop();
		} else {
			std::cout << print_usage() << std::endl;
		}
	} catch (Exception &e) {
		std::cout << e.what() << std::endl;
	}


	return (0);
}

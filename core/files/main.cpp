#include "../../header/Game.hpp"
#include "../../header/Parser.hpp"

int				main(int argc, char **argv) {
	int			x;
	int			y;
	Game		*game;

	if (argc == 3) {
		std::string first(argv[1]);
		std::string second(argv[2]);

		x = Parser::parseNumber(first);
		y = Parser::parseNumber(second);
		if (x < MAX_WIDTH && x > 0 && y > 0 && y < MAX_HEIGHT)
		{
			game = new Game(x, y);
			game->runGame();
			return (0);
		}

	}
	std::cout << "Usage:" << std::endl;
	std::cout << "\t width height" << std::endl;
	std::cout << "Max Height : " << MAX_HEIGHT << std::endl;
	return (0);
}

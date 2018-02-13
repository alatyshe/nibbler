#include "../../header/Game.hpp"
#include "../../header/Parser.hpp"

// typedef 

int				main(int argc, char **argv) {
	int			x;
	int			y;
	Game		*game;

	if (argc == 3) {
		std::string first(argv[1]);
		std::string second(argv[2]);

		x = Parser::parseNumber(first);
		y = Parser::parseNumber(second);



		// dlclose(handle);
		// printf("Return code: %d\n",x);
		// return 0;


		// const char *	dlsym_error;
		// void *			symbol;

		// void * handler = dlopen("libcurses.dylib", RTLD_NOW);
		// if (!handler)
		// 	return (0);
		// dlerror();
		// symbol = dlsym(handler, "glib_instantiate");
		// dlsym_error = dlerror();
		// dlerror();
		// symbol = dlsym(handler, "glib_uninstantiate");
		// dlsym_error = dlerror();


		if (x < MAX_WIDTH && x > MIN_WIDTH 
			&& y > MIN_HEIGHT && y < MAX_HEIGHT)
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

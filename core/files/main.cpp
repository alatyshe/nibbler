#include "../../header/Game.hpp"
#include "../../header/Parser.hpp"
#include <dlfcn.h>

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






		void	(*fun)(void);
		void 	*handle = dlopen("./libcurses.dylib", RTLD_LAZY);

		if (!handle)
		{
			std::cout << "FUCK" << std::endl;
			return(0);
		}
		*(void **) (&fun) = dlsym(handle, "bbbb");
		(*fun)();
		// dlclose(handle);
		// printf("Return code: %d\n",x);
		return 0;






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







		if (x < MAX_WIDTH && x > 0 && y > 0 && y < MAX_HEIGHT)
		{
			// game = new Game(x, y);
			// game->runGame();
			return (0);
		}

	}
	std::cout << "Usage:" << std::endl;
	std::cout << "\t width height" << std::endl;
	std::cout << "Max Height : " << MAX_HEIGHT << std::endl;
	return (0);
}

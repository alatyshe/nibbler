#----- Colors -----
BLACK	= "\033[1;30m"
RED	 	= "\033[1;31m"
GREEN	= "\033[1;32m"
YELLOW	= "\033[1;33m"
BLUE	= "\033[1;34m"
MAGENTA	= "\033[1;35m"
CYAN	= "\033[1;35m"
PURPLE	= "\033[1;36m"
WHITE	= "\033[1;37m"
EOC	 	= "\033[0;0m"
RESET	= "\x1b[0m"
#==================

.PHONY: all
all: SFML GLFW freetype2 FTGL lib_sfml lib_glfw lib_ncurses lib_sdl nibbler_core

.PHONY: clean
clean:
	rm -rf build/
	rm -rf lib/
	rm -rf nibbler

.PHONY: re
re: clean all

build/Makefile: CMakeLists.txt */CMakeLists.txt
	@mkdir -p build
	@(cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..)

.PHONY: SFML
SFML: build/Makefile
	@echo $(YELLOW)"\nCompiling third_party/$@ \n"$(RESET)
	@(cd build && cmake --build third_party/SFML -- -j)

.PHONY: GLFW
GLFW: build/Makefile
	@echo $(YELLOW)"\nCompiling third_party/$@ \n"$(RESET)
	@(cd build && cmake --build third_party/GLFW -- -j)

.PHONY: freetype2
freetype2: build/Makefile
	@echo $(YELLOW)"\nCompiling third_party/$@ \n"$(RESET)
	@(cd build && cmake --build third_party/freetype2 -- -j)

.PHONY: FTGL
FTGL: build/Makefile
	@echo $(YELLOW)"\nCompiling third_party/$@ \n"$(RESET)
	@(cd build && cmake --build third_party/FTGL -- -j)




.PHONY: lib_sfml
lib_sfml: build/Makefile
	@echo $(YELLOW)"\nCompiling $@ library\n"$(RESET)
	@(cd build && cmake --build lib_sfml -- -j)

.PHONY: lib_glfw
lib_glfw: build/Makefile
	@echo $(YELLOW)"\nCompiling $@ library\n"$(RESET)
	@(cd build && cmake --build lib_glfw -- -j)

.PHONY: lib_ncurses
lib_ncurses: build/Makefile
	@echo $(YELLOW)"\nCompiling $@ library\n"$(RESET)
	@(cd build && cmake --build lib_ncurses -- -j)

.PHONY: lib_sdl
lib_sdl: build/Makefile
	@echo $(YELLOW)"\nCompiling $@ library\n"$(RESET)
	@(cd build && cmake --build lib_sdl -- -j)

.PHONY: nibbler_core
nibbler_core: build/Makefile
	@echo $(YELLOW)"\nCompiling $@ \n"$(RESET)
	@(cd build && cmake --build nibbler_core -- -j)



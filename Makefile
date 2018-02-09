#----- Colors ------
BLACK 	= "\033[1;30m"
RED 	= "\033[1;31m"
GREEN 	= "\033[1;32m"
YELLOW 	= "\033[1;33m"
BLUE 	= "\033[1;34m"
MAGENTA = "\033[1;35m"
CYAN 	= "\033[1;35m"
PURPLE 	= "\033[1;36m"
WHITE 	= "\033[1;37m"
RESET 	= "\033[0;0m"
#-------------------

CXX			= clang++
# CXXFLAGS	= -std=gnu++14 -Wall -Wextra -Werror

NAME		= nibbler

#------ make ------
all: $(NAME)

$(NAME): $(CORE_OBJ)
	@make -C core/
	@make -C ncurses/
	
	@$(CXX) -lcurses -ldl -o $@ $^ -L. -lcore -fPIC 

	@echo $(GREEN) "\tnibbler\t\t\t- has been made\n"$(RESET)


#------ make clean ------

clean:
	@make clean -C core/
	@make clean -C ncurses/


#------ make fclean ------

fclean:
	@rm -f $(NAME)
	@make fclean -C core/
	@make fclean -C ncurses/

#------ make re ------
re: fclean all


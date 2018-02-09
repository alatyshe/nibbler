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

CXX				= clang++
# CXXFLAGS		= -std=gnu++14 -Wall -Wextra -Werror
CPPFLAGS		= -I./header
NCURSES_FLAGS	= -lncurses
DYN_LIB_FLAGS	= -shared -fPIC
LIBRARY			= -L../ -lcore

NAME			= ../libcurses.dylib


#------ path -------
NCURSES_PATH			= ./files
NCURSES_OBJECTS_PATH	= ./objects

#------ files ------
NCURSES_FILES	= Ncurses.class 

#------ other ------
NCURSES_OBJ		= $(addprefix $(NCURSES_OBJECTS_PATH)/, $(addsuffix .o, $(NCURSES_FILES)))


#------ make ------
all: $(NAME)

$(NAME): $(NCURSES_OBJ) 
	@echo $(CYAN) "\n\tCompiling $@"$(RESET)
	
	@$(CXX) $(NCURSES_FLAGS) $(DYN_LIB_FLAGS) $(LIBRARY) -o $(NAME) $^  
	
	@echo $(GREEN) "\tn_curses.so\t\t- has been made\n"$(RESET)

$(NCURSES_OBJECTS_PATH)/%.o: $(NCURSES_PATH)/%.cpp
	@echo $(PURPLE) "\tCompiling $<"$(RESET)
	@mkdir $(NCURSES_OBJECTS_PATH) 2> /dev/null || true

	@$(CXX) $(CXXFLAGS) -o $@ -c $<

#------ make clean ------

clean:
	@echo $(YELLOW)"\t\t\t\tN_CURSES"$(RESET)
	@rm -f $(NCURSES_OBJ)
	@rm -rf $(NCURSES_OBJECTS_PATH)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)

#------ make fclean ------

fclean:
	@echo $(YELLOW)"\t\t\t\tN_CURSES"$(RESET)
	@rm -f $(NAME)
	@rm -f $(NCURSES_OBJ)
	@rm -rf $(NCURSES_OBJECTS_PATH)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)
	@echo $(RED) "\tn_curses.so have been cleaned.\n"$(RESET)

#------ make re ------
re: fclean all


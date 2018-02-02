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


#------ path -------
CORE_PATH			= ./core/files
NCURSES_PATH		= ./ncurses/files


NCURSES_OBJECTS_PATH	= ./Ncurses/objects
CORE_OBJECTS_PATH		= ./core/objects


#------ files ------
CORE_FILES		= main Game Piece Exception Parser Lexer 
NCURSES_FILES	= n_Curses 

#------ other ------
CORE_OBJ		= $(addprefix $(CORE_OBJECTS_PATH)/, $(addsuffix .o, $(CORE_FILES)))
NCURSES_OBJ		= $(addprefix $(NCURSES_OBJECTS_PATH)/, $(addsuffix .o, $(NCURSES_FILES)))


#------ make ------
all: $(NAME)

$(NAME): $(CORE_OBJ) $(NCURSES_OBJ) 
	@echo "\n"
	@echo $(CYAN) "\tCompiling $@"$(RESET)
	@$(CXX) -lncurses -o $@ $^
	@echo $(GREEN) "\tnibbler\t\t- has been made\n"$(RESET)

$(CORE_OBJECTS_PATH)/%.o: $(CORE_PATH)/%.cpp
	@echo $(PURPLE) "\tCompiling $<"$(RESET)
	@mkdir $(CORE_OBJECTS_PATH) 2> /dev/null || true
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(NCURSES_OBJECTS_PATH)/%.o: $(NCURSES_PATH)/%.cpp
	@echo $(PURPLE) "\tCompiling $<"$(RESET)
	@mkdir $(NCURSES_OBJECTS_PATH) 2> /dev/null || true
	@$(CXX) $(CXXFLAGS) -o $@ -c $<


#------ make clean ------

clean:
	@echo $(YELLOW)"\t\t\t\tAVM"$(RESET)
	@rm -f $(CORE_OBJ)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@rm -rf $(CORE_OBJECTS_PATH)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)

#------ make fclean ------

fclean:
	@echo $(YELLOW)"\t\t\t\tAVM"$(RESET)
	@rm -f $(FILES_OBJ)
	@rm -f $(CORE_OBJ)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@rm -rf $(CORE_OBJECTS_PATH)
	@rm -rf $(NCURSES_OBJECTS_PATH)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)
	@rm -f $(NAME)
	@echo $(RED) "\tnibbler have been cleaned.\n"$(RESET)

#------ make re ------
re: fclean all


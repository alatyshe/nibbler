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
CXXFLAGS	= -std=gnu++14 -Wall -Wextra -Werror

NAME		= nibbler


#------ path -------
FILES_PATH		= ./files
OBJECTS_PATH	= ./objects


#------ files ------
FILES_FILES		= main Game Piece Exception Parser Lexer 

#------ other ------
FILES_OBJ		= $(addprefix $(OBJECTS_PATH)/, $(addsuffix .o, $(FILES_FILES)))


#------ make ------
all: $(NAME)

$(NAME): $(FILES_OBJ) 
	@echo "\n"
	@echo $(CYAN) "\tCompiling $@"$(RESET)
	@$(CXX) -lncurses -o $@ $^
	@echo $(GREEN) "\tnibbler\t\t- has been made\n"$(RESET)

$(OBJECTS_PATH)/%.o: $(FILES_PATH)/%.cpp
	@echo $(PURPLE) "\tCompiling $<"$(RESET)
	@mkdir $(OBJECTS_PATH) 2> /dev/null || true
	@$(CXX) $(CXXFLAGS) -o $@ -c $<


#------ make clean ------

clean:
	@echo $(YELLOW)"\t\t\t\tAVM"$(RESET)
	@rm -f $(FILES_OBJ)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@rm -rf $(OBJECTS_PATH)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)

#------ make fclean ------

fclean:
	@echo $(YELLOW)"\t\t\t\tAVM"$(RESET)
	@rm -f $(FILES_OBJ)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@rm -rf $(OBJECTS_PATH)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)
	@rm -f $(NAME)
	@echo $(RED) "\tnibbler have been cleaned.\n"$(RESET)

#------ make re ------
re: fclean all


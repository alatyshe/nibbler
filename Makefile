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

NAME			= ./nibbler


#------ path -------
CORE_PATH			= ./core/files
CORE_OBJECTS_PATH	= ./core/objects

#------ files ------
CORE_FILES		= main Game Piece Exception Parser Lexer

#------ other ------
CORE_OBJ		= $(addprefix $(CORE_OBJECTS_PATH)/, $(addsuffix .o, $(CORE_FILES)))


#------ make ------
all: $(NAME)

$(NAME): $(CORE_OBJ)
	@echo $(CYAN) "\n\tCompiling $@"$(RESET)
	
	@make -C ncurses/
	
	# @$(CXX) -lcurses -ldl -o $@ $^

	# @echo $(GREEN) "\tnibbler\t\t- has been made\n"$(RESET)

$(CORE_OBJECTS_PATH)/%.o: $(CORE_PATH)/%.cpp
	@echo $(PURPLE) "\tCompiling $<"$(RESET)
	
	@mkdir $(CORE_OBJECTS_PATH) 2> /dev/null || true
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

#------ make clean ------

clean:
	@echo $(YELLOW)"\t\t\t\tCORE"$(RESET)
	@rm -f $(CORE_OBJ)
	@rm -rf $(CORE_OBJECTS_PATH)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)
	
	@make clean -C ncurses/

#------ make fclean ------

fclean:
	@echo $(YELLOW)"\t\t\t\tCORE"$(RESET)
	@rm -f $(CORE_OBJ)
	@rm -rf $(CORE_OBJECTS_PATH)
	@rm -f $(NAME)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)
	@echo $(RED) "\tcore.a have been cleaned.\n"$(RESET)

	@make fclean -C ncurses/

#------ make re ------
re: fclean all


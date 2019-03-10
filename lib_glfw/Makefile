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

NAME			= ../libglfw.dylib
CXX				= clang++

#------ path -------
LIB_PATH			= ./
LIB_OBJECTS_PATH	= ./objects

#------ files ------
CORE_FILES			= main

CORE_OBJ			= $(addprefix $(CORE_OBJECTS_PATH)/, $(addsuffix .o, $(CORE_FILES)))

CPPFLAGS			?=	-std=c++11
# CPPFLAGS			+=  -Wall -Wextra -Werror 
CPPFLAGS			+=	-pedantic -g3 -std=c++11 -stdlib=libc++
CPPFLAGS			+=	-Iglfw/include 

LDFLAGS				=	-framework Cocoa -framework OpenGL -framework CoreVideo -framework IOKit 
# 
LDFLAGS				+=	-framework GLUT
LDFLAGS				+=	-force_load ./glfw/src/libglfw3.a -shared -fPIC
# ../include
# LDFLAGS		=	-shared -undefined dynamic_lookup
# -fPIC


#------ path -------
LIB_PATH			= ./
LIB_OBJECTS_PATH	= ./objects

#------ files ------
LIB_FILES	= glfw.class 

#------ other ------
LIB_OBJ		= $(addprefix $(LIB_OBJECTS_PATH)/, $(addsuffix .o, $(LIB_FILES)))



all: $(NAME)

$(NAME): $(LIB_OBJ) 
	@echo $(CYAN) "\n\tCompiling $@"$(RESET)
	
	@$(CXX) $(LDFLAGS) -o $(NAME) $^  
	
	@echo $(GREEN) "\tlibcurses.dylib\t\t- has been made\n"$(RESET)

# Прописываем флаги для компиляции cpp файлов, им так же нужно прописывать место, где находиться либа
$(LIB_OBJECTS_PATH)/%.o: $(LIB_PATH)/%.cpp
	@echo $(PURPLE) "\tCompiling $<"$(RESET)
	@mkdir $(LIB_OBJECTS_PATH) 2> /dev/null || true

	@$(CXX) $(CPPFLAGS) -o $@ -c $<

#------ make clean ------

clean:
	@echo $(YELLOW)"\t\t\t\tGLDW"$(RESET)
	@rm -f $(LIB_OBJ)
	@rm -rf $(LIB_OBJECTS_PATH)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)

#------ make fclean ------

fclean:
	@echo $(YELLOW)"\t\t\t\tGLDW"$(RESET)
	@rm -f $(NAME)
	@rm -f $(LIB_OBJ)
	@rm -rf $(LIB_OBJECTS_PATH)
	@echo $(RED) "\t.o files have been cleaned."$(RESET)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)
	@echo $(RED) "\tlibcurses.dylib have been cleaned.\n"$(RESET)

#------ make re ------
re: fclean all


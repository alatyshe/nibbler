CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

project(ncurses_lib)
set(NCURSES_LIB
  Ncurses.class.cpp
)

# Main library
add_library(ncurses_lib ${NCURSES_LIB})
target_link_libraries(ncurses_lib
	ncurses)


# target_link_libraries(elfgames_checkers PUBLIC
#     cppzmq
#     elf
# )

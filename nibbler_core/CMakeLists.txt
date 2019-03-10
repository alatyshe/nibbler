CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

project(nibbler)
set(NIBBLER_EXEC
  files/Exception.cpp
  files/Parser.cpp
  files/Piece.cpp
  files/Game.cpp
  files/main.cpp
)

   
# Executble
add_executable(nibbler ${NIBBLER_EXEC})


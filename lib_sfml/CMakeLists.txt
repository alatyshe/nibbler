CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

project(sfml_lib)
set(SFML_LIB
  sfml.class.cpp
)

# Library
add_library(sfml_lib ${SFML_LIB})
target_link_libraries(sfml_lib
  sfml-graphics 
  sfml-window 
  sfml-system)

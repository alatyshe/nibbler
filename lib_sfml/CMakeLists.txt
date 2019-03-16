CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

project(sfml_main)
set(SFML_EXEC
  main.cpp
)

project(sfml_lib)
set(SFML_LIB
  Sfml.class.cpp
)

# Main library
add_library(sfml_lib ${SFML_LIB})
target_link_libraries(sfml_lib
  sfml-graphics 
  sfml-window 
  sfml-system)
    
# Executble
add_executable(sfml_main ${SFML_EXEC})
target_link_libraries(sfml_main
  sfml-graphics 
  sfml-window 
  sfml-system)


# target_link_libraries(elfgames_checkers PUBLIC
#     cppzmq
#     elf
# )

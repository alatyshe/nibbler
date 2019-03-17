CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# project(sfml_main)
# set(SFML_EXEC
#   main.cpp
# )
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

project(glfw_lib)
set(GLFW_LIB
  glfw.class.cpp
)

find_package(OpenGL REQUIRED)
# target_link_libraries(glfw_lib ${OPENGL_gl_LIBRARY})

# Main library
add_library(glfw_lib ${GLFW_LIB})
# target_include_directories(glfw_lib ${OPENGL_INCLUDE_DIR})
target_link_libraries(glfw_lib 
	glfw
	${OPENGL_gl_LIBRARY})
# target_link_libraries(sfml_lib
#   sfml-graphics 
#   sfml-window 
#   sfml-system)
    



# Executble
# add_executable(sfml_main ${SFML_EXEC})
# target_link_libraries(sfml_main
#   sfml-graphics 
#   sfml-window 
#   sfml-system)


# target_link_libraries(elfgames_checkers PUBLIC
#     cppzmq
#     elf
# )

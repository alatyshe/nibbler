CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

project(glfw_lib)
set(GLFW_LIB
  glfw.class.cpp
)

find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

# Main library
add_library(glfw_lib ${GLFW_LIB})
target_link_libraries(glfw_lib 
	glfw
	ftgl
	${OPENGL_gl_LIBRARY}
	${FREETYPE_LIBRARIES})

    

# project(glfw_main)
# set(SFML_EXEC
#   main.cpp
# )
# # Executble
# add_executable(glfw_main ${SFML_EXEC})
# target_link_libraries(glfw_main
#   glfw
# 	${OPENGL_gl_LIBRARY}
# 	${FREETYPE_LIBRARIES})




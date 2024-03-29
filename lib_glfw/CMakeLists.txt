CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

project(glfw_lib)
set(GLFW_LIB
  glfw_lib.class.cpp
)

find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

# Library
add_library(glfw_lib ${GLFW_LIB})
target_link_libraries(glfw_lib 
	glfw
	ftgl
	${OPENGL_gl_LIBRARY}
	${FREETYPE_LIBRARIES})

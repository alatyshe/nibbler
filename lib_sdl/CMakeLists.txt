CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)


include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})

project(sdl2_lib)
set(SDL_LIB
  Sdl.class.cpp
)

# Main library
add_library(sdl2_lib ${SDL_LIB})
target_link_libraries(sdl2_lib
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES})

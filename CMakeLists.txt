cmake_minimum_required(VERSION 3.3)

# Add Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/SFML/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/GLFW/include)

add_subdirectory(
    third_party
    ${CMAKE_CURRENT_BINARY_DIR}/third_party)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build/third_party/SFML/lib)


# Global compiler config
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS
#     "${CMAKE_CXX_FLAGS} -g -Wno-deprecated-declarations -fPIC -march=native")
# -g
# set(CMAKE_CXX_FLAGS
#     "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wno-register -Wno-deprecated-declarations -fPIC -march=native")

# add_subdirectory(
#     lib_glfw
#     ${CMAKE_CURRENT_BINARY_DIR}/lib_sfml)

add_subdirectory(
    lib_sfml
    ${CMAKE_CURRENT_BINARY_DIR}/lib_sfml)

add_subdirectory(
    lib_glfw
    ${CMAKE_CURRENT_BINARY_DIR}/lib_glfw)

add_subdirectory(
    lib_ncurses
    ${CMAKE_CURRENT_BINARY_DIR}/lib_ncurses)

add_subdirectory(
    nibbler_core
    ${CMAKE_CURRENT_BINARY_DIR}/nibbler_core)


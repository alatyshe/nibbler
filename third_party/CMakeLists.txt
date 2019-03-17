CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

# These projects all have CMakeLists by default, thank you devs!

add_subdirectory(SFML)
add_library(SFML SHARED IMPORTED)

add_subdirectory(glfw)
add_library(glfw SHARED IMPORTED)
# target_include_directories(SFML INTERFACE ${SFML_ROOT_DIR})
# target_include_directories(SFML SYSTEM INTERFACE SFML)
# target_include_directories(SFML SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include)




# add_library(SFML INTERFACE)



# target_include_directories(SFML INTERFACE
#     ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include
# )

# TBB

# set(TBB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/tbb/)
# set(TBB_ROOT ${TBB_ROOT} PARENT_SCOPE)
# include(${TBB_ROOT}/cmake/TBBBuild.cmake)
# tbb_build(
#     TBB_ROOT ${TBB_ROOT}
#     MAKE_ARGS tbb_build_dir=${CMAKE_CURRENT_BINARY_DIR}/tbb/
#     CONFIG_DIR TBB_DIR)
# set(TBB_DIR ${TBB_DIR} PARENT_SCOPE)

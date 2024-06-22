cmake_minimum_required(VERSION 3.01)
project(OSM_roads_parser_cpp)
include_directories("/home/anton/Desktop/OSM_roads_parser_cpp_act/rapidxml-1.13")
include_directories("/home/anton/Desktop/OSM_roads_parser_cpp_act/CImg-3.4.0")

#include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

add_subdirectory(SDL-release-2.30.4)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 20)

add_executable(OSM_roads_parser_cpp
        src/main.cpp
        src/osm_parser.cpp
        include/osm_parser.h
        include/rapidxml_ext.hpp
#        src/render.cpp
#        include/render.h
        src/render_stb.cpp
        include/render_stb.h)

#add_executable(OSM_roads_get_osm_cpp
#        src/get_osm.cpp
#        include/get_osm.h)

target_link_libraries(OSM_roads_parser_cpp PRIVATE SDL2)
cmake_minimum_required(VERSION 3.28)
project(OSM_roads_parser_cpp)
include_directories("./rapidxml-1.13")
include_directories("./CImg-3.4.0")
#find_package(ImageMagick)
#find_package(ImageMagick COMPONENTS Magick++)
#find_package(ImageMagick COMPONENTS convert)
#find_package(ImageMagick COMPONENTS Magick++ convert)

#include_directories(${ImageMagick_INCLUDE_DIRS})
#target_link_libraries(OSM_roads_parser_cpp ${ImageMagick_LIBRARIES})

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 20)

add_executable(OSM_roads_parser_cpp
        src/main.cpp
        src/osm_parser.cpp
        include/osm_parser.h
        include/rapidxml_ext.hpp
        src/render.cpp
        include/render.h)

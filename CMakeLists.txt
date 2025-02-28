cmake_minimum_required(VERSION 3.10)

PROJECT(extMySQL)

# verbose makefiles
#SET(CMAKE_VERBOSE_MAKEFILE ON)
# this helps debugging dependencies - a lot :)
#SET_PROPERTY(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE 1)

INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(MySQL)

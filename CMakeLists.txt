cmake_minimum_required(VERSION 3.0)
project(samhanshat)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/ )


set(SOURCES
	src/Path.cpp
	src/Station.cpp
	src/Request.cpp
	src/City.cpp
	src/main.cpp
)

add_executable(app ${SOURCES})

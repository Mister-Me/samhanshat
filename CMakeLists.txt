cmake_minimum_required(VERSION 3.2)
project(samhanshat)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/ )


set(SOURCES
	src/City.cpp
	src/Station.cpp
	src/Path.cpp
	src/Cost.cpp
	src/Request.cpp
	src/Time.cpp
	src/main.cpp
)

add_executable(app ${SOURCES})

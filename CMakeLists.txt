cmake_minimum_required(VERSION 3.0)
project(project)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/ )


set(SOURCES
   src/
   
)

add_executable(app ${SOURCES})

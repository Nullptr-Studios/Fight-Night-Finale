cmake_minimum_required(VERSION 3.30)
project(fight_night_finale)

set(CMAKE_CXX_STANDARD 26)

include_directories(inc)

add_executable(fnf src/main.cpp)
target_link_directories(fnf PUBLIC lib)
target_link_libraries(fnf PUBLIC aecore)

cmake_minimum_required(VERSION 3.29)
project(game_of_life)

set(CMAKE_CXX_STANDARD 20)

add_executable(game_of_life main.c
                            logic.h
                            constants.h
                            logic.c
)

set(CMAKE_INCLUDE_CURRENT_DIR)

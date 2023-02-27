cmake_minimum_required(VERSION 3.23)
project(Assignment4Zombies)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Assignment4Zombies main.cpp classes/Human.cpp classes/City.cpp classes/Organism.cpp classes/GameSpecs.cpp classes/Zombie.cpp)

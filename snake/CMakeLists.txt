cmake_minimum_required(VERSION 3.23)
project(hackathonProjrct)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

add_executable(hackathonProjrct main.cpp)

target_link_libraries(hackathonProjrct sfml-system sfml-window sfml-graphics sfml-audio)

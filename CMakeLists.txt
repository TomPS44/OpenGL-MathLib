cmake_minimum_required(VERSION 3.10)
project(BaseGameEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

message(STATUS "Configuration terminée pour ${PROJECT_NAME} sur le disque U: !")
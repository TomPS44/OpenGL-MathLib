cmake_minimum_required(VERSION 3.10)
project(MathLib VERSION 0.1)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(include)
target_include_directories(${PROJECT_NAME} PRIVATE include)

message(STATUS "Compilation réussie ! Le fichier ${PROJECT_NAME}.exe a été créé :)")
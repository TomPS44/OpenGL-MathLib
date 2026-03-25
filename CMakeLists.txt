cmake_minimum_required(VERSION 3.10)
project(MathLib VERSION 0.1)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(include)
target_include_directories(${PROJECT_NAME} PRIVATE include)

message(STATUS "Compilation réussie ! Le fichier ${PROJECT_NAME}.exe a été créé :)")


# cmake_minimum_required(VERSION 3.10)
# project(GLMath VERSION 1.0.0 LANGUAGE CXX)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# file(GLOB_RECURSE SOURCES "include/*.hpp" "include/*.inl")

# add_library(GLMath INTERFACE ${SOURCES})
# target_include_directories(GLMath PUBLIC include)

# if (MSVC)
#     target_compile_options(...)
# else ()
#     target_compile_options(...)
# endif()




cmake_minimum_required(VERSION 3.10)
project(MathLib VERSION 0.1)

# On force le C++20 (important pour les littéraux et les templates modernes)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. On définit explicitement les sources 
set(SOURCES 
    main.cpp
    # Ajoute ici tes autres fichiers .cpp du dossier src au fur et à mesure
)

# 2. Création de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# 3. Gestion des includes
# PRIVATE : seul ton moteur voit le dossier include
# PUBLIC : si tu créais une lib, ceux qui l'utilisent verraient aussi les headers
target_include_directories(${PROJECT_NAME} PRIVATE include)

message(STATUS "Compilation réussie ! Le fichier ${PROJECT_NAME}.exe a été créé :)")
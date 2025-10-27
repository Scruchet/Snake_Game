# =========================================
# CMake configuration pour le projet SNAKE
# =========================================

cmake_minimum_required(VERSION 3.10)
project(SNAKE VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(RES_EMBEDDED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/colors/resources_embedded)
set(SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/scripts/generation_header.sh)
set(TEXTURE_HEADER ${INCLUDE_DIR}/textures.h)

file(MAKE_DIRECTORY ${INCLUDE_DIR})
file(MAKE_DIRECTORY ${RES_EMBEDDED_DIR})

# Récupération des fichiers assets
file(GLOB ASSETS "${ASSETS_DIR}/*")

# 💡 Commande pour exécuter le script
add_custom_command(
    OUTPUT ${TEXTURE_HEADER}
    COMMAND ${CMAKE_COMMAND} -E echo "📦 Génération du fichier unique textures.h et des .h embarqués..."
    COMMAND bash ${SCRIPT} ${ASSETS} ${SCRIPT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Création de fichiers embarqués"
)

# 💡 Cible personnalisée pour forcer la génération
add_custom_target(generate_textures ALL
    DEPENDS ${TEXTURE_HEADER}
)

# ================================
# Fichiers sources du projet
# ================================
set(SOURCES
    src/main.cpp
    src/snake.cpp
    src/food.cpp
    src/game.cpp
)

add_executable(main ${SOURCES})

# Le binaire dépend du header généré
add_dependencies(main generate_textures)

target_include_directories(main PUBLIC ${INCLUDE_DIR})
target_link_libraries(main sfml-graphics sfml-window sfml-system)

message(STATUS "✅ Configuration terminée : textures intégrées automatiquement dans l’exécutable")

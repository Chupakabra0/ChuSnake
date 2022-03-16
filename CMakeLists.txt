# ------------------ HEADER -------------------- #

cmake_minimum_required(VERSION 3.0)
project(ChuSnake LANGUAGES CXX)

# ------------------ SETS -------------------- #

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Let SFML static linking
set(SFML_STATIC_LIBRARIES TRUE)

# Set CMake module path
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

# Set .exe name var
set(EXECUTABLE_NAME ${PROJECT_NAME})

# Set var dirs
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(LIB_DIR "${SOURCE_DIR}/lib")

set(SFML_DIR "${LIB_DIR}/SFML-2.5.1/lib/cmake/SFML")
set(FMT_DIR "${LIB_DIR}/fmt-8.1.1")

# ------------------ SUBDIRS -------------------- #

# fmt subdir
add_subdirectory(${FMT_DIR} EXCLUDE_FROM_ALL)

# ------------------ EXECUTABLES -------------------- #

add_executable(${EXECUTABLE_NAME}
        ${SOURCE_DIR}/Main.cpp
        ${SOURCE_DIR}/GameBoard.hpp
        src/GameWindow.hpp
        src/GameVars.hpp
        src/Snake.hpp
        src/Apple.hpp
        src/GameTime.hpp
        src/Utils.hpp
        src/GameWindow.cpp
        src/Snake.cpp)

# ------------------ LINK LIBS -------------------- #

target_link_libraries(${EXECUTABLE_NAME} sfml-graphics fmt::fmt-header-only)

# ------------------ PACKAGES -------------------- #
find_package(SFML 2.5.1 REQUIRED graphics)

cmake_minimum_required(VERSION 3.16)

project(leak4 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set (CMAKE_PREFIX_PATH "C:\\msys64\\mingw64\\include\\qt6\\")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)

qt_add_executable(leak4
  view/app.cc
  view/MainWindow.h
)

target_link_libraries(leak4 PUBLIC Qt::Widgets)
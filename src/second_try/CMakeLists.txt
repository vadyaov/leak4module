cmake_minimum_required(VERSION 3.16)

project(leak VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set (CMAKE_PREFIX_PATH "C:\\msys64\\mingw64\\include\\qt6\\")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Charts)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)

qt_add_executable(leak
  view/app.cc

  view/MainWindow.h view/MainWindow.cc

  view/button.h view/button.cc
  view/GroupBox.h

  model/variants.h model/variants.cc
  model/release.h model/release.cc
  model/nuclides.h model/nuclides.cc
  model/nuclide.h model/nuclide.cc
)

target_link_libraries(leak PUBLIC Qt6::Widgets Qt6::Charts)
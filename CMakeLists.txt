cmake_minimum_required(VERSION 3.15)
project(sfml-imgui-labs
  LANGUAGES CXX
  VERSION 1.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(dependencies)
add_subdirectory(src)

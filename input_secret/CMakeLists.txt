cmake_minimum_required (VERSION 3.8)

project ("inputSecret")

add_executable (inputSecret "inputSecret.cpp" "inputSecret.h")

find_package(FLTK 1.4 CONFIG REQUIRED)

set_property(TARGET inputSecret PROPERTY CXX_STANDARD 20)

target_link_libraries(inputSecret PRIVATE fltk::fltk)


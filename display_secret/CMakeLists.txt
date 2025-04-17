cmake_minimum_required (VERSION 3.8)

project ("displaySecret")

add_executable (displaySecret "displaySecret.cpp")

find_package(FLTK 1.4 CONFIG REQUIRED)

target_link_libraries(displaySecret PRIVATE fltk::fltk)


cmake_minimum_required(VERSION 3.0)

project(template_clojure)

add_executable(template_clojure main.cpp)

install(TARGETS template_clojure RUNTIME DESTINATION bin)

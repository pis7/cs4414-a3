cmake_minimum_required(VERSION 3.12)
project(PTree VERSION 1.0.0)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.hpp")

add_executable(ptree ${SOURCES} ${HEADERS})
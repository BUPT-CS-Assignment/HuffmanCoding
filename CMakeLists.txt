cmake_minimum_required(VERSION 3.0.0)
project(HuffmanCoding VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(HuffmanCoding Main.cpp Document.cpp Readin.cpp Encode.cpp Decode.cpp )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

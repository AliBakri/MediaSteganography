cmake_minimum_required(VERSION 3.20)
project(Steganography)

set(CMAKE_CXX_STANDARD 17)

add_executable(Encoder Encoder.cpp)
add_executable(Decoder Decoder.cpp)
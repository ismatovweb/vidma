cmake_minimum_required(VERSION 3.10)
project(Vidma VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vidma
    src/main.cpp
)

target_include_directories(vidma PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

target_link_libraries(vidma PRIVATE
    Threads::Threads
    OpenSSL::Crypto
)

install(TARGETS vidma RUNTIME DESTINATION bin)

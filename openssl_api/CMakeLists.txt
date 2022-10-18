cmake_minimum_required(VERSION 3.23)
project(openssl_api C)

set(CMAKE_C_STANDARD 99)

add_executable(openssl_api main.c main.c)
target_link_libraries(${PROJECT_NAME} PUBLIC ssl crypto )
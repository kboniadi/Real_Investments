cmake_minimum_required(VERSION 3.17)
project(real_investments C)

set(CMAKE_C_STANDARD 99)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")


add_executable(real_investments main.c
                                DEAL.c
                                DEAL.h)

target_link_libraries(real_investments m)
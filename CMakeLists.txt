# ------------------------- Project settings --------------------------------
project(bane LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5.1)


set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O0 -g -Wall -Werror -Weverything -Wno-c++98-compat-pedantic -Wno-disabled-macro-expansion -Wno-padded -Wno-weak-vtables -pedantic-errors -Wno-global-constructors -Wno-exit-time-destructors  -isystem .. -I ../src/lib -DBOOST_LOG_DYN_LINK")
set(CMAKE_EXE_LINKER_FLAGS "-fuse-ld=gold ")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")

#find_package (Boost 1.58 COMPONENTS system program_options signals log REQUIRED)
find_package (Boost 1.58 COMPONENTS system program_options signals  REQUIRED)
#find_package(Threads)

file(GLOB_RECURSE proj_lib_sources src/lib/*.cpp)

set(PROJECT_NAME_LIB ${PROJECT_NAME}_lib)
add_library(${PROJECT_NAME}_lib OBJECT ${proj_lib_sources} 
)

target_include_directories (${PROJECT_NAME_LIB} 
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(${PROJECT_NAME} 
    $<TARGET_OBJECTS:${PROJECT_NAME_LIB}> src/main.cpp)
target_link_libraries(${PROJECT_NAME}  
    -lboost_system
    -lboost_program_options
    -lboost_log
    -lboost_log_setup
    -lboost_thread
    -lboost_locale
    -lncursesw
    -lpthread
)


cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(yaya_testing_libs)

include(FetchContent)

if(NOT TARGET yaya_memory)
    FetchContent_Declare(c_lib_memory
      GIT_REPOSITORY "https://github.com/seityaya/c_lib_memory.git"
      GIT_TAG "origin/master"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/libs/c_lib_memory"
    )
    FetchContent_MakeAvailable(c_lib_memory)
endif()

if(NOT TARGET yaya_macro)
    FetchContent_Declare(c_lib_macro
      GIT_REPOSITORY "https://github.com/seityaya/c_lib_macro.git"
      GIT_TAG "origin/master"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/libs/c_lib_macro"
    )
    FetchContent_MakeAvailable(c_lib_macro)
endif()

if(NOT TARGET yaya_arithmetic)
    FetchContent_Declare(c_lib_arithmetic
      GIT_REPOSITORY "https://github.com/seityaya/c_lib_arithmetic.git"
      GIT_TAG "origin/master"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/libs/c_lib_arithmetic"
    )
    FetchContent_MakeAvailable(c_lib_arithmetic)
endif()








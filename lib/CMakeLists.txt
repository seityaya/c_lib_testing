#Author                 : Seityagiya Terlekchi
#Contacts               : seityaya@ukr.net
#Creation Date          : 2022.12
#License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
#SPDX-License-Identifier: LGPL-2.1-or-later
#Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 11)
add_definitions(-std=c11)

set(VERSION 0.1)
set(PROJECT_NAME yaya_unit)
project(${PROJECT_NAME})

set(SRC_LIST yaya_unit.c)
set(INC_LIST yaya_unit.h
    yaya_unit_macro.h)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST} ${INC_LIST})

if (NOT TARGET yaya_defines)
    add_subdirectory(${CMAKE_SOURCE_DIR}/../../yaya_defines/lib/ yaya_defines)
    target_include_directories(${PROJECT_NAME} PUBLIC ../../yaya_defines/lib/)
    target_link_libraries(${PROJECT_NAME} yaya_defines)
endif()

#Author                 : Seityagiya Terlekchi
#Contacts               : terlekchiseityaya@gmail.com
#Creation Date          : 2022.12
#License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
#SPDX-License-Identifier: LGPL-2.1-or-later
#Copyright © 2022-2025 Seityagiya Terlekchi. All rights reserved.

cmake_minimum_required(VERSION 3.0)

project(yaya_testing_using)

set(CMAKE_C_STANDARD 11)

file(GLOB FILES
    *.c
    *.h
)

set(SOURSE_LIST
    ${FILES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC yaya_testing)

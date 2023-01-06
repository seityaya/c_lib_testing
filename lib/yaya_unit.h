//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2022 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_UNIT_H
#define YAYA_UNIT_H

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "string.h"
#include "math.h"
#include "stdio.h"

#include "yaya_unit_func.h"

#define UNIT_TEST_MESG_SIZE 1024

/*Генерирование заголовка функции*/
#define UNIT_TEST_GENERATE_FUNC(NAME)      bool UTF_##NAME(unit_func_info_t *info)

/*Генерирование структуры списка функций*/
#define UNIT_TEST_GENERATE_ST(NAME)        { UTF_##NAME, #NAME, false, {0} },
#define UNIT_TEST_GENERATE_ST_BEG          { NULL,        NULL, false, {0} },
#define UNIT_TEST_GENERATE_ST_END          { NULL,        NULL, false, {0} },

typedef struct unit_func_info_t {
    bool result;
    intmax_t test_flag;
    intmax_t test_count;

    char file[UNIT_TEST_MESG_SIZE];
    uintmax_t line;

    char mesg[UNIT_TEST_MESG_SIZE];    /*сообщение об ошибке*/

    char value[UNIT_TEST_MESG_SIZE];
    char expec[UNIT_TEST_MESG_SIZE];
    char count[UNIT_TEST_MESG_SIZE];
} unit_func_info_t;

typedef struct unit_test_func_t {         /*список токенов*/
    bool (*func)(unit_func_info_t *info); /*функция теста*/
    const char *name;                     /*текстовое название теста*/
    bool pass;                            /*прохождение теста*/

    unit_func_info_t info;
} unit_test_func_t;

typedef struct unit_test_sett_t {
    bool print_now;
}unit_test_sett_t;

typedef struct unit_test_t {
    unit_test_func_t *list;          /*указатель на массив с тестами*/
    unit_test_sett_t *sett;          /*указатель на массив с тестами*/
    uintmax_t count_test_all;        /*общее количество тестов*/
    uintmax_t count_test_running;    /*количество запущенных  тестов*/
    uintmax_t count_test_completed;  /*количество завершенных тестов*/
    uintmax_t count_test_successful; /*количество успешных    тестов*/
    uintmax_t count_test_failure;    /*количество неудачных   тестов*/
}unit_test_t;

bool unit_test_init(unit_test_t *info, unit_test_func_t *list, unit_test_sett_t *sett);
//bool unit_test_push(unit_test_info_t *info, const char *name, bool (*func)(char *mesg));
//bool unit_test_free();

bool unit_test_start_all(unit_test_t *info);

bool unit_test_print_stats(unit_test_t *info);
bool unit_test_print_result(unit_test_t *info);

#endif /*YAYA_UNIT_H*/

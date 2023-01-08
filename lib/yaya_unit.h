//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_UNIT_H
#define YAYA_UNIT_H

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "string.h"
#include "math.h"
#include "stdio.h"

#include "yaya_unit_macro.h"

typedef struct unit_test_stat_t {
    uintmax_t count_test_running;    /*количество запущенных  тестов*/
    uintmax_t count_test_completed;  /*количество завершенных тестов*/
    uintmax_t count_test_successful; /*количество успешных    тестов*/
    uintmax_t count_test_failure;    /*количество неудачных   тестов*/
    uintmax_t group;
}unit_test_stat_t;

typedef struct unit_test_func_t {
    void (*func)(unit_test_stat_t* stat);
} unit_test_func_t;

typedef struct unit_test_t {
    unit_test_func_t *list;           /*указатель на массив с функциями*/
    uintmax_t count_test_func;        /*общее количество функций с тестами*/
    unit_test_stat_t  stat;           /*статистика*/
}unit_test_t;

bool unit_test_init (unit_test_t *info, unit_test_func_t *list);
bool unit_test_start(unit_test_t *info);
bool unit_test_print(unit_test_t *info);
bool unit_test_stats(unit_test_t *info);

bool __unit_test_last_status(unit_test_stat_t *stat);
void __unit_test_group_beg(unit_test_stat_t *stat, char* name);
void __unit_test_group_end(unit_test_stat_t* stat);

void __unit_test_block_beg(unit_test_stat_t *stat, char* name);
void __unit_test_block_init(unit_test_stat_t* stat);
void __unit_test_block_test(unit_test_stat_t* stat);
void __unit_test_block_free(unit_test_stat_t* stat);
void __unit_test_block_end(unit_test_stat_t* stat);

void __unit_test_group_ext(unit_test_stat_t* stat, char* mesg);
void __unit_test_group_ret(unit_test_stat_t* stat, char* mesg);
void __unit_test_group_brk(unit_test_stat_t* stat, char* mesg);
void __unit_test_group_msg(unit_test_stat_t* stat, char* mesg);

void __unit_test_assert_info(unit_test_stat_t* stat, char* name_test, char* ACT, char* EXT, char* EPS);
void __unit_test_assert_beg(unit_test_stat_t* stat);
void __unit_test_assert_end(unit_test_stat_t* stat);
void __unit_test_assert_suce(unit_test_stat_t* stat);
void __unit_test_assert_feil(unit_test_stat_t* stat);

#endif /*YAYA_UNIT_H*/

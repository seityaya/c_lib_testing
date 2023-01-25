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

#include "yaya_unit_macro.h"

typedef enum group_t{
    UT_NULL,
    UT_GROUP_T,
    UT_BLOCK_T,
    UT_BLOCK_INIT_T,
    UT_BLOCK_TEST_T,
    UT_BLOCK_FREE_T,
    UT_MESEGE_T,
}group_t;

typedef enum last_staus_t{
    UT_SUCE,
    UT_FAIL,
    UT_SKIP,
}last_staus_t;

typedef struct unit_test_tree_t{
    char*   name;
    group_t type;
}unit_test_tree_t;

typedef struct unit_test_stat_t {
    bool init;                       /*флаг инициализации теста*/
    bool run;                        /*флаг запуска теста*/
    bool out;                        /*флаг вывода  текта*/

    uintmax_t count_test_assert;     /*количество всех        тестов*/
    uintmax_t count_test_running;    /*количество запущенных  тестов*/
    uintmax_t count_test_successful; /*количество успешных    тестов*/
    uintmax_t count_test_failure;    /*количество неудачных   тестов*/

    uintmax_t group_count_current;         /*Глубина групп*/
    uintmax_t group_count_max;             /*Глубина групп*/
    uintmax_t group_len_current;           /*Глубина групп*/
    uintmax_t group_len_max;               /*Глубина групп*/
    unit_test_tree_t group[1024];          /*Название групп*/

    const char* file;
    const char* func;
    uintmax_t line;

    uintmax_t last_staus;
    char* last_test;

    uintmax_t param;

    char* val_macro_str;
    char* exp_macro_str;
    char* eps_macro_str;

    char val_value_str[1024];
    char exp_value_str[1024];
    char eps_value_str[1024];
}unit_test_stat_t;

typedef struct {
    bool map;
    bool suse;
    bool stat;
    bool fold;
} unit_test_sett_t;

typedef struct unit_test_func_t {
    void (*func)(void*);
    uintmax_t run_count;
} unit_test_func_t;

typedef struct unit_test_t {
    uintmax_t count_test_func;        /*общее количество функций с тестами*/
    unit_test_func_t *list;           /*указатель на массив структур с функциями*/
    unit_test_sett_t *sett;           /*указатель на структуру с настройками*/
    unit_test_stat_t *stat;           /*статистика*/
}unit_test_t;



bool unit_test_init(unit_test_t *ut_main, unit_test_func_t *list, unit_test_sett_t* sett);
bool unit_test_start(unit_test_t *ut_main);
bool unit_test_print(unit_test_t *ut_main);
bool unit_test_stats(unit_test_t *ut_main);

void __unit_test_print(unit_test_t *ut_main);
bool __unit_test_last_status(unit_test_t *ut_main);
void __unit_test_group_beg(unit_test_t *ut_main, char* name);
void __unit_test_group_end(unit_test_t *ut_main);

void __unit_test_block_beg(unit_test_t *ut_main, char* name);
void __unit_test_block_init(unit_test_t *ut_main);
void __unit_test_block_test(unit_test_t *ut_main);
void __unit_test_block_free(unit_test_t *ut_main);
void __unit_test_block_end(unit_test_t *ut_main);

void __unit_test_group_ext(unit_test_t *ut_main, char* mesg);
void __unit_test_group_ret(unit_test_t *ut_main, char* mesg);
void __unit_test_group_brk(unit_test_t *ut_main, char* mesg);
void __unit_test_group_msg(unit_test_t *ut_main, char* mesg);

void __unit_test_assert_info(unit_test_t *ut_main,
                             const char* file, const char* func, const uintmax_t line,
                             char* name_test, ut_list_t ut_list,  uintmax_t param,
                             char* ACT, char* EXT, char* EPS);

void __unit_test_assert_val(unit_test_t *ut_main,
                            void*  ACT_P, void*  EXT_P, void*  EPS_P,
                            int8_t ACT_l, int8_t EXT_l, int8_t EPS_l,
                            int8_t ACT_T, int8_t EXT_T, int8_t EPS_T,
                            char   ACT_N, char   EXT_N, char   EPS_N,
                            char*  ACT_S, char*  EXT_S, char*  EPS_S,
                            char*  ACT_s, char*  EXT_s, char*  EPS_s);

void __unit_test_assert_beg(unit_test_t *ut_main);
void __unit_test_assert_end(unit_test_t *ut_main);
void __unit_test_assert_suce(unit_test_t *ut_main);
void __unit_test_assert_feil(unit_test_t *ut_main);

#endif /*YAYA_UNIT_H*/

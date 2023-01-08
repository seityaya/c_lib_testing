//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

#include "yaya_unit.h"
#include "inttypes.h"

bool unit_test_init(unit_test_t *info, unit_test_func_t *list) {
    if(info == NULL){ return false; }
    if(list == NULL){ return false; }

    info->list = list;

    {
        if(info->list[0].func != NULL){
            info->count_test_func = 0;
        }else{
            for (uintmax_t i = 1; i < __UINTMAX_MAX__; i++) {
                if(info->list[i].func == NULL){
                    info->count_test_func = i - 1;
                    break;
                }
            }
        }
    }

    return true;
}
bool unit_test_start(unit_test_t *info){
    if(info       == NULL){ return false; }
    if(info->list == NULL){ return false; }

    for (uintmax_t i = 1; i <= info->count_test_func; i++) {
        info->list[i].func(&info->stat);
    }

    return true;
}
bool unit_test_stats(unit_test_t *info){
    printf("==========\n");
    printf("FUNC    %" PRIuMAX "\n", info->count_test_func);
    printf("RUN     %" PRIuMAX "\n", info->stat.count_test_running);
    printf("COMPLET %" PRIuMAX "\n", info->stat.count_test_completed);
    printf("SUCCES  %" PRIuMAX "\n", info->stat.count_test_successful);
    printf("FAILURE %" PRIuMAX "\n", info->stat.count_test_failure);
    printf("==========\n");
    return true;
}

bool unit_test_print(unit_test_t *info){

}

bool __unit_test_last_status(unit_test_stat_t *stat){
    return true;
}

void __unit_test_group_beg(unit_test_stat_t* stat, char* name){
    stat->group++; printf("   | %*s G:%s\n", stat->group * 2, "*", name); fflush(stdout);
}
void __unit_test_group_end(unit_test_stat_t* stat){
    stat->group--;
}

void __unit_test_block_beg(unit_test_stat_t *stat, char* name){
    stat->group++; printf("   | %*s B:%s\n", stat->group * 2, "*", name); fflush(stdout);
}

void __unit_test_block_init(unit_test_stat_t* stat){
    stat->group++;               printf("   | %*s I:%s\n", stat->group * 2, "*", "n"); fflush(stdout); stat->group--;
}

void __unit_test_block_test(unit_test_stat_t* stat){
    stat->group++;               printf("   | %*s T:%s\n", stat->group * 2, "*", "n"); fflush(stdout); stat->group--;
}

void __unit_test_block_free(unit_test_stat_t* stat){
    stat->group++;               printf("   | %*s F:%s\n", stat->group * 2, "*", "n"); fflush(stdout); stat->group--;
}

void __unit_test_block_end(unit_test_stat_t* stat){
    stat->group--;
}

void __unit_test_group_ret(unit_test_stat_t* stat, char* mesg){

}
void __unit_test_group_ext(unit_test_stat_t* stat, char* mesg){

}
void __unit_test_group_brk(unit_test_stat_t* stat, char* mesg){
    printf("   | %s\n", mesg); fflush(stdout);
}

void __unit_test_group_msg(unit_test_stat_t* stat, char* mesg){
    printf("   | %*s B:%s\n", stat->group * 2, "*", mesg); fflush(stdout);
}


void __unit_test_assert_info(unit_test_stat_t* stat, char* name_test, char* ACT, char* EXT, char* EPS){
    printf("   %*s", stat->group * 2, "-");         \
    printf("%*s", 40 - stat->group * 2, "");        \
    printf("%-*s ", 25,  name_test);                        \
    printf("%-*s ", 10 ,  ACT);                       \
    printf("%-*s ", 10 ,  EXT);                       \
    printf("%-*s ", 10 ,  EPS);
    printf("\n");
}

void __unit_test_assert_beg(unit_test_stat_t* stat){
    stat->count_test_running++;
}
void __unit_test_assert_end(unit_test_stat_t* stat){
    stat->count_test_completed++;              \

}
void __unit_test_assert_suce(unit_test_stat_t* stat){
    stat->count_test_successful++; \
    printf("%s", "OK |");

}
void __unit_test_assert_feil(unit_test_stat_t* stat){
    stat->count_test_failure++;    \
    printf("%s", "ER |");
}

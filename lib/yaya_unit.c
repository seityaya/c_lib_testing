//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_unit.h"
#include "inttypes.h"

bool unit_test_init(unit_test_t *info, unit_test_func_t *list, unit_test_sett_t *sett) {
    if(info == NULL){ return false; }
    if(list == NULL){ return false; }
    if(sett == NULL){ return false; }

    info->list = list;
    info->sett = sett;

    {
        if(info->list[0].func != NULL){
            info->count_test_all = 0;
        }else{
            for (uintmax_t i = 1; i < __UINTMAX_MAX__; i++) {
                if(info->list[i].func == NULL){
                    info->count_test_all = i - 1;
                    break;
                }
            }
        }
    }

    return true;
}

bool unit_test_start_all(unit_test_t *info){
    if(info       == NULL){ return false; }
    if(info->list == NULL){ return false; }
    if(info->sett == NULL){ return false; }

    for (uintmax_t i = 1; i < info->count_test_all + 1; i++) {
        info->count_test_running++;
        if(info->list[i].func(&info->list[i].info)){
            info->list[i].pass = true;
            info->count_test_completed++;
            if(info->list[i].info.result == true){
                info->count_test_successful++;
            }else{
                info->count_test_failure++;
            }
        }
    }
    return true;
}

bool unit_test_print_stats(unit_test_t *info){
    printf("==========\n");
    printf("TOTAL   %" PRIuMAX "\n", info->count_test_all);
    printf("RUN     %" PRIuMAX "\n", info->count_test_running);
    printf("COMPLET %" PRIuMAX "\n", info->count_test_completed);
    printf("SUCCES  %" PRIuMAX "\n", info->count_test_successful);
    printf("FAILURE %" PRIuMAX "\n", info->count_test_failure);
    printf("==========\n");
    return true;
}

bool unit_test_print_result(unit_test_t* info){
    if(info       == NULL){ return false; }
    if(info->list == NULL){ return false; }
    if(info->sett == NULL){ return false; }

    for (uintmax_t i = 1; i < info->count_test_all + 1; i++) {
        printf("TEST %4ju: ", i);
        if(info->list[i].pass){
            if(info->list[i].info.result){
                printf("OK   : [%s]", info->list[i].name);
            }else{
                printf("ERROR: [%s]    [%s  %s %s]", info->list[i].name, info->list[i].info.mesg, info->list[i].info.value, info->list[i].info.expec);
            }
        }else{
            printf("NOT RUN");
        }

        printf("\n");
    }
    return true;
}

bool unit_test_start_level(unit_test_t *info, uintmax_t level){
    (void)(info);
    (void)(level);
    return true;
}

bool unit_test_start_group(unit_test_func_t* list, uintmax_t group){
    (void)(list);
    (void)(group);
    return true;
}


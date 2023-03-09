//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

#include "inttypes.h"
#include "math.h"
#include "stdio.h"
#include "string.h"

#include "yaya_arithmetic.h"
#include "yaya_unit.h"

unit_test_sett_t unit_test_sett_def = {
    .map = false,
    .suse = false,
    .stat = true,
    .fold = false,
};

unit_test_stat_t stat = {0};

bool_t unit_test_init(unit_test_t *ut_main, unit_test_func_t* list, unit_test_sett_t* sett) {
    if(ut_main == NULL){ return false; }
    if(list == NULL){ return false; }
    if(sett == NULL){ sett = &unit_test_sett_def; }

    ut_main->list = list;
    ut_main->sett = sett;

    ut_main->stat = &stat;

    {
        if(ut_main->list[0].func != NULL){
            ut_main->count_test_func = 0;
        }else{
            for (uintmax_t i = 1; i < __UINTMAX_MAX__; i++) {
                if(ut_main->list[i].func == NULL){
                    ut_main->count_test_func = i - 1;
                    break;
                }
            }
        }
    }

    ut_main->stat->init = true;
    ut_main->stat->run = false;
    ut_main->stat->out = false;

    for (uintmax_t i = 1; i <= ut_main->count_test_func; i++) {
        for(uintmax_t j = 0; j < ut_main->list[i].run_count; j++){
            ut_main->list[i].func(ut_main);
        }
    }

    return true;
}

bool_t unit_test_stats(unit_test_t *ut_main){
    if(ut_main->sett->stat == true){
        printf("== STATS ==\n");
        printf("FUNC    %3" PRIuMAX "\n", ut_main->count_test_func);
        printf("ALL     %3" PRIuMAX "\n", ut_main->stat->count_test_assert);
        printf("RUN     %3" PRIuMAX "\n", ut_main->stat->count_test_running);
        printf("SUCCES  %3" PRIuMAX "\n", ut_main->stat->count_test_successful);
        printf("FAILURE %3" PRIuMAX "\n", ut_main->stat->count_test_failure);
        printf("===========\n");
    }
    return true;
}

bool_t unit_test_start(unit_test_t *ut_main){
    if(ut_main       == NULL){ return false; }
    if(ut_main->list == NULL){ return false; }

    ut_main->stat->init = false;
    ut_main->stat->run = true;
    ut_main->stat->out = true;

    printf("== TESTS ==\n");
    for (uintmax_t i = 1; i <= ut_main->count_test_func; i++) {
        for(uintmax_t j = 0; j < ut_main->list[i].run_count; j++){
            ut_main->list[i].func(ut_main);
        }
    }
    printf("===========\n");
    return true;
}

bool_t unit_test_print(unit_test_t *ut_main){
    if(ut_main       == NULL){ return false; }
    if(ut_main->list == NULL){ return false; }

    ut_main->stat->init = false;
    ut_main->stat->run = false;
    ut_main->stat->out = true;

    printf("==========\n");
    for (uintmax_t i = 1; i <= ut_main->count_test_func; i++) {
        for(uintmax_t j = 0; j < ut_main->list[i].run_count; j++){
            ut_main->list[i].func(ut_main);
        }
    }
    printf("==========\n");
    return true;
}

void __unit_test_print(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }

    if(ut_main->stat->out && (ut_main->sett->suse || ut_main->stat->last_staus == UT_FAIL)) {
        //head
        if(ut_main->stat->group[ut_main->stat->group_count_current].type == UT_GROUP_T || ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_T){
            switch (ut_main->stat->last_staus) {
                case UT_SUCE:    printf("+ %s", "SUCE");  break;
                case UT_FAIL:    printf("- %s", "FAIL");  break;
                case UT_SKIP:    printf("? %s", "SKIP");  break;
            }
        }
        if(ut_main->stat->group[ut_main->stat->group_count_current].type == UT_MESEGE_T){
            printf("! %s", "MESG");
        }

        //path
        {

            printf("%s", " | ");
            printf("%s", "/");

            int len = 0;

            for (uintmax_t i = 1; i <= ut_main->stat->group_count_current; i++) {
                if(ut_main->stat->group[i].type == UT_GROUP_T || ut_main->stat->group[i].type == UT_BLOCK_T){
                    len += printf("%s/", ut_main->stat->group[i].name);
                }
            }

            printf("%*s", (int)((ut_main->stat->group_len_max + ut_main->stat->group_count_max) - (len)), "");
            printf("%s", " | ");
        }

        //assert
        if(ut_main->stat->group[ut_main->stat->group_count_current].type == UT_GROUP_T || ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_T){
            printf("ASSERT: ");
            printf("%-*s", 15, ut_main->stat->last_test);
            printf(" | ");

            if(ut_main->stat->param >= 1){ printf("%*s [%s] ", (int)(10 - strlen(ut_main->stat->val_macro_str)), "", ut_main->stat->val_macro_str); }
            if(ut_main->stat->param >= 2){ printf("<-> [%s] %-*s ",  ut_main->stat->exp_macro_str, (int)(10 - strlen(ut_main->stat->exp_macro_str)), "" ); }
            else{ printf("       %-*s ", (int)(10), "" ); }

            printf("%s", "|");

            if(ut_main->stat->param >= 1){ printf("%*s (%s) ",  (int)(20 - strlen(ut_main->stat->val_value_str)), "", ut_main->stat->val_value_str); }
            if(ut_main->stat->param >= 2){ printf("<-> (%s) ", ut_main->stat->exp_value_str); }

            //            if(ut_main->stat->param >= 3){ printf("[%s] == (%s) ", ut_main->stat->eps_macro_str, ut_main->stat->eps_value_str); }
        }
        if(ut_main->stat->group[ut_main->stat->group_count_current].type == UT_MESEGE_T){
            printf("MESAGE: ");
            printf("%s", ut_main->stat->group[ut_main->stat->group_count_current].name);
        }
        printf("\n");

        fflush(stdout);
    }
}

bool_t __unit_test_last_status(unit_test_t *ut_main){
    if(ut_main == NULL){ return false; }

    if(ut_main->stat->last_staus == UT_SUCE){
        return true;
    }
    return false;
}

void __unit_test_group_beg(unit_test_t *ut_main, char* name){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_count_current++;

    ut_main->stat->group_len_current += strlen(name);
    ut_main->stat->group_len_max = max(ut_main->stat->group_len_max, ut_main->stat->group_len_current);
    ut_main->stat->group_count_max = max(ut_main->stat->group_count_max, ut_main->stat->group_count_current);

    ut_main->stat->group[ut_main->stat->group_count_current].name = name;
    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_GROUP_T;
}

void __unit_test_group_end(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_len_current -= strlen(ut_main->stat->group[ut_main->stat->group_count_current].name);
    ut_main->stat->group_count_current--;
}
void __unit_test_block_beg(unit_test_t *ut_main, char* name){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_count_current++;

    ut_main->stat->group_len_current += strlen(name);
    ut_main->stat->group_len_max = max(ut_main->stat->group_len_max, ut_main->stat->group_len_current);
    ut_main->stat->group_count_max = max(ut_main->stat->group_count_max, ut_main->stat->group_count_current);

    ut_main->stat->group[ut_main->stat->group_count_current].name = name;
    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_BLOCK_T;
}
void __unit_test_block_init(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }
//    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_BLOCK_INIT_T;
}
void __unit_test_block_test(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }
//    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_BLOCK_TEST_T;
}
void __unit_test_block_free(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }
//    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_BLOCK_FREE_T;
}
void __unit_test_block_end(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_len_current -= strlen(ut_main->stat->group[ut_main->stat->group_count_current].name);
    ut_main->stat->group_count_current--;
}
void __unit_test_group_ret(unit_test_t *ut_main, char* mesg){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_count_current = 0;
}
void __unit_test_group_ext(unit_test_t *ut_main, char* mesg){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_count_current = 0;
}
void __unit_test_group_brk(unit_test_t *ut_main, char* mesg){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_count_current = 0;
}
void __unit_test_group_msg(unit_test_t *ut_main, char* mesg){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_count_current++;
    ut_main->stat->group[ut_main->stat->group_count_current].name = mesg;
    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_MESEGE_T;
    __unit_test_print(ut_main);
    ut_main->stat->group_count_current--;
}
void __unit_test_assert_info(unit_test_t *ut_main, const char* file, const char* func, const uintmax_t line, char* name_test, ut_list_t ut_list, uintmax_t param, char* ACT, char* EXT, char* EPS){
    if(ut_main == NULL){ return; }
    ut_main->stat->file = file;
    ut_main->stat->func = func;
    ut_main->stat->line = line;

    ut_main->stat->last_test = &name_test[0];
    ut_main->stat->param = param;
    ut_main->stat->val_macro_str = ACT;
    ut_main->stat->exp_macro_str = EXT;
    ut_main->stat->eps_macro_str = EPS;
}

void __unit_test_assert_val_build(char*  text,
                                  void*  ACT_P,
                                  int8_t ACT_l,
                                  int8_t ACT_T,
                                  char   ACT_N,
                                  char*  ACT_S,
                                  char*  ACT_s){
    char fmt[128] = {0};

    if(ACT_T > 0){
        snprintf(fmt, 128, "%%%s", ACT_S);
        if(ACT_T == STD_TYPE_GROUP_UINT){
            if(ACT_l == sizeof(uint8_t)){
                snprintf(text, 1024, fmt, *(int8_t*)ACT_P);
            }
        }

        if(ACT_T == STD_TYPE_GROUP_FLT){
            snprintf(fmt, 128, "%%.54%s", ACT_S);
            snprintf(text, 1024, fmt, *(double*)ACT_P);
        }

        if(ACT_T < 0){
            snprintf(fmt, 128, "%%p");
            snprintf(text, 1024, fmt, &ACT_P);
        }

    }
}

void __unit_test_assert_val(unit_test_t *ut_main,
                            void*  ACT_P, void*  EXT_P,  void* EPS_P,
                            int8_t ACT_l, int8_t EXT_l, int8_t EPS_l,
                            int8_t ACT_T, int8_t EXT_T, int8_t EPS_T,
                            char   ACT_N, char   EXT_N, char   EPS_N,
                            char*  ACT_S, char*  EXT_S,  char* EPS_S,
                            char*  ACT_s, char*  EXT_s,  char* EPS_s)
{
    if(ut_main == NULL){ return; }
    ut_main->stat->count_test_running++;

    ut_main->stat->val_value_str[0] = '\0';
    ut_main->stat->exp_value_str[0] = '\0';
    ut_main->stat->eps_value_str[0] = '\0';

    if(ut_main->stat->param >= 1){  __unit_test_assert_val_build(ut_main->stat->val_value_str, ACT_P, ACT_l, ACT_T, ACT_N, ACT_S, ACT_s); }
    if(ut_main->stat->param >= 2){  __unit_test_assert_val_build(ut_main->stat->exp_value_str, EXT_P, EXT_l, EXT_T, EXT_N, EXT_S, EXT_s); }
    if(ut_main->stat->param >= 3){  __unit_test_assert_val_build(ut_main->stat->eps_value_str, EPS_P, EPS_l, EPS_T, EPS_N, EPS_S, EPS_s); }

}
void __unit_test_assert_beg(unit_test_t *ut_main){
    if(ut_main->stat->init){
        ut_main->stat->count_test_assert++;
    }
    ut_main->stat->last_staus = UT_SKIP;
}
void __unit_test_assert_end(unit_test_t *ut_main){
    __unit_test_print(ut_main);
}
void __unit_test_assert_suce(unit_test_t *ut_main){
    ut_main->stat->count_test_successful++;
    ut_main->stat->last_staus = UT_SUCE;
}
void __unit_test_assert_feil(unit_test_t *ut_main){
    ut_main->stat->count_test_failure++;
    ut_main->stat->last_staus = UT_FAIL;
}

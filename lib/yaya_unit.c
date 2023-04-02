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
    .suse = false,
    .stat = true,
};

unit_test_stat_t stat = {0};

bool_t unit_test_init(unit_test_t *ut_main, unit_test_func_t* list, unit_test_sett_t* sett) {
    if(ut_main == NULL) { return false; }
    if(list    == NULL) { return false; }
    if(sett    == NULL) { sett = &unit_test_sett_def; }

    ut_main->list = list;
    ut_main->sett = sett;

    ut_main->stat = &stat;

    unit_test_func_t* l = ut_main->list;
    {
        if(l[0].func != NULL){
            ut_main->count_test_func = 0;
        }else{
            for (uintmax_t i = 1; i < __UINTMAX_MAX__; i++) {
                if(l[i].func == NULL){
                    ut_main->count_test_func = i - 1;
                    break;
                }
            }
        }
    }

    ut_main->stat->init = true;
    ut_main->stat->run  = false;
    ut_main->stat->out  = false;
    for (uintmax_t i = 1; i <= ut_main->count_test_func; i++) {
        if(l[i].run_count == 0){
            l[i].func(ut_main);
        }else{
            for(uintmax_t j = 0; j < l[i].run_count; j++) {
                l[i].func(ut_main);
            }
        }
    }

    return true;
}
bool_t unit_test_start(unit_test_t *ut_main){
    if(ut_main       == NULL){ return false; }
    if(ut_main->list == NULL){ return false; }

    ut_main->stat->init = false;
    ut_main->stat->run  = true;
    ut_main->stat->out  = true;

    unit_test_func_t* l = ut_main->list;

    printf("=== TESTS ===\n");
    for (uintmax_t i = 1; i <= ut_main->count_test_func; i++) {
        for(uintmax_t j = 0; j < l[i].run_count; j++){
            l[i].func(ut_main);
        }
    }
    printf("=============\n");
    return true;
}
bool_t unit_test_print(unit_test_t *ut_main){
    if(ut_main       == NULL){ return false; }
    if(ut_main->list == NULL){ return false; }

    ut_main->stat->init = false;
    ut_main->stat->run  = false;
    ut_main->stat->out  = true;

    unit_test_func_t* l = ut_main->list;

    printf("==== МАР ====\n");
    for (uintmax_t i = 1; i <= ut_main->count_test_func; i++) {
        for(uintmax_t j = 0; j < l[i].run_count; j++){
            l[i].func(ut_main);
        }
    }
    printf("=============\n");
    return true;
}
bool_t unit_test_stats(unit_test_t *ut_main){
    if(ut_main->sett->stat == true){
        printf("=== STATS ===\n");
        printf("FUNC    %5" PRIuMAX "\n", ut_main->count_test_func);
        printf("ALL     %5" PRIuMAX "\n", ut_main->stat->count_test_assert);
        printf("RUN     %5" PRIuMAX "\n", ut_main->stat->count_test_running);
        printf("SUCCES  %5" PRIuMAX "\n", ut_main->stat->count_test_successful);
        printf("FAILURE %5" PRIuMAX "\n", ut_main->stat->count_test_failure);
        printf("=============\n");
    }
    return true;
}

void __unit_test_assert_beg(unit_test_t *ut_main){
    if(ut_main->stat->init){
        ut_main->stat->count_test_assert++;
    }
    ut_main->stat->last_test_staus = UT_SKIP;
}
void __unit_test_assert_end(unit_test_t *ut_main){
    __unit_test_format_print(ut_main);
}

void __unit_test_assert_suce(unit_test_t *ut_main){
    ut_main->stat->count_test_successful++;
    ut_main->stat->last_test_staus = UT_SUCE;
}
void __unit_test_assert_fail(unit_test_t *ut_main){
    ut_main->stat->count_test_failure++;
    ut_main->stat->last_test_staus = UT_FAIL;
}

void __unit_test_group_beg(unit_test_t *ut_main, char* name){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_count_current++;
    ut_main->stat->group_len_current += strlen(name);
    ut_main->stat->group[ut_main->stat->group_count_current].name = name;
    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_GROUP_T;

    if(ut_main->stat->init){
        ut_main->stat->group_len_max = max(ut_main->stat->group_len_max, ut_main->stat->group_len_current);
        ut_main->stat->group_count_max = max(ut_main->stat->group_count_max, ut_main->stat->group_count_current);
    }
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
    ut_main->stat->group[ut_main->stat->group_count_current].name = name;
    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_BLOCK_T;

    if(ut_main->stat->init){
        ut_main->stat->group_len_max = max(ut_main->stat->group_len_max, ut_main->stat->group_len_current);
        ut_main->stat->group_count_max = max(ut_main->stat->group_count_max, ut_main->stat->group_count_current);
    }
}
void __unit_test_block_init(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }
    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_BLOCK_INIT_T;
}
void __unit_test_block_test(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }
    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_BLOCK_TEST_T;
}
void __unit_test_block_free(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }
    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_BLOCK_FREE_T;
}
void __unit_test_block_end(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }
    ut_main->stat->group_len_current -= strlen(ut_main->stat->group[ut_main->stat->group_count_current].name);
    ut_main->stat->group_count_current--;
}

void __unit_test_group_ret(unit_test_t *ut_main, const char* file, const char* func, const uintmax_t line, const char* mesg){
    UNUSED_VAR(mesg);
    if(ut_main == NULL){ return; }
    ut_main->stat->file = file;
    ut_main->stat->func = func;
    ut_main->stat->line = line;
    ut_main->stat->group_count_current = 0;
}
void __unit_test_group_ext(unit_test_t *ut_main, const char* file, const char* func, const uintmax_t line, const char* mesg){
    UNUSED_VAR(mesg);
    if(ut_main == NULL){ return; }
    ut_main->stat->file = file;
    ut_main->stat->func = func;
    ut_main->stat->line = line;
    ut_main->stat->group_count_current = 0;
}
void __unit_test_group_brk(unit_test_t *ut_main, const char* file, const char* func, const uintmax_t line, const char* mesg){
    UNUSED_VAR(mesg);
    if(ut_main == NULL){ return; }
    ut_main->stat->file = file;
    ut_main->stat->func = func;
    ut_main->stat->line = line;
    ut_main->stat->group_count_current--;
}
void __unit_test_group_msg(unit_test_t *ut_main, const char* file, const char* func, const uintmax_t line, const char* mesg){
    if(ut_main == NULL){ return; }
    ut_main->stat->file = file;
    ut_main->stat->func = func;
    ut_main->stat->line = line;
    ut_main->stat->group_count_current++;
    ut_main->stat->group[ut_main->stat->group_count_current].name = mesg;
    ut_main->stat->group[ut_main->stat->group_count_current].type = UT_MESEGE_T;
    __unit_test_format_print(ut_main);
    ut_main->stat->group_count_current--;
}

void __unit_test_assert_info(unit_test_t *ut_main,
        const char* file,
        const char* func,
        const uintmax_t line,
        char* name_test,
        uintmax_t param,
        char* OP,
        char* ACT,
        char* EXT,
        char* EPS)
{
    if(ut_main == NULL){ return; }
    ut_main->stat->file = file;
    ut_main->stat->func = func;
    ut_main->stat->line = line;

    ut_main->stat->last_test_name = name_test;
    ut_main->stat->last_test_param = param;

    ut_main->stat->last_op_macro_str  = OP;
    ut_main->stat->last_val_macro_str = ACT;
    ut_main->stat->last_exp_macro_str = EXT;
    ut_main->stat->last_eps_macro_str = EPS;

    if(ut_main->stat->init){
        ut_main->stat->file_len_max = max(ut_main->stat->file_len_max, strlen(file));
        ut_main->stat->func_len_max = max(ut_main->stat->func_len_max, strlen(func));
        ut_main->stat->line_len_max = max(ut_main->stat->line_len_max, line);

        ut_main->stat->last_val_macro_str_len = max(ut_main->stat->last_val_macro_str_len, strlen(ACT));
        ut_main->stat->last_exp_macro_str_len = max(ut_main->stat->last_exp_macro_str_len, strlen(EXT));
        ut_main->stat->last_eps_macro_str_len = max(ut_main->stat->last_eps_macro_str_len, strlen(EPS));
    }
}

void __unit_test_format_print(unit_test_t *ut_main){
    if(ut_main == NULL){ return; }

    if(ut_main->stat->out && (ut_main->sett->suse || ut_main->stat->last_test_staus == UT_FAIL)) {
        //head
        if(ut_main->stat->group[ut_main->stat->group_count_current].type == UT_GROUP_T      ||
           ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_T      ||
           ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_INIT_T ||
           ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_TEST_T ||
           ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_FREE_T )
        {
            switch (ut_main->stat->last_test_staus) {
            case UT_SUCE:    printf("+ %s", "SUCE");  break;
            case UT_FAIL:    printf("- %s", "FAIL");  break;
            case UT_SKIP:    printf("? %s", "SKIP");  break;
            }
        }
        if(ut_main->stat->group[ut_main->stat->group_count_current].type == UT_MESEGE_T){
            printf("! %s", "MESG");
        }

        printf("%s", " | ");
        printf("%4ld", ut_main->stat->line);
        printf("%s", " | ");

        //path
        {
            int len = 0;
            len += printf("%s", "/");
            len += printf("%s", ut_main->stat->func);
            len += printf("%s", "/");
            for (uintmax_t i = 1; i <= ut_main->stat->group_count_current; i++) {
                if(ut_main->stat->group[ut_main->stat->group_count_current].type == UT_GROUP_T      ||
                   ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_T      ||
                   ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_INIT_T ||
                   ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_TEST_T ||
                   ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_FREE_T )
                {
                    len += printf("%s/", ut_main->stat->group[i].name);
                }
            }

            printf("%*s", ((int)(4 + ut_main->stat->group_len_max + ut_main->stat->group_count_max + ut_main->stat->func_len_max) - (len)), "");
            printf("%s", " | ");
        }

        //assert
        if(ut_main->stat->group[ut_main->stat->group_count_current].type == UT_GROUP_T      ||
           ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_T      ||
           ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_INIT_T ||
           ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_TEST_T ||
           ut_main->stat->group[ut_main->stat->group_count_current].type == UT_BLOCK_FREE_T )
        {

            printf("ASSERT: ");
            printf("%-*s", 17, ut_main->stat->last_test_name);
            printf(" | ");

            if(ut_main->stat->val_last_test_spec == NULL && ut_main->stat->exp_last_test_spec == NULL){
                printf("<und> | <und>");
            }else{
                printf("<%3s> - <%3s>", ut_main->stat->val_last_test_spec, ut_main->stat->exp_last_test_spec);
            }

            printf(" | ");

            if(ut_main->stat->last_test_param >= 1){
                printf("%*s [%s]",
                       (int)(ut_main->stat->last_val_macro_str_len - strlen(ut_main->stat->last_val_macro_str)),
                       "", ut_main->stat->last_val_macro_str);
            }
            if(ut_main->stat->last_test_param >= 2){
                printf(" %s ", ut_main->stat->last_op_macro_str);

                printf("[%s] %-*s ",
                       ut_main->stat->last_exp_macro_str,
                       (int)(ut_main->stat->last_exp_macro_str_len - strlen(ut_main->stat->last_exp_macro_str)), "" );
            }
            else{
                printf("       %-*s ", (int)(ut_main->stat->last_exp_macro_str_len), "" );
            }
            if(ut_main->stat->last_test_param == 3){
                //pass
            }

            printf("%s", " | ");

            if(ut_main->stat->run){
                if(ut_main->stat->last_test_param >= 1){
                    printf("(%s)", ut_main->stat->val_value_str);
                }
                if(ut_main->stat->last_test_param >= 2){
                    printf(" %s ", ut_main->stat->last_op_macro_str);
                    printf("(%s) ", ut_main->stat->exp_value_str);
                }
                if(ut_main->stat->last_test_param == 3){
                    printf("{[%s] -- (%s)}", ut_main->stat->last_eps_macro_str, ut_main->stat->eps_value_str);
                }
            }

        }
        if(ut_main->stat->group[ut_main->stat->group_count_current].type == UT_MESEGE_T){
            printf("MESAGE: ");
            printf("%s", ut_main->stat->group[ut_main->stat->group_count_current].name);
        }
        printf("\n");

        fflush(stdout);
    }
}

void __unit_test_assert_val_build(char*  text,
                                  void*  v_point,
                                  int8_t v_size ,
                                  int8_t v_group,
                                  char   v_index,
                                  char*  v_print,
                                  const char*  v_spec ){
    UNUSED_VAR(v_index);
    UNUSED_VAR(v_spec);

    char fmt[128] = {0};

    if(v_group == STD_TYPE_GROUP_CHAR){
        snprintf(fmt, 128, "\'%%%s\'", v_print);
        snprintf(text, 1024, fmt, *(char*)v_point);
        return;
    }

    if(v_group == STD_TYPE_GROUP_UINT){
        snprintf(fmt, 128, "%%%s", v_print);

        if(v_size == sizeof(uint8_t)){
            snprintf(text, 1024, fmt, *(uint8_t*)v_point);
        }
        if(v_size == sizeof(uint16_t)){
            snprintf(text, 1024, fmt, *(uint16_t*)v_point);
        }
        if(v_size == sizeof(uint32_t)){
            snprintf(text, 1024, fmt, *(uint32_t*)v_point);
        }
        if(v_size == sizeof(uint64_t)){
            snprintf(text, 1024, fmt, *(uint64_t*)v_point);
        }
        return;
    }

    if(v_group == STD_TYPE_GROUP_SINT){
        snprintf(fmt, 128, "%%%s", v_print);

        if(v_size == sizeof(int8_t)){
            snprintf(text, 1024, fmt, *(int8_t*)v_point);
        }
        if(v_size == sizeof(int16_t)){
            snprintf(text, 1024, fmt, *(int16_t*)v_point);
        }
        if(v_size == sizeof(int32_t)){
            snprintf(text, 1024, fmt, *(int32_t*)v_point);
        }
        if(v_size == sizeof(int64_t)){
            snprintf(text, 1024, fmt, *(int64_t*)v_point);
        }
        return;
    }

    if(v_group == STD_TYPE_GROUP_FLT){
        if(v_size == sizeof(f32_t)){
            snprintf(fmt, 128, "%%.26%s", v_print);
            snprintf(text, 1024, fmt, *(f32_t*)v_point);
        }
        if(v_size == sizeof(f64_t)){
            snprintf(fmt, 128, "%%.55%s", v_print);
            snprintf(text, 1024, fmt, *(f64_t*)v_point);
        }
        if(v_size == sizeof(f128_t)){
            snprintf(fmt, 128, "%%.66%s", v_print);
            snprintf(text, 1024, fmt, *(f128_t*)v_point);
        }
        return;
    }

    if(v_group == STD_TYPE_GROUP_CHAR_P){
        snprintf(fmt, 128, "\"%%%s\"", v_print);
        snprintf(text, 1024, fmt, (char*)v_point);
        return;
    }

    if(v_group > STD_TYPE_GROUP_CHAR_P){
        snprintf(text, 1024, "0x%0*" PRIxPTR, (int)(sizeof(uintmax_t) * 2), *(uintmax_t*)v_point);
        return;
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

    ut_main->stat->val_last_test_spec = ACT_s;
    ut_main->stat->exp_last_test_spec = EXT_s;
    ut_main->stat->eps_last_test_spec = EPS_s;

    ut_main->stat->val_value_str[0] = '\0';
    ut_main->stat->exp_value_str[0] = '\0';
    ut_main->stat->eps_value_str[0] = '\0';

    if(ut_main->stat->last_test_param >= 1){  __unit_test_assert_val_build(ut_main->stat->val_value_str, ACT_P, ACT_l, ACT_T, ACT_N, ACT_S, ACT_s); }
    if(ut_main->stat->last_test_param >= 2){  __unit_test_assert_val_build(ut_main->stat->exp_value_str, EXT_P, EXT_l, EXT_T, EXT_N, EXT_S, EXT_s); }
    if(ut_main->stat->last_test_param >= 3){  __unit_test_assert_val_build(ut_main->stat->eps_value_str, EPS_P, EPS_l, EPS_T, EPS_N, EPS_S, EPS_s); }
}

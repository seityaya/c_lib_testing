// Author                 : Seityagiya Terlekchi
// Contacts               : seityaya@ukr.net
// Creation Date          : 2022.12
// License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_UNIT_MACRO_H
#define YAYA_UNIT_MACRO_H
// clang-format off

#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#include "yaya_arithmetic.h"
#include "yaya_bool.h"
#include "yaya_check.h"
#include "yaya_type.h"

struct unit_test_p;
typedef struct unit_test_p *unit_test_p;

typedef struct unit_test_func_t {
    void (*func)(unit_test_p, bool_t);
    uintmax_t run_count;
} unit_test_func_t;

typedef struct {
    bool_t suse;
    bool_t stat;
} unit_test_sett_t;

//====================================================================================================================================================

bool_t unit_test_init(unit_test_p *ut_main_p, unit_test_func_t *list, unit_test_sett_t* sett);
bool_t unit_test_free(unit_test_p *ut_main_p);

bool_t unit_test_start(unit_test_p ut_main);
bool_t unit_test_print(unit_test_p ut_main);
bool_t unit_test_stats(unit_test_p ut_main);

void __unit_test_assert_beg(unit_test_p ut_main);
void __unit_test_assert_end(unit_test_p ut_main);
void __unit_test_assert_suce(unit_test_p ut_main);
void __unit_test_assert_fail(unit_test_p ut_main);

void __unit_test_group_beg(unit_test_p ut_main, char* name);
void __unit_test_group_end(unit_test_p ut_main);

void __unit_test_block_beg(unit_test_p ut_main, char* name);
void __unit_test_block_init(unit_test_p ut_main);
void __unit_test_block_test(unit_test_p ut_main);
void __unit_test_block_free(unit_test_p ut_main);
void __unit_test_block_end(unit_test_p ut_main);

void __unit_test_group_ext(unit_test_p ut_main, const char* file, const char* func, uintmax_t line, const char* mesg);
void __unit_test_group_ret(unit_test_p ut_main, const char* file, const char* func, uintmax_t line, const char* mesg);
void __unit_test_group_brk(unit_test_p ut_main, const char* file, const char* func, uintmax_t line, const char* mesg);
void __unit_test_group_msg(unit_test_p ut_main, const char* file, const char* func, uintmax_t line, const char* mesg);

void __unit_test_format_print(unit_test_p ut_main);

void __unit_test_assert_info(unit_test_p ut_main,
                             const char* file, const char* func, uintmax_t line,
                             char* name_test, uintmax_t param, char* OP,
                             char* ACT, char* EXT, char* EPS);

void __unit_test_assert_val(unit_test_p ut_main,
                            void*  ACT_P,  void*  EXT_P,  void*  EPS_P,
                            int8_t ACT_l,  int8_t EXT_l,  int8_t EPS_l,
                            uint8_t ACT_T, uint8_t EXT_T, uint8_t EPS_T,
                            char   ACT_N,  char   EXT_N,  char   EPS_N,
                            char*  ACT_S,  char*  EXT_S,  char*  EPS_S,
                            char*  ACT_s,  char*  EXT_s,  char*  EPS_s);

//====================================================================================================================================================

#define UT_FUNC_GEN(NAME)    void NAME(unit_test_p ut_main, bool_t run_flag)

#define UT_GROUP_BEG(NAME)  __unit_test_group_beg(ut_main, #NAME);                                                                                   \
                            {
#define UT_GROUP_END        }                                                                                                                        \
                            __unit_test_group_end(ut_main)

#define UT_BLOCK_BEG(NAME)   __unit_test_block_beg(ut_main, #NAME);                                                                                  \
                            {                                                                                                                        \
                                switch(run_flag ? 1 : 2)
#define UT_BLOCK_INIT               case 1:                                                                                                          \
                                    __unit_test_block_init(ut_main)
#define UT_BLOCK_TEST               [[fallthrough]];                                                                                                 \
                                    case 2:                                                                                                          \
                                    __unit_test_block_test(ut_main)
#define UT_BLOCK_FREE               [[fallthrough]];                                                                                                 \
                                    case 3: \
                                    if(!run_flag){break;}                                                                                            \
                                    __unit_test_block_free(ut_main)
#define UT_BLOCK_END        }                                                                                                                        \
                            __unit_test_block_end(ut_main)

#define UT_SPASE_TEST_BEG   if(run_flag)                                                                                                             \
                            {   do
#define UT_SPASE_TEST_END       while(false);                                                                                                        \
                            }

#define UT_EXIT(MSG)         __unit_test_group_ext(ut_main, __FILE__, __FUNCTION__, __LINE__, #MSG); exit(1)
#define UT_RETURN(MSG)       __unit_test_group_ret(ut_main, __FILE__, __FUNCTION__, __LINE__, #MSG); return
#define UT_BREAK(MSG)        __unit_test_group_brk(ut_main, __FILE__, __FUNCTION__, __LINE__, #MSG); break
#define UT_MESAGE(MSG)       __unit_test_group_msg(ut_main, __FILE__, __FUNCTION__, __LINE__, #MSG)

//====================================================================================================================================================

#define UT_ASSERT_CALL_IF(                )  ({ __UT_ASSERT_CHEK( CALL_IF           , "!!", 0, nullptr, nullptr, nullptr, ""  , ""     , ""   ) })
#define UT_ASSERT_BOOL_TR(  VAL           )  ({ __UT_ASSERT_CHEK( BOOL_TRUE         , "==", 2, VAL    , true   , nullptr, #VAL, "TRUE" , ""   ) })
#define UT_ASSERT_BOOL_FL(  VAL           )  ({ __UT_ASSERT_CHEK( BOOL_FALSE        , "==", 2, VAL    , false  , nullptr, #VAL, "FALSE", ""   ) })
#define UT_ASSERT_BIT_EQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( BIT_EQUAL         , "==", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_BIT_NQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( BIT_NOT_EQUAL     , "!=", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_NUM_EQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( NUM_EQUAL         , "==", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_NUM_NQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( NUM_NOT_EQUAL     , "!=", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_CHR_EQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( CHAR_EQUAL        , "==", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_CHR_NQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( CHAR_NOT_EQUAL    , "!=", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_PTR_EQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( PTR_EQUAL         , "==", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_PTR_NQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( PTR_NOT_EQUAL     , "!=", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_NUL_EQ(   VAL           )  ({ __UT_ASSERT_CHEK( PTR_NULL          , "==", 2, VAL    , nullptr, nullptr, #VAL, "NULL" , ""   ) })
#define UT_ASSERT_NUL_NQ(   VAL           )  ({ __UT_ASSERT_CHEK( PTR_NOT_NULL      , "!=", 2, VAL    , nullptr, nullptr, #VAL, "NULL" , ""   ) })
#define UT_ASSERT_STR_EQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( STR_EQUAL         , "==", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_STR_NQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( STR_NOT_EQUAL     , "!=", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_STR_EQ_N( ACT, EXP, CNT )  ({ __UT_ASSERT_CHEK( STR_LEN_EQUAL     , "==", 3, ACT    , EXP    , CNT    , #ACT, #EXP   , #CNT ) })
#define UT_ASSERT_STR_NQ_N( ACT, EXP, CNT )  ({ __UT_ASSERT_CHEK( STR_LEN_NOT_EQUAL , "!=", 3, ACT    , EXP    , CNT    , #ACT, #EXP   , #CNT ) })
#define UT_ASSERT_FLT_EQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( FLT_EQUAL         , "==", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_FLT_NQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( FLT_NOT_EQUAL     , "!=", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_FLT_EQ_E( ACT, EXP, EPS )  ({ __UT_ASSERT_CHEK( FLT_EPS_EQUAL     , "==", 3, ACT    , EXP    , EPS    , #ACT, #EXP   , #EPS ) })
#define UT_ASSERT_FLT_NQ_E( ACT, EXP, EPS )  ({ __UT_ASSERT_CHEK( FLT_EPS_NOT_EQUAL , "!=", 3, ACT    , EXP    , EPS    , #ACT, #EXP   , #EPS ) })
#define UT_ASSERT_TYP_EQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( TYPE_EQUAL        , "==", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })
#define UT_ASSERT_TYP_NQ(   ACT, EXP      )  ({ __UT_ASSERT_CHEK( TYPE_NOT_EQUAL    , "!=", 2, ACT    , EXP    , nullptr, #ACT, #EXP   , ""   ) })


#define __UT_ASSERT_CALL_IF(          A, B, C) (false)
#define __UT_ASSERT_BOOL_TRUE(        A, B, C) ((bool_t)(A) == (true ))
#define __UT_ASSERT_BOOL_FALSE(       A, B, C) ((bool_t)(A) == (false))
#define __UT_ASSERT_BIT_EQUAL(        A, B, C) COMPILE_ASSERT_TYPE_EQUAL_2_CALC((A), (B), _x, _y, ((((umax_t)(_x)) ^ ((umax_t)(_y))) == 0))
#define __UT_ASSERT_BIT_NOT_EQUAL(    A, B, C) COMPILE_ASSERT_TYPE_EQUAL_2_CALC((A), (B), _x, _y, ((((umax_t)(_x)) ^ ((umax_t)(_y))) != 0))
#define __UT_ASSERT_NUM_EQUAL(        A, B, C) COMPILE_ASSERT_GROUP_MATCH_2_CALC(BASE_TYPE_GROUP_SINT | BASE_TYPE_GROUP_UINT, A, B, a, b, COMPILE_ASSERT_TYPE_EQUAL_2_CALC((a), (b), _x, _y, (_x) == (_y)))
#define __UT_ASSERT_NUM_NOT_EQUAL(    A, B, C) COMPILE_ASSERT_GROUP_MATCH_2_CALC(BASE_TYPE_GROUP_SINT | BASE_TYPE_GROUP_UINT, A, B, a, b, COMPILE_ASSERT_TYPE_EQUAL_2_CALC((a), (b), _x, _y, (_x) != (_y)))
#define __UT_ASSERT_CHAR_EQUAL(       A, B, C) COMPILE_ASSERT_GROUP_MATCH_2_CALC(BASE_TYPE_GROUP_CHAR, A, B, a, b, COMPILE_ASSERT_TYPE_EQUAL_2_CALC((a), (b), _x, _y, (_x) == (_y)))
#define __UT_ASSERT_CHAR_NOT_EQUAL(   A, B, C) COMPILE_ASSERT_GROUP_MATCH_2_CALC(BASE_TYPE_GROUP_CHAR, A, B, a, b, COMPILE_ASSERT_TYPE_EQUAL_2_CALC((a), (b), _x, _y, (_x) != (_y)))
#define __UT_ASSERT_PTR_EQUAL(        A, B, C) ((void*)(A) == (void*)(B))
#define __UT_ASSERT_PTR_NOT_EQUAL(    A, B, C) ((void*)(A) != (void*)(B))
#define __UT_ASSERT_PTR_NULL(         A, B, C) ((void*)(A) == NULL)
#define __UT_ASSERT_PTR_NOT_NULL(     A, B, C) ((void*)(A) != NULL)
#define __UT_ASSERT_STR_EQUAL(        A, B, C) (0 == strcmp ((const char*)(A), (const char*)(B)))
#define __UT_ASSERT_STR_NOT_EQUAL(    A, B, C) (0 != strcmp ((const char*)(A), (const char*)(B)))
#define __UT_ASSERT_STR_LEN_EQUAL(    A, B, C) (0 == strncmp((const char*)(A), (const char*)(B), (size_t)(C)))
#define __UT_ASSERT_STR_LEN_NOT_EQUAL(A, B, C) (0 != strncmp((const char*)(A), (const char*)(B), (size_t)(C)))
#define __UT_ASSERT_FLT_EQUAL(        A, B, C) COMPILE_ASSERT_GROUP_MATCH_2_CALC(BASE_TYPE_GROUP_FLT, A, B, a, b, (!(abs(a - b) >= base_type_eps(a))))
#define __UT_ASSERT_FLT_NOT_EQUAL(    A, B, C) COMPILE_ASSERT_GROUP_MATCH_2_CALC(BASE_TYPE_GROUP_FLT, A, B, a, b, (!(abs(a - b) <  base_type_eps(a))))
#define __UT_ASSERT_FLT_EPS_EQUAL(    A, B, C) COMPILE_ASSERT_GROUP_MATCH_2_CALC(BASE_TYPE_GROUP_FLT, A, B, a, b, (!(abs(a - b) >  abs(C)))          )
#define __UT_ASSERT_FLT_EPS_NOT_EQUAL(A, B, C) COMPILE_ASSERT_GROUP_MATCH_2_CALC(BASE_TYPE_GROUP_FLT, A, B, a, b, (!(abs(a - b) <= abs(C)))          )
#define __UT_ASSERT_TYPE_EQUAL(       A, B, C) COMPILE_TYPE_EQUAL(A, B)
#define __UT_ASSERT_TYPE_NOT_EQUAL(   A, B, C) !COMPILE_TYPE_EQUAL(A, B)

//====================================================================================================================================================

#define __UT_ASSERT_CHEK(NAME, OP, PAR, ACT, EXP, EPS, ACT_T, EXP_T, EPS_T)                                                                          \
({                                                                                                                                                   \
    __unit_test_assert_beg(ut_main);                                                                                                                 \
    __unit_test_assert_info(ut_main, __FILE__, __FUNCTION__, __LINE__, #NAME, PAR, OP, ACT_T, EXP_T, EPS_T);                                         \
    if(run_flag) {                                                                                                                                   \
        typeof(ACT) _ACT = ACT;                                                                                                                      \
        typeof(EXP) _EXP = EXP;                                                                                                                      \
        typeof(EPS) _EPS = EPS;                                                                                                                      \
        __unit_test_assert_val(ut_main,                                                                                                              \
                               (void*)        (&_ACT), (void*)        (&_EXP), (void*)        (&_EPS),                                               \
                               sizeof         ( _ACT), sizeof         ( _EXP), sizeof         ( _EPS),                                               \
                               base_type_group( _ACT), base_type_group( _EXP), base_type_group( _EPS),                                               \
                               base_type_uid  ( _ACT), base_type_uid  ( _EXP), base_type_uid  ( _EPS),                                               \
                               base_type_print( _ACT), base_type_print( _EXP), base_type_print( _EPS),                                               \
                               base_type_spec ( _ACT), base_type_spec ( _EXP), base_type_spec ( _EPS));                                              \
        if(__UT_ASSERT_##NAME(_ACT, _EXP, _EPS)) {                                                                                                   \
            __unit_test_assert_suce(ut_main);                                                                                                        \
        }else{                                                                                                                                       \
            __unit_test_assert_fail(ut_main);                                                                                                        \
        }                                                                                                                                            \
    }                                                                                                                                                \
    __unit_test_assert_end(ut_main);                                                                                                                 \
});

// clang-format on
#endif /*YAYA_UNIT_MACRO_H*/

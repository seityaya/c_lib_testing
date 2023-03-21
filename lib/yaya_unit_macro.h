//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_UNIT_MACRO_H
#define YAYA_UNIT_MACRO_H

#include "yaya_chek.h"
#include "yaya_arithmetic.h"

typedef enum ut_list_t{
    UT_ENUM_BOOL          ,
    UT_ENUM_BOOL_TRUE     ,
    UT_ENUM_BOOL_FALSE    ,
    UT_ENUM_BIT_EQUAL     ,
    UT_ENUM_BIT_NOT_EQUAL ,
    UT_ENUM_NUM_EQUAL     ,
    UT_ENUM_NUM_NOT_EQUAL ,
    UT_ENUM_CHAR_EQUAL    ,
    UT_ENUM_CHAR_NOT_EQUAL,
    UT_ENUM_PTR_EQUAL     ,
    UT_ENUM_PTR_NOT_EQUAL ,
    UT_ENUM_PTR_NULL      ,
    UT_ENUM_PTR_NOT_NULL  ,
    UT_ENUM_STR_EQUAL     ,
    UT_ENUM_STR_NOT_EQUAL ,
    UT_ENUM_NSTR_EQUAL    ,
    UT_ENUM_NSTR_NOT_EQUAL,
    UT_ENUM_FLT_EQUAL     ,
    UT_ENUM_FLT_NOT_EQUAL ,
    UT_ENUM_NFLT_EQUAL    ,
    UT_ENUM_NFLT_NOT_EQUAL,
    UT_ENUM_TYPE_EQUAL    ,
    UT_ENUM_TYPE_NOT_EQUAL,
}ut_list_t;

#define UT_FUNC_GEN(NAME)    void NAME(unit_test_t *ut_main)

#define UT_GROUP_BEG(NAME)                __unit_test_group_beg(ut_main, #NAME);   {
#define UT_GROUP_END         }            __unit_test_group_end(ut_main)

#define UT_BLOCK_BEG(NAME)                __unit_test_block_beg(ut_main, #NAME);   { switch(ut_main->stat->run ? 1 : 2)
#define UT_BLOCK_INIT        case 1:      __unit_test_block_init(ut_main)
#define UT_BLOCK_TEST        case 2:      __unit_test_block_test(ut_main)
#define UT_BLOCK_FREE        case 3:      if(!ut_main->stat->run){break;}  __unit_test_block_free(ut_main)
#define UT_BLOCK_END         }            __unit_test_block_end(ut_main)

#define UT_SPASE_TEST_BEG    ({ if(ut_main->stat->run)
#define UT_SPASE_TEST_END    })

#define UT_EXIT(MSG)                      __unit_test_group_ext(ut_main, #MSG);    exit(1)
#define UT_RETURN(MSG)                    __unit_test_group_ret(ut_main, #MSG);    return
#define UT_BREAK(MSG)                     __unit_test_group_brk(ut_main, #MSG);    break
#define UT_MESAGE(MSG)                    __unit_test_group_msg(ut_main, #MSG)

#define UT_ASSERT_BOOL(VAL)                      ({ __UT_ASSERT_CHEK( BOOL           , 1, VAL, NULL, NULL, #VAL, ""  , ""   ) })
#define UT_ASSERT_BOOL_TR(VAL)                   ({ __UT_ASSERT_CHEK( BOOL_TRUE      , 1, VAL, NULL, NULL, #VAL, ""  , ""   ) })
#define UT_ASSERT_BOOL_FL(VAL)                   ({ __UT_ASSERT_CHEK( BOOL_FALSE     , 1, VAL, NULL, NULL, #VAL, ""  , ""   ) })

#define UT_ASSERT_BIT_EQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( BIT_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_BIT_NQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( BIT_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_NUM_EQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( NUM_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_NUM_NQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( NUM_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_CHR_EQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( CHAR_EQUAL     , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_CHR_NQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( CHAR_NOT_EQUAL , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_PTR_EQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( PTR_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_PTR_NQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( PTR_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })

#define UT_ASSERT_PTR_NULL_EQ(VAL)               ({ __UT_ASSERT_CHEK( PTR_NULL       , 1, VAL, NULL, NULL, #VAL, ""  , ""   ) })
#define UT_ASSERT_PTR_NULL_NQ(VAL)               ({ __UT_ASSERT_CHEK( PTR_NOT_NULL   , 1, VAL, NULL, NULL, #VAL, ""  , ""   ) })

#define UT_ASSERT_STR_EQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( STR_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_STR_NQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( STR_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_STR_EQ_N(ACT, EXP, CNT)        ({ __UT_ASSERT_CHEK( NSTR_EQUAL     , 3, ACT, EXP , CNT , #ACT, #EXP, #CNT ) })
#define UT_ASSERT_STR_NQ_N(ACT, EXP, CNT)        ({ __UT_ASSERT_CHEK( NSTR_NOT_EQUAL , 3, ACT, EXP , CNT , #ACT, #EXP, #CNT ) })

#define UT_ASSERT_FLT_EQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( FLT_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_FLT_NQ(ACT, EXP)               ({ __UT_ASSERT_CHEK( FLT_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_FLT_EQ_E(ACT, EXP, EPS)        ({ __UT_ASSERT_CHEK( NFLT_EQUAL     , 3, ACT, EXP , EPS , #ACT, #EXP, #EPS ) })
#define UT_ASSERT_FLT_NQ_E(ACT, EXP, EPS)        ({ __UT_ASSERT_CHEK( NFLT_NOT_EQUAL , 3, ACT, EXP , EPS , #ACT, #EXP, #EPS ) })

#define UT_ASSERT_TYPE_EQ(ACT, EXP)              ({ __UT_ASSERT_CHEK( TYPE_EQUAL     , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })
#define UT_ASSERT_TYPE_NQ(ACT, EXP)              ({ __UT_ASSERT_CHEK( TYPE_NOT_EQUAL , 2, ACT, EXP , NULL, #ACT, #EXP, ""   ) })

#include "yaya_type.h"

#define __UT_ASSERT_BOOL(          A, B, C) false == (bool_t)(A)
#define __UT_ASSERT_BOOL_TRUE(     A, B, C) false == (bool_t)(A)
#define __UT_ASSERT_BOOL_FALSE(    A, B, C) false != (bool_t)(A)

#define __UT_ASSERT_BIT_EQUAL(     A, B, C) COMPILE_WCHDOG_2((A), (B), _x, _y, (((umax_t)(_x)) ^ ((umax_t)(_y))) != 0)
#define __UT_ASSERT_BIT_NOT_EQUAL( A, B, C) COMPILE_WCHDOG_2((A), (B), _x, _y, (((umax_t)(_x)) ^ ((umax_t)(_y))) == 0)

#define __UT_ASSERT_NUM_EQUAL(     A, B, C) COMPILE_WCHDOG_GROUP_2(STD_TYPE_GROUP_SINT | STD_TYPE_GROUP_UINT, A, B, a, b, (a) != (b))
#define __UT_ASSERT_NUM_NOT_EQUAL( A, B, C) COMPILE_WCHDOG_GROUP_2(STD_TYPE_GROUP_SINT | STD_TYPE_GROUP_UINT, A, B, a, b, (a) == (b))

#define __UT_ASSERT_CHAR_EQUAL(    A, B, C) COMPILE_WCHDOG_GROUP_2(STD_TYPE_GROUP_CHAR, A, B, a, b, (a) != (b))
#define __UT_ASSERT_CHAR_NOT_EQUAL(A, B, C) COMPILE_WCHDOG_GROUP_2(STD_TYPE_GROUP_CHAR, A, B, a, b, (a) == (b))

#define __UT_ASSERT_PTR_EQUAL(     A, B, C) (void*)(A) != (void*)(B)
#define __UT_ASSERT_PTR_NOT_EQUAL( A, B, C) (void*)(A) == (void*)(B)
#define __UT_ASSERT_PTR_NULL(      A, B, C) NULL != (void*)(A)
#define __UT_ASSERT_PTR_NOT_NULL(  A, B, C) NULL == (void*)(A)

#define __UT_ASSERT_STR_EQUAL(     A, B, C) 0 != strcmp((const char*)A, (const char*) B)
#define __UT_ASSERT_STR_NOT_EQUAL( A, B, C) !strcmp((const char*)A, (const char*)B)
#define __UT_ASSERT_NSTR_EQUAL(    A, B, C) 0 !=  strncmp((const char*)A, (const char*)B, (size_t)C)
#define __UT_ASSERT_NSTR_NOT_EQUAL(A, B, C) !strncmp((const char*)A, (const char*)B, (size_t)C)

#define __UT_ASSERT_FLT_EQUAL(     A, B, C) ({ COMPILE_GROUPMATCH_EQ(STD_TYPE_GROUP_FLT, A); COMPILE_GROUPMATCH_EQ(STD_TYPE_GROUP_FLT, B); (abs((A - B)) >  __DBL_EPSILON__); })
#define __UT_ASSERT_FLT_NOT_EQUAL( A, B, C) ({ COMPILE_GROUPMATCH_EQ(STD_TYPE_GROUP_FLT, A); COMPILE_GROUPMATCH_EQ(STD_TYPE_GROUP_FLT, B); (abs((A - B)) <= __DBL_EPSILON__);  })
#define __UT_ASSERT_NFLT_EQUAL(    A, B, C) ({ COMPILE_GROUPMATCH_EQ(STD_TYPE_GROUP_FLT, A); COMPILE_GROUPMATCH_EQ(STD_TYPE_GROUP_FLT, B); (abs((A - B)) >  abs((double_t)(C))); })
#define __UT_ASSERT_NFLT_NOT_EQUAL(A, B, C) ({ COMPILE_GROUPMATCH_EQ(STD_TYPE_GROUP_FLT, A); COMPILE_GROUPMATCH_EQ(STD_TYPE_GROUP_FLT, B); (abs((A - B)) <= abs((double_t)(C))); })

#define __UT_ASSERT_TYPE_EQUAL(     A, B, C) !COMPILE_TYPECHEK(A, B)
#define __UT_ASSERT_TYPE_NOT_EQUAL( A, B, C) COMPILE_TYPECHEK(A, B)

#if 1
#define __UT_ASSERT_CHEK(NAME, PAR, ACT, EXP, EPS, ACT_T, EXP_T, EPS_T)     ({                            \
    __unit_test_assert_beg(ut_main);                                                                           \
    __unit_test_assert_info(ut_main, __FILE__, __FUNCTION__, __LINE__, #NAME, UT_ENUM_##NAME, PAR, ACT_T, EXP_T, EPS_T); \
    if(ut_main->stat->run) {                                                                                    \
    typeof(ACT) _ACT = ACT;                                                                           \
    typeof(EXP) _EXP = EXP;                                                                                \
    typeof(EPS) _EPS = EPS;                                                                       \
    __unit_test_assert_val(ut_main,     (void*)(&_ACT),     (void*)(&_EXP),      (void*)(&_EPS),           \
    sizeof( _ACT),      sizeof( _EXP),       sizeof( _EPS),           \
    std_type_group( _ACT),     std_type_group( _EXP),      std_type_group( _EPS),           \
    std_type_index( _ACT),     std_type_index( _EXP),      std_type_index( _EPS),           \
    std_type_print( _ACT),  std_type_print( _EXP),   std_type_print( _EPS),           \
    std_type_spec( _ACT),   std_type_spec( _EXP),    std_type_spec( _EPS));          \
    if(__UT_ASSERT_##NAME(_ACT, _EXP, _EPS))                                                                          \
{\
    __unit_test_assert_feil(ut_main);                                                                  \
    }else{                                                                                                 \
    __unit_test_assert_suce(ut_main);                                                                  \
    }                                                                                                      \
    }                                                                                                          \
    __unit_test_assert_end(ut_main);                                             });
#else
#define __UT_ASSERT_CHEK(NAME, PAR, ACT, EXP, EPS, ACT_T, EXP_T, EPS_T) ({                                           \
    typeof(ACT) _ACT = (ACT);                                                                           \
    typeof(EXP) _EXP = (EXP);                                                                           \
    typeof(EPS) _EPS = (EPS);                                                                           \
    });

#endif
#endif /*YAYA_UNIT_MACRO_H*/

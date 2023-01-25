//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_UNIT_MACRO_H
#define YAYA_UNIT_MACRO_H

#include "yaya_chek.h"

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

#define UT_GROUP_BEG(NAME)                __unit_test_group_beg(ut_main, #NAME);   do
#define UT_GROUP_END         while(0);    __unit_test_group_end(ut_main)

#define UT_BLOCK_BEG(NAME)                __unit_test_block_beg(ut_main, #NAME);   do { switch(ut_main->run ? 1 : 2)
#define UT_BLOCK_INIT        case 1:      __unit_test_block_init(ut_main)
#define UT_BLOCK_TEST        case 2:      __unit_test_block_test(ut_main)
#define UT_BLOCK_FREE        case 3:                                               if(!ut_main->run){ break; }     \
                                          __unit_test_block_free(ut_main)
#define UT_BLOCK_END         } while(0);  __unit_test_block_end(ut_main)

#define UT_EXIT(MSG)                      __unit_test_group_ext(ut_main, #MSG);    exit(1)
#define UT_RETURN(MSG)                    __unit_test_group_ret(ut_main, #MSG);    return
#define UT_BREAK(MSG)                     __unit_test_group_brk(ut_main, #MSG);    break
#define UT_MESAGE(MSG)                    __unit_test_group_msg(ut_main, #MSG)

#define UT_ASSERT_BOOL(VAL)                      { __UT_ASSERT_CHEK( UT_ENUM_BOOL           , 1, VAL, NULL, NULL, #VAL, ""  , ""  , __UT_ASSERT_BOOL            ) }
#define UT_ASSERT_BOOL_TRUE(VAL)                 { __UT_ASSERT_CHEK( UT_ENUM_BOOL_TRUE      , 1, VAL, NULL, NULL, #VAL, ""  , ""  , __UT_ASSERT_BOOL_TRUE       ) }
#define UT_ASSERT_BOOL_FALSE(VAL)                { __UT_ASSERT_CHEK( UT_ENUM_BOOL_FALSE     , 1, VAL, NULL, NULL, #VAL, ""  , ""  , __UT_ASSERT_BOOL_FALSE      ) }
#define UT_ASSERT_BIT_EQUAL(ACT, EXP)            { __UT_ASSERT_CHEK( UT_ENUM_BIT_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_BIT_EQUAL       ) }
#define UT_ASSERT_BIT_NOT_EQUAL(ACT, EXP)        { __UT_ASSERT_CHEK( UT_ENUM_BIT_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_BIT_NOT_EQUAL   ) }
#define UT_ASSERT_NUM_EQUAL(ACT, EXP)            { __UT_ASSERT_CHEK( UT_ENUM_NUM_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_NUM_EQUAL       ) }
#define UT_ASSERT_NUM_NOT_EQUAL(ACT, EXP)        { __UT_ASSERT_CHEK( UT_ENUM_NUM_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_NUM_NOT_EQUAL   ) }
#define UT_ASSERT_CHAR_EQUAL(ACT, EXP)           { __UT_ASSERT_CHEK( UT_ENUM_CHAR_EQUAL     , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_CHAR_EQUAL      ) }
#define UT_ASSERT_CHAR_NOT_EQUAL(ACT, EXP)       { __UT_ASSERT_CHEK( UT_ENUM_CHAR_NOT_EQUAL , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_CHAR_NOT_EQUAL  ) }
#define UT_ASSERT_PTR_EQUAL(ACT, EXP)            { __UT_ASSERT_CHEK( UT_ENUM_PTR_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_PTR_EQUAL       ) }
#define UT_ASSERT_PTR_NOT_EQUAL(ACT, EXP)        { __UT_ASSERT_CHEK( UT_ENUM_PTR_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_PTR_NOT_EQUAL   ) }
#define UT_ASSERT_PTR_NULL(VAL)                  { __UT_ASSERT_CHEK( UT_ENUM_PTR_NULL       , 1, VAL, NULL, NULL, #VAL, ""  , ""  , __UT_ASSERT_PTR_NULL        ) }
#define UT_ASSERT_PTR_NOT_NULL(VAL)              { __UT_ASSERT_CHEK( UT_ENUM_PTR_NOT_NULL   , 1, VAL, NULL, NULL, #VAL, ""  , ""  , __UT_ASSERT_PTR_NOT_NULL    ) }
#define UT_ASSERT_STR_EQUAL(ACT, EXP)            { __UT_ASSERT_CHEK( UT_ENUM_STR_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_STR_EQUAL       ) }
#define UT_ASSERT_STR_NOT_EQUAL(ACT, EXP)        { __UT_ASSERT_CHEK( UT_ENUM_STR_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_STR_NOT_EQUAL   ) }
#define UT_ASSERT_NSTR_EQUAL(ACT, EXP, CNT)      { __UT_ASSERT_CHEK( UT_ENUM_NSTR_EQUAL     , 3, ACT, EXP , CNT , #ACT, #EXP, #CNT, __UT_ASSERT_NSTR_EQUAL      ) }
#define UT_ASSERT_NSTR_NOT_EQUAL(ACT, EXP, CNT)  { __UT_ASSERT_CHEK( UT_ENUM_NSTR_NOT_EQUAL , 3, ACT, EXP , CNT , #ACT, #EXP, #CNT, __UT_ASSERT_NSTR_NOT_EQUAL  ) }
#define UT_ASSERT_FLT_EQUAL(ACT, EXP)            { __UT_ASSERT_CHEK( UT_ENUM_FLT_EQUAL      , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_FLT_EQUAL       ) }
#define UT_ASSERT_FLT_NOT_EQUAL(ACT, EXP)        { __UT_ASSERT_CHEK( UT_ENUM_FLT_NOT_EQUAL  , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_FLT_NOT_EQUAL   ) }
#define UT_ASSERT_NFLT_EQUAL(ACT, EXP, EPS)      { __UT_ASSERT_CHEK( UT_ENUM_NFLT_EQUAL     , 3, ACT, EXP , EPS , #ACT, #EXP, #EPS, __UT_ASSERT_NFLT_EQUAL      ) }
#define UT_ASSERT_NFLT_NOT_EQUAL(ACT, EXP, EPS)  { __UT_ASSERT_CHEK( UT_ENUM_NFLT_NOT_EQUAL , 3, ACT, EXP , EPS , #ACT, #EXP, #EPS, __UT_ASSERT_NFLT_NOT_EQUAL  ) }
#define UT_ASSERT_TYPE_EQUAL(ACT, EXP)           { __UT_ASSERT_CHEK( UT_ENUM_TYPE_EQUAL     , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_TYPE_EQUAL      ) }
#define UT_ASSERT_TYPE_NOT_EQUAL(ACT, EXP)       { __UT_ASSERT_CHEK( UT_ENUM_TYPE_NOT_EQUAL , 2, ACT, EXP , NULL, #ACT, #EXP, ""  , __UT_ASSERT_TYPE_NOT_EQUAL  ) }

#include "yaya_type.h"

#define __UT_ASSERT_BOOL(          A, B, C) false == (bool)(A)
#define __UT_ASSERT_BOOL_TRUE(     A, B, C) false == (bool)(A)
#define __UT_ASSERT_BOOL_FALSE(    A, B, C) false != (bool)(A)

#define __UT_ASSERT_BIT_EQUAL(     A, B, C) COMPILE_WCHDOG((A), (B), (_x ^ _y) != 0)
#define __UT_ASSERT_BIT_NOT_EQUAL( A, B, C) COMPILE_WCHDOG((A), (B), (_x ^ _y) == 0)

#define __UT_ASSERT_NUM_EQUAL(     A, B, C) ({ COMPILE_GROUPMATCH(TYPE_GROUP_INT, A);  COMPILE_GROUPMATCH(TYPE_GROUP_INT, B);  (A) != (B); })
#define __UT_ASSERT_NUM_NOT_EQUAL( A, B, C) ({ COMPILE_GROUPMATCH(TYPE_GROUP_INT, A);  COMPILE_GROUPMATCH(TYPE_GROUP_INT, B);  (A) == (B); })

#define __UT_ASSERT_CHAR_EQUAL(    A, B, C) ({ COMPILE_GROUPMATCH(TYPE_GROUP_CHAR, A); COMPILE_GROUPMATCH(TYPE_GROUP_CHAR, B); (A) != (B); })
#define __UT_ASSERT_CHAR_NOT_EQUAL(A, B, C) ({ COMPILE_GROUPMATCH(TYPE_GROUP_CHAR, A); COMPILE_GROUPMATCH(TYPE_GROUP_CHAR, B); (A) == (B); })

#define __UT_ASSERT_PTR_EQUAL(     A, B, C) (void*)(A) != (void*)(B)
#define __UT_ASSERT_PTR_NOT_EQUAL( A, B, C) (void*)(A) == (void*)(B)
#define __UT_ASSERT_PTR_NULL(      A, B, C) NULL != (void*)(A)
#define __UT_ASSERT_PTR_NOT_NULL(  A, B, C) NULL == (void*)(A)

#define __UT_ASSERT_STR_EQUAL(     A, B, C) 0 != strcmp((const char*)A, (const char*) B)
#define __UT_ASSERT_STR_NOT_EQUAL( A, B, C) !strcmp((const char*)A, (const char*)B)
#define __UT_ASSERT_NSTR_EQUAL(    A, B, C) 0 !=  strncmp((const char*)A, (const char*)B, (size_t)C)
#define __UT_ASSERT_NSTR_NOT_EQUAL(A, B, C) !strncmp((const char*)A, (const char*)B, (size_t)C)

#define __UT_ASSERT_FLT_EQUAL(     A, B, C) ({ COMPILE_GROUPMATCH(TYPE_GROUP_FLT, A); COMPILE_GROUPMATCH(TYPE_GROUP_FLT, B); (fabs((long double)(A - B)) >  __DBL_EPSILON__); })
#define __UT_ASSERT_FLT_NOT_EQUAL( A, B, C) ({ COMPILE_GROUPMATCH(TYPE_GROUP_FLT, A); COMPILE_GROUPMATCH(TYPE_GROUP_FLT, B); (fabs((long double)(A - B)) <= __DBL_EPSILON__);  })
#define __UT_ASSERT_NFLT_EQUAL(    A, B, C) ({ COMPILE_GROUPMATCH(TYPE_GROUP_FLT, A); COMPILE_GROUPMATCH(TYPE_GROUP_FLT, B); (fabs((long double)(A - B)) >  fabs((double_t)(C))); })
#define __UT_ASSERT_NFLT_NOT_EQUAL(A, B, C) ({ COMPILE_GROUPMATCH(TYPE_GROUP_FLT, A); COMPILE_GROUPMATCH(TYPE_GROUP_FLT, B); (fabs((long double)(A - B)) <= fabs((double_t)(C))); })

#define __UT_ASSERT_TYPE_EQUAL(     A, B, C) !COMPILE_TYPECHEK(A, B)
#define __UT_ASSERT_TYPE_NOT_EQUAL( A, B, C) COMPILE_TYPECHEK(A, B)


#define __UT_ASSERT_CHEK(NAME, PAR, ACT, EXP, EPS, ACT_T, EXP_T, EPS_T, ASSERT)                                 \
    __unit_test_assert_beg(ut_main);                                                                           \
    __unit_test_assert_info(ut_main, __FILE__, __FUNCTION__, __LINE__, #NAME, NAME, PAR, ACT_T, EXP_T, EPS_T); \
    if(ut_main->stat->run) {                                                                                   \
        typeof(ACT) _ACT = ACT;                                                                                \
        typeof(EXP) _EXP = EXP;                                                                                \
        typeof(EPS) _EPS = EPS;                                                                                \
        __unit_test_assert_val(ut_main,     (void*)(&_ACT),     (void*)(&_EXP),      (void*)(&_EPS),           \
                                             sizeof( _ACT),      sizeof( _EXP),       sizeof( _EPS),           \
                                            type_group( _ACT),     type_group( _EXP),      type_group( _EPS),           \
                                            type_index( _ACT),     type_index( _EXP),      type_index( _EPS),           \
                                         type_print( _ACT),  type_print( _EXP),   type_print( _EPS),           \
                                          type_spec( _ACT),   type_spec( _EXP),    type_spec( _EPS));          \
        if(ASSERT(_ACT, _EXP, _EPS)){                                                                          \
            __unit_test_assert_feil(ut_main);                                                                  \
        }else{                                                                                                 \
            __unit_test_assert_suce(ut_main);                                                                  \
        }                                                                                                      \
    }                                                                                                          \
    __unit_test_assert_end(ut_main);                                                                           \

#endif /*YAYA_UNIT_MACRO_H*/

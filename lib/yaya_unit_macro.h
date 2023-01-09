//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_UNIT_MACRO_H
#define YAYA_UNIT_MACRO_H

#define UT_FUNC_GEN(NAME)    void NAME(unit_test_stat_t *ut_stat)

#define UT_BEG_GROUP(NAME)                __unit_test_group_beg(ut_stat, #NAME);   do
#define UT_END_GROUP         while(0);    __unit_test_group_end(ut_stat)

#define UT_BLOCK_BEG(NAME)                __unit_test_block_beg(ut_stat, #NAME);   do { switch(ut_stat->run ? 1 : 2)
#define UT_BLOCK_INIT        case 1:      __unit_test_block_init(ut_stat)
#define UT_BLOCK_TEST        case 2:      __unit_test_block_test(ut_stat)
#define UT_BLOCK_FREE        case 3:                                               if(!ut_stat->run){ break; }     \
                                          __unit_test_block_free(ut_stat)
#define UT_BLOCK_END         } while(0);  __unit_test_block_end(ut_stat)

#define UT_EXIT(MSG)                      __unit_test_group_ext(ut_stat, #MSG);    exit(1)
#define UT_RETURN(MSG)                    __unit_test_group_ret(ut_stat, #MSG);    return
#define UT_BREAK(MSG)                     __unit_test_group_brk(ut_stat, #MSG);    break
#define UT_MESAGE(MSG)                    __unit_test_group_msg(ut_stat, #MSG)

#define UT_ASSERT_BOOL(VAL)                      { _UT_ASSERT_CHEK( "ASSERT_BOOL"          , VAL, NULL, NULL, false == (bool)(VAL)                                           ) }
#define UT_ASSERT_BOOL_TRUE(VAL)                 { _UT_ASSERT_CHEK( "ASSERT_BOOL_TRUE"     , VAL, NULL, NULL, false == (bool)(VAL)                                           ) }
#define UT_ASSERT_BOOL_FALSE(VAL)                { _UT_ASSERT_CHEK( "ASSERT_BOOL_FALSE"    , VAL, NULL, NULL, false != (bool)(VAL)                                           ) }
#define UT_ASSERT_NUM_EQUAL(ACT, EXP)            { _UT_ASSERT_CHEK( "ASSERT_NUM_EQUAL"     , ACT, EXP , NULL, (ACT) != (EXP)                                                 ) }
#define UT_ASSERT_NUM_NOT_EQUAL(ACT, EXP)        { _UT_ASSERT_CHEK( "ASSERT_NUM_NOT_EQUAL" , ACT, EXP , NULL, (ACT) == (EXP)                                                 ) }
#define UT_ASSERT_PTR_EQUAL(ACT, EXP)            { _UT_ASSERT_CHEK( "ASSERT_PTR_EQUAL"     , ACT, EXP , NULL, (void*)(ACT) != (void*)(EXP)                                   ) }
#define UT_ASSERT_PTR_NOT_EQUAL(ACT, EXP)        { _UT_ASSERT_CHEK( "ASSERT_PTR_NOT_EQUAL" , ACT, EXP , NULL, (void*)(ACT) == (void*)(EXP)                                   ) }
#define UT_ASSERT_PTR_NULL(VAL)                  { _UT_ASSERT_CHEK( "ASSERT_PTR_NULL"      , VAL, NULL, NULL, NULL != (void*)(VAL)                                           ) }
#define UT_ASSERT_PTR_NOT_NULL(VAL)              { _UT_ASSERT_CHEK( "ASSERT_PTR_NOT_NULL"  , VAL, NULL, NULL, NULL == (void*)(VAL)                                           ) }
#define UT_ASSERT_STR_EQUAL(ACT, EXP)            { _UT_ASSERT_CHEK( "ASSERT_STR_EQUAL"     , ACT, EXP , NULL, 0 != strcmp((const char*)ACT, (const char*)EXP)                ) }
#define UT_ASSERT_STR_NOT_EQUAL(ACT, EXP)        { _UT_ASSERT_CHEK( "ASSERT_STR_NOT_EQUAL" , ACT, EXP , NULL, !strcmp((const char*)ACT, (const char*)EXP)                    ) }
#define UT_ASSERT_NSTR_EQUAL(ACT, EXP, CNT)      { _UT_ASSERT_CHEK( "ASSERT_NSTR_EQUAL"    , ACT, EXP , CNT , 0 !=  strncmp((const char*)ACT, (const char*)EXP, (size_t)CNT) ) }
#define UT_ASSERT_NSTR_NOT_EQUAL(ACT, EXP, CNT)  { _UT_ASSERT_CHEK( "ASSERT_NSTR_NOT_EQUAL", ACT, EXP , CNT , !strncmp((const char*)ACT, (const char*)EXP, (size_t)CNT)      ) }
#define UT_ASSERT_DBL_EQUAL(ACT, EXP)            { _UT_ASSERT_CHEK( "ASSERT_DBL_EQUAL"     , ACT, EXP , NULL, (fabs((double)ACT - EXP) > __DBL_EPSILON__)                    ) }
#define UT_ASSERT_DBL_NOT_EQUAL(ACT, EXP)        { _UT_ASSERT_CHEK( "ASSERT_DBL_NOT_EQUAL" , ACT, EXP , NULL, (fabs((double)ACT - EXP) <= __DBL_EPSILON__)                   ) }
#define UT_ASSERT_NDBL_EQUAL(ACT, EXP, EPS)      { _UT_ASSERT_CHEK( "ASSERT_NDBL_EQUAL"    , ACT, EXP , EPS , (fabs((double)ACT - EXP) > fabs((double)EPS))                  ) }
#define UT_ASSERT_NDBL_NOT_EQUAL(ACT, EXP, EPS)  { _UT_ASSERT_CHEK( "ASSERT_NDBL_NOT_EQUAL", ACT, EXP , EPS , (fabs((double)ACT - EXP) <= fabs((double)EPS))                 ) }

#define _UT_ASSERT_CHEK(MSG, ACT, EXP, EPS, ASSERT)                                  \
    __unit_test_assert_beg(ut_stat);                                                 \
    if(ut_stat->run) {                                                               \
    typeof(ACT) _ACT = ACT;                                                          \
    typeof(EXP) _EXP = EXP;                                                          \
    typeof(EPS) _EPS = EPS;                                                          \
    __unit_test_assert_val(ut_stat, (void*)(&_ACT), (void*)(&_EXP), (void*)(&_EPS),  \
                                     sizeof( _ACT),  sizeof( _EXP),  sizeof( _EPS)); \
    if(ASSERT){                                                                      \
    __unit_test_assert_feil(ut_stat);                                                \
    }else{                                                                           \
    __unit_test_assert_suce(ut_stat);                                                \
    }                                                                                \
    __unit_test_assert_end(ut_stat);                                                 \
    }                                                                                \
    __unit_test_assert_info(ut_stat, MSG, #ACT, #EXP, #EPS);

#endif /*YAYA_UNIT_MACRO_H*/

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

#define UT_BLOCK_BEG(NAME)                __unit_test_block_beg(ut_stat, #NAME);   do { switch (1)
#define UT_BLOCK_INIT        case 1:      __unit_test_block_init(ut_stat)
#define UT_BLOCK_TEST        case 2:      __unit_test_block_test(ut_stat)
#define UT_BLOCK_FREE        case 3:      __unit_test_block_free(ut_stat)
#define UT_BLOCK_END         } while(0);    __unit_test_block_end(ut_stat)

#define UT_EXIT(MSG)        __unit_test_group_ext(ut_stat, #MSG);  exit(1)
#define UT_RETURN(MSG)      __unit_test_group_ret(ut_stat, #MSG);  return
#define UT_BREAK(MSG)       __unit_test_group_brk(ut_stat, #MSG);  break
#define UT_MESAGE(MSG)      __unit_test_group_msg(ut_stat, #MSG)

#define UT_ASSERT_BOOL(value)                                    { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( false == (bool)(value)                                                   ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_BOOL"          , #value , ""       , ""          ) }
#define UT_ASSERT_BOOL_TRUE(value)                               { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( false == (bool)(value)                                                   ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_BOOL_TRUE"     , #value , ""       , ""          ) }
#define UT_ASSERT_BOOL_FALSE(value)                              { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( false != (bool)(value)                                                   ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_BOOL_FALSE"    , #value , ""       , ""          ) }
#define UT_ASSERT_NUM_EQUAL(actual, expected)                    { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( (actual) != (expected)                                                   ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_NUM_EQUAL"     , #actual, #expected, ""          ) }
#define UT_ASSERT_NUM_NOT_EQUAL(actual, expected)                { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( (actual) == (expected)                                                   ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_NUM_NOT_EQUAL" , #actual, #expected, ""          ) }
#define UT_ASSERT_PTR_EQUAL(actual, expected)                    { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( (void*)(actual) != (void*)(expected)                                     ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_PTR_EQUAL"     , #actual, #expected, ""          ) }
#define UT_ASSERT_PTR_NOT_EQUAL(actual, expected)                { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( (void*)(actual) == (void*)(expected)                                     ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_PTR_NOT_EQUAL" , #actual, #expected, ""          ) }
#define UT_ASSERT_PTR_NULL(value)                                { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( NULL != (void*)(value)                                                   ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_PTR_NULL"      , #value , ""       , ""          ) }
#define UT_ASSERT_PTR_NOT_NULL(value)                            { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( NULL == (void*)(value)                                                   ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_PTR_NOT_NULL"  , #value , ""       , ""          ) }
#define UT_ASSERT_STR_EQUAL(actual, expected)                    { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( 0 != strcmp((const char*)actual, (const char*)expected)                  ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_STR_EQUAL"     , #actual, #expected, ""          ) }
#define UT_ASSERT_STR_NOT_EQUAL(actual, expected)                { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( !strcmp((const char*)actual, (const char*)expected)                      ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_STR_NOT_EQUAL" , #actual, #expected, ""          ) }
#define UT_ASSERT_NSTR_EQUAL(actual, expected, count)            { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( 0 !=  strncmp((const char*)actual, (const char*)expected, (size_t)count) ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_NSTR_EQUAL"    , #actual, #expected, #count      ) }
#define UT_ASSERT_NSTR_NOT_EQUAL(actual, expected, count)        { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( !strncmp((const char*)actual, (const char*)expected, (size_t)count)      ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_NSTR_NOT_EQUAL", #actual, #expected, #count      ) }
#define UT_ASSERT_DBL_EQUAL(actual, expected)                    { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( (fabs((double)actual - expected) > __DBL_EPSILON__)                      ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_DBL_EQUAL"     , #actual, #expected, ""          ) }
#define UT_ASSERT_DBL_NOT_EQUAL(actual, expected)                { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( (fabs((double)actual - expected) <= __DBL_EPSILON__)                     ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_DBL_NOT_EQUAL" , #actual, #expected, ""          ) }
#define UT_ASSERT_NDBL_EQUAL(actual, expected, granularity)      { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( (fabs((double)actual - expected) > fabs((double)granularity))            ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_NDBL_EQUAL"    , #actual, #expected, #granularity) }
#define UT_ASSERT_NDBL_NOT_EQUAL(actual, expected, granularity)  { _UT_ASSERT_BEG() _UT_ASSERT_CHEK( (fabs((double)actual - expected) <= fabs((double)granularity))           ) _UT_ASSERT_END() _UT_ASSERT_INFO( "ASSERT_NDBL_NOT_EQUAL", #actual, #expected, #granularity) }

#define _UT_ASSERT_BEG()    { __unit_test_assert_beg(ut_stat);
#define _UT_ASSERT_CHEK(x)    if(x){ _UT_ASSERT_FEIL() }else{ _UT_ASSERT_SUCE() }
#define _UT_ASSERT_SUCE()     __unit_test_assert_suce(ut_stat);
#define _UT_ASSERT_FEIL()     __unit_test_assert_feil(ut_stat);
#define _UT_ASSERT_END()      __unit_test_assert_end(ut_stat); }

#define _UT_ASSERT_INFO(MSG, ACT, EXT, EPS) \
    __unit_test_assert_info(ut_stat, MSG, ACT, EXT, EPS);

#endif /*YAYA_UNIT_MACRO_H*/

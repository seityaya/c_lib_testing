//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2022 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_UNIT_FUNC_H
#define YAYA_UNIT_FUNC_H

#define _ASSERT_BEG()                                     \

#define _ASSERT_FEIL()                                    \
    info->result = false;

#define _ASSERT_EXCEPTION(FLAG, MSG, ACT, EXT, EPS)       \
    info->test_flag |= FLAG;                              \
    strncpy(info->mesg,  MSG,   UNIT_TEST_MESG_SIZE);     \
    strncpy(info->value, ACT,   UNIT_TEST_MESG_SIZE);     \
    strncpy(info->expec, EXT,   UNIT_TEST_MESG_SIZE);     \
    strncpy(info->count, EPS,   UNIT_TEST_MESG_SIZE);

#define _ASSERT_END()                                     \
    if(info->result){                                     \
    info->test_count++;                                   \
    }else{                                                \
    return true;                                          \
    }

#define UT_BEG()                                          \
    strncpy(info->file, __FILE__,  UNIT_TEST_MESG_SIZE);  \
    info->line = __LINE__;                                \
    info->result = true

#define UT_END()                                          \
    return true

#define UT_EXIT(MSG)                                      \
    strncpy(info->mesg, MSG, UNIT_TEST_MESG_SIZE);        \
    info->result = false;                                 \
    return false

#define UT_ASSERT(value)                                         { _ASSERT_BEG(); if (false == (bool)(value))                                                   { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U <<  1U), "ASSERT ",               #value , "",        ""          );  _ASSERT_END(); }
#define UT_ASSERT_BOOL_TRUE(value)                               { _ASSERT_BEG(); if (false == (bool)(value))                                                   { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U <<  2U), "ASSERT_BOOL_TRUE",      #value , "",        ""          );  _ASSERT_END(); }
#define UT_ASSERT_BOOL_FALSE(value)                              { _ASSERT_BEG(); if (false != (bool)(value))                                                   { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U <<  3U), "ASSERT_BOOL_FALSE",     #value , "",        ""          );  _ASSERT_END(); }
#define UT_ASSERT_NUM_EQUAL(actual, expected)                    { _ASSERT_BEG(); if ((actual) != (expected))                                                   { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U <<  4U), "ASSERT_NUM_EQUAL",      #actual, #expected, ""          );  _ASSERT_END(); }
#define UT_ASSERT_NUM_NOT_EQUAL(actual, expected)                { _ASSERT_BEG(); if ((actual) == (expected))                                                   { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U <<  5U), "ASSERT_NUM_NOT_EQUAL",  #actual, #expected, ""          );  _ASSERT_END(); }
#define UT_ASSERT_PTR_EQUAL(actual, expected)                    { _ASSERT_BEG(); if ((void*)(actual) != (void*)(expected))                                     { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U <<  6U), "ASSERT_PTR_EQUAL",      #actual, #expected, ""          );  _ASSERT_END(); }
#define UT_ASSERT_PTR_NOT_EQUAL(actual, expected)                { _ASSERT_BEG(); if ((void*)(actual) == (void*)(expected))                                     { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U <<  7U), "ASSERT_PTR_NOT_EQUAL",  #actual, #expected, ""          );  _ASSERT_END(); }
#define UT_ASSERT_PTR_NULL(value)                                { _ASSERT_BEG(); if (NULL != (void*)(value))                                                   { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U <<  8U), "ASSERT_PTR_NULL",       #value , "",        ""          );  _ASSERT_END(); }
#define UT_ASSERT_PTR_NOT_NULL(value)                            { _ASSERT_BEG(); if (NULL == (void*)(value))                                                   { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U <<  9U), "ASSERT_PTR_NOT_NULL",   #value , "",        ""          );  _ASSERT_END(); }
#define UT_ASSERT_STR_EQUAL(actual, expected)                    { _ASSERT_BEG(); if (0 != strcmp((const char*)actual, (const char*)expected))                  { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U << 10U), "ASSERT_STR_EQUAL",      #actual, #expected, ""          );  _ASSERT_END(); }
#define UT_ASSERT_STR_NOT_EQUAL(actual, expected)                { _ASSERT_BEG(); if (!strcmp((const char*)actual, (const char*)expected))                      { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U << 11U), "ASSERT_STR_NOT_EQUAL",  #actual, #expected, ""          );  _ASSERT_END(); }
#define UT_ASSERT_NSTR_EQUAL(actual, expected, count)            { _ASSERT_BEG(); if (0 !=  strncmp((const char*)actual, (const char*)expected, (size_t)count)) { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U << 12U), "ASSERT_NSTR_EQUAL",     #actual, #expected, #count      );  _ASSERT_END(); }
#define UT_ASSERT_NSTR_NOT_EQUAL(actual, expected, count)        { _ASSERT_BEG(); if (!strncmp((const char*)actual, (const char*)expected, (size_t)count))      { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U << 13U), "ASSERT_NSTR_NOT_EQUAL", #actual, #expected, #count      );  _ASSERT_END(); }
#define UT_ASSERT_DBL_EQUAL(actual, expected)                    { _ASSERT_BEG(); if ((fabs((double)actual - expected) > __DBL_EPSILON__))                      { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U << 14U), "ASSERT_DBL_EQUAL",      #actual, #expected, ""          );  _ASSERT_END(); }
#define UT_ASSERT_DBL_NOT_EQUAL(actual, expected)                { _ASSERT_BEG(); if ((fabs((double)actual - expected) <= __DBL_EPSILON__))                     { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U << 15U), "ASSERT_DBL_NOT_EQUAL",  #actual, #expected, ""          );  _ASSERT_END(); }
#define UT_ASSERT_NDBL_EQUAL(actual, expected, granularity)      { _ASSERT_BEG(); if ((fabs((double)actual - expected) > fabs((double)granularity)))            { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U << 14U), "ASSERT_NDBL_EQUAL",     #actual, #expected, #granularity);  _ASSERT_END(); }
#define UT_ASSERT_NDBL_NOT_EQUAL(actual, expected, granularity)  { _ASSERT_BEG(); if ((fabs((double)actual - expected) <= fabs((double)granularity)))           { _ASSERT_FEIL(); } _ASSERT_EXCEPTION( (1U << 15U), "ASSERT_NDBL_NOT_EQUAL", #actual, #expected, #granularity);  _ASSERT_END(); }

#endif /*YAYA_UNIT_FUNC_H*/

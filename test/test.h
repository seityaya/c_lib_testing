#ifndef TEST_C
#define TEST_C

#include "yaya_unit.h"

#define LIST_OF_TEST \
    X(ASSERT_ok                  ) \
    X(ASSERT_er                  ) \
    X(ASSERT_TRUE_ok             ) \
    X(ASSERT_TRUE_er             ) \
    X(ASSERT_FALSE_ok            ) \
    X(ASSERT_FALSE_er            ) \
    X(ASSERT_EQUAL_ok            ) \
    X(ASSERT_EQUAL_er            ) \
    X(ASSERT_NOT_EQUAL_ok        ) \
    X(ASSERT_NOT_EQUAL_er        ) \
    X(ASSERT_PTR_EQUAL_ok        ) \
    X(ASSERT_PTR_EQUAL_er        ) \
    X(ASSERT_PTR_NOT_EQUAL_ok    ) \
    X(ASSERT_PTR_NOT_EQUAL_er    ) \
    X(ASSERT_PTR_NULL_ok         ) \
    X(ASSERT_PTR_NULL_er         ) \
    X(ASSERT_PTR_NOT_NULL_ok     ) \
    X(ASSERT_PTR_NOT_NULL_er     ) \
    X(ASSERT_STRING_EQUAL_ok     ) \
    X(ASSERT_STRING_EQUAL_er     ) \
    X(ASSERT_STRING_NOT_EQUAL_ok ) \
    X(ASSERT_STRING_NOT_EQUAL_er ) \
    X(ASSERT_NSTRING_EQUAL_ok    ) \
    X(ASSERT_NSTRING_EQUAL_er    ) \
    X(ASSERT_NSTRING_NOT_EQUAL_ok) \
    X(ASSERT_NSTRING_NOT_EQUAL_er) \
    X(ASSERT_DOUBLE_EQUAL_ok     ) \
    X(ASSERT_DOUBLE_EQUAL_er     ) \
    X(ASSERT_DOUBLE_NOT_EQUAL_ok ) \
    X(ASSERT_DOUBLE_NOT_EQUAL_er )


#define X(NAME, ...) UNIT_TEST_GENERATE_FUNC(NAME);
LIST_OF_TEST
#undef X


static unit_test_func_t unit_test_func[] = {
    UNIT_TEST_GENERATE_ST_BEG
    #define X(NAME) UNIT_TEST_GENERATE_ST(NAME)
    LIST_OF_TEST
    #undef X
    UNIT_TEST_GENERATE_ST_END
};

#endif /*TEST_C*/

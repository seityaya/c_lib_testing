//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

#include "yaya_unit.h"

UT_FUNC_GEN(my_unit_test_macro){
    UT_BEG_GROUP(macro) {
        UT_BEG_GROUP(test1) {
            UT_ASSERT_BOOL_TRUE(true);
        }UT_END_GROUP;

        UT_BEG_GROUP(test2){
            UT_ASSERT_BOOL_TRUE(true);
        }UT_END_GROUP;

        UT_BLOCK_BEG(test3)
        {
            UT_BLOCK_INIT;
            int a = 0;
            int b = 0;
            UT_MESAGE(INIT);

            UT_BLOCK_TEST;
            a = 1;
            b = 1;
            UT_MESAGE(TEST);

            UT_BLOCK_FREE;
            a = -1;
            b = -1;
            UT_MESAGE(FREE);

        } UT_BLOCK_END;
    } UT_END_GROUP;
}

UT_FUNC_GEN(my_unit_test_ok)
{
    UT_BEG_GROUP(test)
    {
        UT_BEG_GROUP(OK)
        {
            UT_ASSERT_BOOL(0 == 0);
            UT_ASSERT_BOOL_TRUE(true);
            UT_ASSERT_BOOL_FALSE(false);
            UT_ASSERT_NUM_EQUAL(5, 5);
            UT_ASSERT_NUM_NOT_EQUAL(8, 9);

            UT_BEG_GROUP(ptr_eq){
                int a = 0;
                int *b = &a;

                UT_ASSERT_PTR_EQUAL(&a, b);
                UT_ASSERT_PTR_NOT_EQUAL(&a, &b);
            }
            UT_END_GROUP;

            UT_BEG_GROUP(ptr_nl){
                int *a = NULL;
                UT_ASSERT_PTR_NULL(a + 0);
                UT_ASSERT_PTR_NOT_NULL(a + 1);
            }
            UT_END_GROUP;

            UT_ASSERT_STR_EQUAL("test1", "test1");
            UT_ASSERT_STR_NOT_EQUAL("test1", "test2");
            UT_ASSERT_NSTR_EQUAL("test1", "test1", 5);
            UT_ASSERT_NSTR_NOT_EQUAL("test1", "test2", 5);
            UT_ASSERT_NDBL_EQUAL(3.00, 3.01, 0.1);
            UT_ASSERT_NDBL_NOT_EQUAL(3.00, 3.01, 0.001);
        }
        UT_END_GROUP;
    }
    UT_END_GROUP;
}

UT_FUNC_GEN(my_unit_test_er){
    UT_BEG_GROUP(test)
    {
        UT_BEG_GROUP(ER)
        {
            UT_ASSERT_BOOL(0 == 1);
            UT_ASSERT_BOOL_TRUE(false);
            UT_ASSERT_BOOL_FALSE(true);
            UT_ASSERT_NUM_EQUAL(5, 6);
            UT_ASSERT_NUM_NOT_EQUAL(8, 8);

            UT_BEG_GROUP(ptr_eq)
            {
                int a = 0;
                int *b = &a;

                UT_ASSERT_PTR_EQUAL(&a, &b);
                UT_ASSERT_PTR_NOT_EQUAL(&a, b);
            }
            UT_END_GROUP;

            UT_BEG_GROUP(ptr_nl)
            {
                int *a = NULL;

                UT_ASSERT_PTR_NULL(a + 1);
                UT_ASSERT_PTR_NOT_NULL(a);
            }
            UT_END_GROUP;

            UT_ASSERT_STR_EQUAL("test1", "test2");
            UT_ASSERT_STR_NOT_EQUAL("test1", "test1");
            UT_ASSERT_NSTR_EQUAL("test1", "test2", 5);
            UT_ASSERT_NSTR_NOT_EQUAL("test1", "test1", 5);
            UT_ASSERT_NDBL_EQUAL(3.00, 3.01, 0.001);
            UT_ASSERT_NDBL_NOT_EQUAL(3.00, 3.01, 0.1);
        }
        UT_END_GROUP;
    }
    UT_END_GROUP;
}

int main() {
    unit_test_t MyUnitTest = {0};
    unit_test_func_t MyUnitFunc[] = { NULL,
                                      my_unit_test_macro,
                                      my_unit_test_ok,
                                      my_unit_test_er,
                                      NULL
                                    };

    unit_test_init (&MyUnitTest, &MyUnitFunc);
    unit_test_start(&MyUnitTest);
    unit_test_print(&MyUnitTest);
    unit_test_stats(&MyUnitTest);

    return 0;
}

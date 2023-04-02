//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2023 Seityagiya Terlekchi. All rights reserved.

#include "yaya_unit.h"

UT_FUNC_GEN(my_unit_test_macro) {
    UT_GROUP_BEG(macro) {
        UT_GROUP_BEG(test1) {
            UT_GROUP_BEG(test1.1) {
                UT_GROUP_BEG(test1.1.1) {
                UT_MESAGE(EXEMPLE 1.1);
                } UT_GROUP_END;
                } UT_GROUP_END;
        } UT_GROUP_END;

        UT_GROUP_BEG(test2){
            UT_MESAGE(EXEMPLE 2);
        } UT_GROUP_END;

        UT_BLOCK_BEG(test3)
        {
            UT_BLOCK_INIT;
            UT_MESAGE(INIT);
            int a = 0;
            int b = 0;

            UT_BLOCK_TEST;
            UT_MESAGE(TEST);
            a = 1;
            b = 1;

            UT_BLOCK_FREE;
            UT_MESAGE(FREE);


            printf("%d %d\n", a, b);

        } UT_BLOCK_END;
    } UT_GROUP_END;
}

UT_FUNC_GEN(my_unit_test_ok) {
    UT_GROUP_BEG(test)
    {
        UT_GROUP_BEG(OK)
        {
            UT_ASSERT_BOOL_TR(true);
            UT_ASSERT_BOOL_FL(false);

            UT_ASSERT_BIT_EQ(    u8_c(255), u8_c(-1));
            UT_ASSERT_BIT_NQ(u8_c(256), u8_c(-128));

            UT_ASSERT_CHR_EQ(char_c('a'), char_c('a'));
            UT_ASSERT_CHR_NQ(char_c('a'), char_c('b'));

            UT_ASSERT_NUM_EQ(5, 5);
            UT_ASSERT_NUM_NQ(8, 9);

            UT_ASSERT_NUM_EQ(8000U, 8000U);
            UT_ASSERT_NUM_NQ(8000U, 9000U);

            UT_GROUP_BEG(ptr_eq){
                int a = 0;
                int *b = &a;

                UT_ASSERT_PTR_EQ(&a, b);
                UT_ASSERT_PTR_NQ(&a, &b);
            }
            UT_GROUP_END;

            UT_GROUP_BEG(ptr_nl){
                int *a = NULL;
                UT_ASSERT_NUL_EQ(a + 0);
                UT_ASSERT_NUL_NQ(a + 1);
            }
            UT_GROUP_END;

            UT_ASSERT_STR_EQ("test1", "test1");
            UT_ASSERT_STR_NQ("test1", "test2");
            UT_ASSERT_STR_EQ_N("test1", "test1", 5);
            UT_ASSERT_STR_NQ_N("test1", "test2", 5);
            UT_ASSERT_FLT_EQ_E(3.00, 3.01, 0.1);
            UT_ASSERT_FLT_NQ_E(3.00, 3.01, 0.001);

            UT_ASSERT_FLT_NQ(f32_c (1.0 / 3.0), f32_c (1.0 / 3.0));
            UT_ASSERT_FLT_NQ(f64_c (1.0 / 3.0), f64_c (1.0 / 3.0));
            UT_ASSERT_FLT_NQ(f128_c(1.0L / 3.0L), f128_c(1.0L / 3.0L));
        }
        UT_GROUP_END;
    }
    UT_GROUP_END;
}

UT_FUNC_GEN(my_unit_test_er){
    UT_GROUP_BEG(test)
    {
        UT_GROUP_BEG(ER)
        {
            UT_ASSERT_BOOL_TR(false);
            UT_ASSERT_BOOL_FL(true);

            UT_ASSERT_CHR_EQ(char_c('A'), char_c('B'));
            UT_ASSERT_CHR_NQ(char_c('A'), char_c('A'));

            UT_ASSERT_NUM_EQ(5, 6);
            UT_ASSERT_NUM_NQ(8, 8);

            UT_GROUP_BEG(ptr_eq)
            {
                int  A = 0;
                int *a = &A;

                int  B = 0;
                int *b = &B;

                UT_ASSERT_PTR_EQ(a, b);
                UT_ASSERT_PTR_NQ(a, a);
            }
            UT_GROUP_END;

            UT_GROUP_BEG(ptr_nl)
            {
                int *a = NULL;

                UT_ASSERT_NUL_EQ(a + 1);
                UT_ASSERT_NUL_NQ(a);
            }
            UT_GROUP_END;

            UT_ASSERT_STR_EQ("test1", "test2");
            UT_ASSERT_STR_NQ("test1", "test1");
            UT_ASSERT_STR_EQ_N("test1", "test2", 5);
            UT_ASSERT_STR_NQ_N("test1", "test1", 5);
            UT_ASSERT_FLT_EQ_E(3.00, 3.01, 0.001);
            UT_ASSERT_FLT_NQ_E(3.00, 3.01, 0.1);
        }
        UT_GROUP_END;
    }
    UT_GROUP_END;
}

int main() {
    unit_test_t MyUnTest = {0};

    unit_test_sett_t MyUnSett = { .suse = true,
                                  .stat = true,
                                  //print_map
                                  //info_block
                                  //
                                };

    unit_test_func_t MyUnFunc[] = { {0},
                                    {my_unit_test_macro, 1},
                                    {my_unit_test_ok,    1},
                                    {my_unit_test_er,    1},
                                    {0}
                                  };

    unit_test_init(&MyUnTest, MyUnFunc, &MyUnSett);

//    unit_test_print(&MyUnTest);
    unit_test_start(&MyUnTest);

    unit_test_stats(&MyUnTest);

    return 0;
}

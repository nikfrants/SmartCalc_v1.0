
//
// Created by nikolay on 1/2/24.
//

#include "tests.h"

#include <check.h>

//
START_TEST(push_part_1) {
  stack st;
  stackInit(&st);
  push(&st, initData(1, 0, 0));
  stNode *val = pop(&st);
  ck_assert_int_eq(val->data.value, 1);
  ck_assert_int_eq(val->data.type, 0);
  freeStack(&st);
  free(val);
}
END_TEST

Suite *calc_complements() {
  Suite *s = suite_create("pushPop");
  TCase *tc_create = tcase_create("pushPop");
  tcase_add_test(tc_create, push_part_1);
  // tcase_add_test(tc_create, calc_complements_part_2);
  // tcase_add_test(tc_create, calc_complements_part_3);
  suite_add_tcase(s, tc_create);
  return s;
}

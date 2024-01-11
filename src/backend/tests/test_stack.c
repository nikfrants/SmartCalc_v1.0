//
// Created by nikolay on 1/2/24.
//

#include <check.h>
#include "test.h"

//
START_TEST(push_1) {
  stack st;
  stackInit(&st);
  push(&st, initData(1, 0, 0, 0));
  stNode *val = top(&st);
  ck_assert_int_eq(val->data.number, 1);
  ck_assert_int_eq(val->data.type, 0);
  freeStack(&st);
}

START_TEST(empty_1) {
  stack st;
  stackInit(&st);
  int first = isEmpty(&st);
  push(&st, initData(1, 0, 0, 0));
  int second = isEmpty(&st);
  int third = isEmpty(&st);
  ck_assert_int_eq(first, 1);
  ck_assert_int_eq(second, 0);
  ck_assert_int_eq(third, 0);
  freeStack(&st);
}

END_TEST

START_TEST(pop_empty_1) {
  stack st;
  stackInit(&st);
  parseData first = pop(&st);
  ck_assert_int_eq(first.type = E_STACK_UNDERFLOW, E_STACK_UNDERFLOW);
  freeStack(&st);
}

END_TEST

START_TEST(top_1) {
  stack st;
  stackInit(&st);
  push(&st, initData(1, 0, 0, 0));
  parseData node1;
  node1 = top(&st)->data;
  ck_assert_int_eq(node1.number, 1);
  pop(&st);
  ck_assert_ptr_null(top(&st));
  ck_assert_int_eq(node1.type, 0);
  freeStack(&st);
}

END_TEST

START_TEST(print_all_1) {
  parseData data1 = initData(1, 0, 0, 0);
  parseData data2 = initData(1, 0, 1, 0);

  stackPrintValue(data1, 0);
  stackPrintValue(data1, 1);

  stackPrintValue(data2, 0);
  stackPrintValue(data2, 1);
  stack st;
  stackInit(&st);
  push(&st, initData(1, 0, 0, 0));
  stackPrintByIndex(&st, 3);
  push(&st, initData(3, 0, 1, 0));
  push(&st, initData(3, 0, 2, 0));
  push(&st, initData(3, 0, 3, 0));
  push(&st, initData(3, 0, 4, 0));
  push(&st, initData(3, 0, 5, 0));
  push(&st, initData(3, 0, 5, 0));

  stackPrintByIndex(&st, 2);
  stackPrintAll(&st);
  for(int i = 0 ; i < 5 ; i++){
    parseData data = pop(&st);
    printParsedData(&data,  1);
  }
  freeStack(&st);
}

START_TEST(notatnion_to_str) {
  stack st;
  stackInit(&st);
  char s[200] = "-cos(4)+(((sin(4)+tan(4)+sqrt(4))+ln(4)+log(4)+asin(4))+acos(4)+atan(4))+1-1*1/1^1mod1";
 // int size;
  st = evaluatePolishNotation(s);
  char ans [200];
  char correct[200] = "4 cos ~ 4 sin 4 tan + 4 sqrt + 4 ln + 4 log + 4 asin + 4 acos + 4 atan + + 1 + 1 1 * 1 1 ^ / 1 m -";
  notationToString(s, ans);
  ck_assert_str_eq(ans, correct);
  freeStack(&st);
  // free(val);
}

END_TEST

Suite *Stack() {
  Suite *s = suite_create("Stack");
  TCase *tc_create = tcase_create("Stack");
  tcase_add_test(tc_create, push_1);
  tcase_add_test(tc_create, empty_1);
  tcase_add_test(tc_create, pop_empty_1);
  tcase_add_test(tc_create, print_all_1);
  tcase_add_test(tc_create, top_1);
  tcase_add_test(tc_create, notatnion_to_str);
  suite_add_tcase(s, tc_create);
  return s;
}

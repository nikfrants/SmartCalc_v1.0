//
// Created by nikolay on 1/2/24.
//

#include <check.h>
#include "test.h"


START_TEST(test_calc_polish_n) {
  char expression[300] =
      "1+~1*1-1/"
      "1^11+1+sin(30)+cos(90)+tan(20)+ln(4)+log(2)+asin(0.1)+acos(0.1)+atan(0."
      "1)+sqrt(4)+2mod4";
  int size;//, error;
  parseData *parsedExpression = {NULL};
  parsedExpression = parser(expression, &size);
  stack notation, reversed;
  stackInit(&notation), stackInit(&reversed);
  notation = evaluatePolishNotation(expression);
  while (notation.stSize) push(&reversed, pop(&notation));
  calc_s ans = calcPolishNotation(&reversed);
  printf("\n\nanswer: %0.20Lg\n\n", ans.n);
  ck_assert_int_eq(ans.n, 8.1588450400726407834);
  freeStack(&notation);
  freeStack(&reversed);
  free(parsedExpression);
}
END_TEST

Suite *Calc_polish_n() {
  Suite *s = suite_create("Calc_polish_n");
  TCase *tc_create = tcase_create("Calc_polish_n");
  tcase_add_test(tc_create, test_calc_polish_n);
  suite_add_tcase(s, tc_create);
  return s;
}

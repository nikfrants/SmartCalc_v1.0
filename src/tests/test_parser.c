//
// Created by nikolay on 1/3/24.
//

//
// Created by nikolay on 1/2/24.
//

#include <check.h>

#include "test.h"

//
START_TEST(parse_cos) {
  char s[9] = "cos(4)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_str_eq(newexpression[0].func, "cos");
  free(newexpression);
}
END_TEST



START_TEST(parse_tan) {
  char s[9] = "tan(4)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_str_eq(newexpression[0].func, "tan");
  free(newexpression);
}
END_TEST

START_TEST(parse_sin) {
  char s[9] = "sin(4)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_str_eq(newexpression[0].func, "sin");
  free(newexpression);
}
END_TEST


START_TEST(parse_acos) {
  char s[9] = "acos(4)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_str_eq(newexpression[0].func, "acos");
  free(newexpression);
}
END_TEST

START_TEST(parse_asin) {
  char s[9] = "asin(4)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_str_eq(newexpression[0].func, "asin");
  free(newexpression);
}
END_TEST

START_TEST(parse_atan) {
  char s[9] = "atan(4)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_str_eq(newexpression[0].func, "atan");
  free(newexpression);
}
END_TEST

START_TEST(parse_sqrt) {
  char s[9] = "sqrt(4)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_str_eq(newexpression[0].func, "sqrt");
  free(newexpression);
}
END_TEST


START_TEST(parse_ln) {
  char s[9] = "ln(4)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_str_eq(newexpression[0].func, "ln");
  free(newexpression);
}
END_TEST

START_TEST(parse_log) {
  char s[9] = "log(4)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_str_eq(newexpression[0].func, "log");
  free(newexpression);
}
END_TEST






// START_TEST(parse_empty) {
//
//   char s[9] = "4*4*sin";
//   stack st;
//   stackInit(&st);
//   parseData* newexpression = {NULL};
//   int size;
//   newexpression = parser(s, &size);
//   ck_assert_int_eq(newexpression[0].type, 1);
//   freeStack(&st);
//   free(newexpression);
// }
// END_TEST




Suite *Parser() {
  Suite *s = suite_create("Parser");
  TCase* tc_create = tcase_create("Parser");
  tcase_add_test(tc_create, parse_cos);
  tcase_add_test(tc_create, parse_tan);
  tcase_add_test(tc_create, parse_sin);
  tcase_add_test(tc_create, parse_acos);
  tcase_add_test(tc_create, parse_asin);
  tcase_add_test(tc_create, parse_atan);
  tcase_add_test(tc_create, parse_sqrt);
  tcase_add_test(tc_create, parse_ln);
  tcase_add_test(tc_create, parse_log);
  // tcase_add_test(tc_create, parse_empty);


  // tcase_add_test(tc_create, calc_complements_part_2);
  // tcase_add_test(tc_create, calc_complements_part_3);
  suite_add_tcase(s, tc_create);
  return s;
}

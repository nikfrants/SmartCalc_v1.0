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


START_TEST(parse_op_add) {
  char s[9] = "1+1";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_int_eq(newexpression[1].op, '+');
  free(newexpression);
}
END_TEST

START_TEST(parse_op_sub) {
  char s[9] = "1-1";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_int_eq(newexpression[1].op, '-');
  free(newexpression);
}
END_TEST


START_TEST(parse_op_mul) {
  char s[9] = "1*1";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_int_eq(newexpression[1].op, '*');
  free(newexpression);
}
END_TEST

START_TEST(parse_op_div) {
  char s[9] = "1/1";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_int_eq(newexpression[1].op, '/');
  free(newexpression);
}
END_TEST


START_TEST(parse_op_ex) {
  print("hi\n");
  // char s[9] = "sin(4)*4";
  //  char s[30] = "2mod4*88.348+12"; // correct
  // int arrsize = 100;
  // char s[ARR_SIZE] = "2/cos(pi/2)"; // nan - correct
  // char s[100] = "sin(+4.24)*--sin(1)*tan(2.421)*-tan(1)* 1245"; // correct
  //
  // char s[100] =  "sin(4.24 )*(-(-sin(1 )))*tan(2.421 )*(-tan(1 ))*1245";
  // correct
  //
  // char s[100] =  "*2"; // ToDo incorrect
  // char s[100] =  "((2)"; // ToDo incorrect
  // char s[200] =
  // "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  // //correct

  // char s[200] = "(2.1*(2)";
  //  char s[200] = "2*(*)*2";// ToDo incorrect
  char s[200] = "2/cos(pi/2)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  if (newexpression[0].type == INCORRECT_EXPRESSION)
    fprintf(stderr, "incorrect expression error");
  print("data:");
  print(s);

  print("\nparsed data:\n");
  printParsedData(newexpression, size);
  print("\nnotation\n");
  stack notation;
  notation = evaluatePolishNotation(s);
  stackPrintAll(&notation);
  stack reversed;
  stackInit(&reversed);
  // reverse &notation to &reversed
  //  stNode * temp;
  while (notation.stSize) {
    stNode* emp = pop(&notation);
    stNode * temp1 = createNode(emp->data);
    free(emp);
    push(&reversed, temp1);
  };
  // if(temp)
  //   free(temp);
  print("\nreversed\n");
  stackPrintAll(&reversed);
  print("\n");
  long double ans = toPolishNotation(&reversed);
  // free(&notation);
  printf("\nresult = %.8LF", ans);
  freeStack(&notation);
  freeStack(&reversed);
  free(newexpression);
}
END_TEST


START_TEST(parse_op_unary_sub) {
  char s[9] = "1~1";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_int_eq(newexpression[1].op, '~');
  free(newexpression);
}
END_TEST

START_TEST(parse_op_mod) {
  char s[9] = "1mod1";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_int_eq(newexpression[1].op, 'm');
  free(newexpression);
}
END_TEST


START_TEST(parse_op_open_paren) {
  char s[9] = "1(1*2)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_int_eq(newexpression[1].op, '(');
  free(newexpression);
}
END_TEST

START_TEST(parse_op_close_paren) {
  char s[9] = "()";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  ck_assert_int_eq(newexpression[1].op, ')');
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

  tcase_add_test(tc_create, parse_op_add);
  tcase_add_test(tc_create, parse_op_sub);
  tcase_add_test(tc_create, parse_op_mul);
  tcase_add_test(tc_create, parse_op_div);
  tcase_add_test(tc_create, parse_op_ex);
  tcase_add_test(tc_create, parse_op_unary_sub);
  tcase_add_test(tc_create, parse_op_mod);
  tcase_add_test(tc_create, parse_op_open_paren);
  tcase_add_test(tc_create, parse_op_close_paren);


  // tcase_add_test(tc_create, parse_empty);


  // tcase_add_test(tc_create, calc_complements_part_2);
  // tcase_add_test(tc_create, calc_complements_part_3);
  suite_add_tcase(s, tc_create);
  return s;
}

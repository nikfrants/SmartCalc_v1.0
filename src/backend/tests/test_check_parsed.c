//
// Created by nikolay on 1/11/24.
//
//
// Created by nikolay on 1/2/24.
//

#include <check.h>

#include "test.h"

//
START_TEST(pest_parsed_check_brackets) {
  int size;
  char expression[300] = "1+1";
  char expression1[300] = "1(+1";
  char expression2[300] = "1+1)";
  parseData *inputStr = parser(expression, &size);
  parseData *inputStr1 = parser(expression1, &size);
  parseData *inputStr2 = parser(expression2, &size);

  int ans = check(inputStr, size, expression);
  int ans1 = check(inputStr1, size, expression1);
  int ans2 = check(inputStr2, size, expression2);
  ck_assert_int_eq(ans, E_NO_ERRORS);
  ck_assert_int_eq(ans1, E_INCORRECT_BRACKETS_SEQUENE);
  ck_assert_int_eq(ans2, E_INCORRECT_BRACKETS_SEQUENE);

  free(inputStr);
  free(inputStr1);
  free(inputStr2);
}
END_TEST

START_TEST(pest_parsed_check_operations) {
  int size, size1, size2, size3, size4, size5, size6, size7;
  char expression[300] = "1+mod2";
  char expression1[300] = "1**1";
  char expression2[300] = "1^^1";
  char expression3[300] = "1//1";
  char expression4[300] = "1+2modmod1+1";
  char expression5[300] = "1sinsin1";
  char expression6[300] = "x";
  char expression7[300] = "1+mod";

  parseData *inputStr = parser(expression, &size);
  parseData *inputStr1 = parser(expression1, &size1);
  parseData *inputStr2 = parser(expression2, &size2);
  parseData *inputStr3 = parser(expression3, &size3);
  parseData *inputStr4 = parser(expression4, &size4);
  parseData *inputStr5 = parser(expression5, &size5);
  parseData *inputStr6 = parser(expression6, &size6);
  parseData *inputStr7 = parser(expression7, &size7);

  int ans = check(inputStr, size, expression);
  int ans1 = check(inputStr1, size1, expression1);
  int ans2 = check(inputStr2, size2, expression2);
  int ans3 = check(inputStr3, size3, expression3);
  int ans4 = check(inputStr4, size4, expression4);
  int ans5 = check(inputStr5, size5, expression5);
  int ans6 = check(inputStr6, size6, expression6);
  int ans7 = check(inputStr7, size7, expression7);
  free(inputStr);
  free(inputStr1);
  free(inputStr2);
  free(inputStr3);
  free(inputStr4);
  free(inputStr5);
  free(inputStr6);
  free(inputStr7);

  ck_assert_int_eq(ans, E_MOD_HAS_ONE_NUMBERS);
  ck_assert_int_eq(ans1, E_TWO_MULTIPLES_NEARBODY);
  ck_assert_int_eq(ans2, E_TWO_POW_NEARBODY);
  ck_assert_int_eq(ans3, E_TWO_DIVISION_NEARBODY);
  ck_assert_int_eq(ans4, E_TWO_MOD_NEARBODY);
  ck_assert_int_eq(ans5, E_TWO_FUNCTIONS_NEARBODY);
  ck_assert_int_eq(ans6, E_ONLY_DIGITS_EXIST);
  ck_assert_int_eq(ans7, E_INCORRECT_EXPRESSION);

  // free(inputStr);
}

END_TEST

Suite *Check_parsed() {
  Suite *s = suite_create("Check_parsed");
  TCase *tc_create = tcase_create("Check_parsed");
  tcase_add_test(tc_create, pest_parsed_check_brackets);
  tcase_add_test(tc_create, pest_parsed_check_operations);

  // tcase_add_test(tc_create, calc_complements_part_2);
  // tcase_add_test(tc_create, calc_complements_part_3);
  suite_add_tcase(s, tc_create);
  return s;
}

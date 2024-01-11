//
// Created by nikolay on 1/3/24.
//

#include "test.h"

void run_test(Suite *thesuit) {
  SRunner *therunner = srunner_create(thesuit);
  srunner_run_all(therunner, CK_NORMAL);
  srunner_free(therunner);
  printf("\n");
}

int main() {
  printf("================= TESTING =================\n\n");
  Suite *stack = Stack();
  Suite *parser = Parser();
  Suite *check_parsed = Check_parsed();
  Suite *calc_polish_n = Calc_polish_n();




  run_test(stack);
  run_test(parser);
  run_test(check_parsed);
  run_test(calc_polish_n);
  printf("================= END =================\n");
  return 0;
}
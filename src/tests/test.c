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
  run_test(stack);  // Запуск тестов из тестового кейса

  run_test(parser);
  printf("================= END =================\n");
  return 0;
}
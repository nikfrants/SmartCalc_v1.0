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
  Suite *s_1 = pushPop();  // Создание тестового кейса create_matrix

  run_test(s_1);  // Запуск тестов из тестового кейса

  printf("================= END =================\n");
  return 0;
}
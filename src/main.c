//
// Created by nikolay on 12/31/23.
//

/*
     ветка develop - всегда рабочая
     делаешь от develop свою ветку, там работаешь,
     когда функция готова, мерджим в девелоп
 */

#include "smart_calc.h"
#include "stdio.h"

int main() {
  printf("Hello, World!\n");

  stack st;
  stackInit(&st);

  push(&st, 1);

  stackPrintByIndex(&st, 0);
  int val = pop(&st);
  printf("%d\n", val);
  stackPrintByIndex(&st, 0);

  return 0;
}
// codeium


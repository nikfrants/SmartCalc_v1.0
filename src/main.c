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
  print("hi, ");

  stack st;
  stackInit(&st);
  push(&st, initData(1, 0, 0));

  stackPrintByIndex(&st, 0);
  stNode* val = pop(&st);

  stackPrintValue(val->data,0);

  push(&st, initData(2, '(', 1));

  stackPrintByIndex(&st, 0);
  pop(&st);

  push(&st, initData(3, '(', 0));
  push(&st, initData(2, '(', 0));
  push(&st, initData(1, '(', 0));

print("\n\n\n");
  stackPrintAll(&st);
  print("\n");
  char s[9] = "sin(4)4+5";

  float n = atof(s);
  printf("n = %f", n);
  char expr[5] = "sin(1)";
  parseData *newexpression = {NULL} ;
  int size; ;
  print("\n\n\n");

  newexpression = parser(s, &size);
  for (int i = 0; i < size; ++i) {
    if (newexpression[i].type == 1)
      printf(" %Lg ", newexpression[i].ldval);
    else if (newexpression[i].type == 2)
      printf(" %f ", newexpression[i].fval);
    else if (newexpression[i].type == 3)
      printf(" %c ", newexpression[i].operator);
    else
      printf(" %s ", newexpression[i].func);

  }
 free(newexpression);
  return 0;
}


void print(char * s) {
  printf("%s\n", s);
}
//
// Created by nikolay on 12/31/23.
//

/*
     ветка develop - всегда рабочая
     делаешь от develop свою ветку, там работаешь,
     когда функция готова, мерджим в девелоп
 */

#include "stack.h"
#include "stdio.h"
#define ARR_SIZE 100

int main() {
  print("hi\n");

  int size, error;
  char s[200] = "--acos(0.234)* - e ++ sin(+4.24)*--sin(1)*tan(2.421)*-tan(1)* a+pimodb+2/1+ln(10)+log(1)";
  parseData* newexpression = {NULL};

  newexpression = parser(s, &size);
  error = check(newexpression, size, s);
  if (error != E_NO_ERRORS) {
    printf("Error - %s", errorDescription(error));
    return error;
  }
  stack notation, reversed;
  stackInit(&notation), stackInit(&reversed);
  notation = evaluatePolishNotation(s);
  while (notation.stSize) push(&reversed, pop(&notation));
  calc_s ans = calcPolishNotation(&reversed);
  printf("\nresult: %.15LF\nerror - %s", ans.n, errorDescription(ans.e));

  freeStack(&notation);
  freeStack(&reversed);
  free(newexpression);

  return 0;
}


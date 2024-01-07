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
  int size;
  char s[200] = "--acos(0.234)* - 2";
  parseData* newexpression = {NULL};
  newexpression = parser(s, &size);
  // print("data:");
  // print(s);
  // print("\nparsed data:\n");
  // printParsedData(newexpression, size);
  // print("\nnotation\n");
  int error = check(newexpression, size, s);
  if (error != E_NO_ERRORS) printf("Error - %s", errorDescription(error));

  stack notation, reversed;
  stackInit(&notation), stackInit(&reversed);
  notation = evaluatePolishNotation(s);
  // stackPrintAll(&notation);
  // print("\n");
  while (notation.stSize) {
    push(&reversed, pop(&notation));
  }
  // print("\nreversed\n");
  // stackPrintAll(&reversed);
  // print("\n");

  calc_s ans = calcPolishNotation(&reversed);
  printf("\nresult: %.15LF\nerror - %s", ans.n, errorDescription(ans.e));


  freeStack(&notation);
  freeStack(&reversed);
  free(newexpression);

  return 0;
}


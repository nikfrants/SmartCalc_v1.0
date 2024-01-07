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
  char s[200] = "a+b";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  if (newexpression[0].type == E_INCORRECT_EXPRESSION) {
    fprintf(stderr, "incorrect expression error");
    return 0;
  }
  print("data:");
  print(s);
  print("\nparsed data:\n");
  printParsedData(newexpression, size);
  print("\nnotation\n");
  int error = check_brackets(newexpression, size);
  if (error < -100) {
    print(errorDescription(error));
    return 0;
  }
  error = check_operations(newexpression, size);
  if (error < -100) {
    print(errorDescription(error));
    return 0;
  }
  error = check_digits_in_str(s);
  if (error < -100) {
    print(errorDescription(error));
    return 0;
  }
  error = check_digits_near_dot(s);
  if (error < -100) {
    print(errorDescription(error));
    return 0;
  }

  stack notation;
  notation = evaluatePolishNotation(s);
  stackPrintAll(&notation);
  stack reversed;
  stackInit(&reversed);
  print("\n");
  // reverse &notation to &reversed
  //  stNode * temp;
  // reverse notatnion

  while (notation.stSize) {
    push(&reversed, pop(&notation));
  };
  // if(temp)
  //   free(temp);
  print("\nreversed\n");
  stackPrintAll(&reversed);
  print("\n");

  calc_s ans = calcPolishNotation(&reversed);
  // free(&notation);
  printf("\nresult: %.15LF\nerror - %s", ans.n, errorDescription( ans.e));

  freeStack(&notation);
  freeStack(&reversed);
  free(newexpression);

  return 0;
}


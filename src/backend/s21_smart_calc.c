//
// Created by nikolay on 12/31/23.
//

/*
     ветка develop - всегда рабочая
     делаешь от develop свою ветку, там работаешь,
     когда функция готова, мерджим в девелоп
 */

#include "stack.h"
#define ARR_SIZE 100

calc_s calculate(char s[], variables vars_In_Notatation[]) {
  // int main(){
  print("hi\n");
  // char s[300];
  int size, error;

  // strcpy(s,s);

  parseData* newexpression = {NULL};

  newexpression = parser(s, &size);
  error = check(newexpression, size, s);
  if (error != E_NO_ERRORS) {
    // printf("Error - %s", errorDescription(error));
    calc_s ans ={0,error};
    return ans;
    // return ans.n;
  }
  stack notation, reversed;
  stackInit(&notation), stackInit(&reversed);
  notation = evaluatePolishNotation(s);
  while (notation.stSize) push(&reversed, pop(&notation));

  calc_s ans = calcPolishNotation(&reversed, vars_In_Notatation);
  // printf("\nresult: %.15LF\nerror - %s", ans.n, errorDescription(ans.e));
  // print("\n\n");
  freeStack(&notation);
  notation = evaluatePolishNotation(s);
  char* str = notationToString(s);
  // printf("%s", str);
  freeStack(&notation);
  freeStack(&reversed);
  free(newexpression);
  return ans;
  // return ans.n;
}


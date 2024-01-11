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

// calc_s calculate(char s[]) {
int main(){
  long double answer;
  char expression[300] =
      "1+~1*1-1/"
      "1^11+1+sin(30)+cos(90)+tan(20)+ln(4)+log(2)+asin(0.1)+acos(0.1)+atan(0."
      "1)+sqrt(4)+2mod4";
  int size, error;
  parseData *parsedExpression = {NULL};
  parsedExpression = parser(expression, &size);
  error = check(parsedExpression, size, expression);

  stack notation, reversed;
  stackInit(&notation), stackInit(&reversed);
  notation = evaluatePolishNotation(expression);
  while (notation.stSize) push(&reversed, pop(&notation));
  char *ans[300];
  getPolish(expression, ans);
  printf("POLISH STRING: \n\n\n%s\n\n\n", *ans);
  // ck_assert_str_eq(ans.n, 8.1588450400726407834);
  // char * error2 = errorDescription(2);
  // ck_assert_int_eq(ans1, E_INCORRECT_BRACKETS_SEQUENE);
  // ck_assert_int_eq(ans2, E_INCORRECT_BRACKETS_SEQUENE);
  freeStack(&notation);
  freeStack(&reversed);
  free(parsedExpression);



  return 0;
}


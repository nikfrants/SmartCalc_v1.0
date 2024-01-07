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
  // stack st;
  // stackInit(&st);
  // stack st2;
  // stackInit(&st2);
  // stNode* node;
  // push(&st, createNode(initData(1, 0, 0, 0)));
  // push(&st, createNode(initData(2, 0, 0, 0)));
  // push(&st, createNode(initData(2, 0, 0, 0)));
  // push(&st, createNode(initData(2, 0, 0, 0)));
  // node = pop(&st);
  // push(&st2, createNode(node->data));
  // free(node);
  // node = pop(&st);
  // push(&st2, createNode(node->data));
  // free(node);
  // node = pop(&st);
  // push(&st2, createNode(node->data));
  // free(node);
  //
  // freeStack(&st);
  // freeStack(&st2);
  // return 0;
  // char s[9] = "sin(4)*4";
  //  char s[30] = "2mod4*88.348+12"; // correct
  // int arrsize = 100;
  // char s[ARR_SIZE] = "2/cos(pi/2)"; // nan - correct
  // char s[100] = "sin(+4.24)*--sin(1)*tan(2.421)*-tan(1)* 1245"; // correct
  //
  // char s[100] =  "sin(4.24 )*(-(-sin(1 )))*tan(2.421 )*(-tan(1 ))*1245";
  // correct
  //
  // char s[100] =  "*2"; // ToDo incorrect
  // char s[100] =  "((2)"; // ToDo incorrect
  // char s[200] =
  // "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  // //correct

  // char s[200] = "(2.1*(2)";
  //  char s[200] = "2*(*)*2";// ToDo incorrect
  // char s[200] = "2/cos(pi/2)";
  char s[200] = "2/cos(pi/2)";
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

  calc_s ans = toPolishNotation(&reversed);
  // free(&notation);
  printf("\nresult: %.15LF\nerror - %s", ans.n, errorDescription( ans.e));

  freeStack(&notation);
  freeStack(&reversed);
  free(newexpression);

  return 0;
}


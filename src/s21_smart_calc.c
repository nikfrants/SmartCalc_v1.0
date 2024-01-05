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
void printParsedData(parseData* data, int size);

void shiftArray(char* arr, int start, int end, int shift, int direction) {
  if (direction == 1) {  // Сдвиг вправо
    for (int i = end; i >= start; i--) {
      arr[i + shift] = arr[i];
    }
  } else if (direction == 0) {  // Сдвиг влево
    for (int i = start; i <= end; i++) {
      arr[i] = arr[i + shift];
    }
  } else {
    printf(
        "Неверное направление сдвига. Используйте 0 для сдвига влево или 1 для "
        "сдвига вправо.\n");
  }
}

int main() {
  print("hi\n");
  // char s[9] = "sin(4)*4";
 //  char s[30] = "2mod4*88.348+12"; // correct
  int arrsize = 100;
 // char s[ARR_SIZE] = "2/cos(pi/2)"; // nan - correct
   //char s[100] = "sin(+4.24)*--sin(1)*tan(2.421)*-tan(1)* 1245"; // correct
//
 // char s[100] =  "sin(4.24 )*(-(-sin(1 )))*tan(2.421 )*(-tan(1 ))*1245"; correct
 //
  //char s[100] =  "*2"; // ToDo incorrect
 // char s[100] =  "((2)"; // ToDo incorrect
//  char s[200] =  "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";correct


  // char s[200] = "(2.1*(2)";
//  char s[200] = "2*(*)*2";// ToDo incorrect
  char s[200] = "2/cos(pi/2)";
  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  if (newexpression[0].type == INCORRECT_EXPRESSION)
    fprintf(stderr, "incorrect expression error");
  print("data:");
  print(s);

  print("\nparsed data:\n");
  printParsedData(newexpression, size);
  print("\nnotation\n");
  stack notation;
  notation = evaluatePolishNotation(s);
  stackPrintAll(&notation);
  stack reversed;
  stackInit(&reversed);
  // reverse &notation to &reversed
  while (notation.stSize) push(&reversed, pop(&notation)->data);
  print("\nreversed\n");
  stackPrintAll(&reversed);
  print("\n");
  long double ans = calcPolishNotation (&reversed);
  // free(&notation);
  printf("\nresult = %.8LF", ans);
  freeStack(&notation);
  freeStack(&reversed);
  free(newexpression);
  return 0;
}

void printParsedData(parseData* data, int size) {
  for (int i = 0; i < size; ++i) {
    if (data[i].type == TYPE_DIGIT) printf("%Lg ", data[i].number);
    if (data[i].type == TYPE_BRACKET)
      printf("%c ", data[i].op);
    else if (data[i].type == TYPE_OPERATOR)
      printf("%c ", data[i].op);
    else if (data[i].type == TYPE_FUNCTION)
      printf("%s ", data[i].func);
    else if (data[i].type == TYPE_VARIABLE)
      printf("%s ", data[i].varName);
  }
}

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

void printParsedData(parseData* data, int size);

// функция которая сдвигает массив на данное число элементов в данную сторону


  void shiftArray(char *arr, int start, int end, int shift, int direction) {
    if (direction == 1) {  // Сдвиг вправо
      for (int i = end; i >= start; i--) {
        arr[i + shift] = arr[i];
      }
    } else if (direction == 0) {  // Сдвиг влево
      for (int i = start; i <= end; i++) {
        arr[i - shift] = arr[i];
      }
    } else {
      printf("Неверное направление сдвига. Используйте 0 для сдвига влево или 1 для сдвига вправо.\n");
    }
  }


int main() {
  print("hi\n");
  // char s[9] = "sin(4)*4";
  // char s[30] = "2mod4*88.348+12";
  char s[20] = "sin(30)";

  if(s[0] == '-') {
    shiftArray(s, 0, 19, 1,1);
    s[0]='0';
  }
    for(int i = 0; i < 19; i++) {
      if (s[i] == '(' && s[i+1] == '-') {
        shiftArray(s, i, 19, 1,1);
        s[i+1] = '0';
      }
    }

  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);
  if (newexpression[0].type == INCORRECT_EXPRESSION)
    fprintf(stderr, "incorrect expression error");
  print("data:");
  printf(s);

  print("\nparsed data:\n");
  printParsedData(newexpression, size);
  print("\nnotation\n");
  stack notation;
  notation = evaluatePolishNotation(s);
  stackPrintAll(&notation);
  // free(&notation);
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

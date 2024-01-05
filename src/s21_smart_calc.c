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

  void shiftArray(char *arr, int start, int end, int shift, int direction) {
    if (direction == 1) {  // Сдвиг вправо
      for (int i = end; i >= start; i--) {
        arr[i + shift] = arr[i];
      }
    } else if (direction == 0) {  // Сдвиг влево
      for (int i = start; i <= end; i++) {
        arr[i] = arr[i+shift];
      }
    } else {
      printf("Неверное направление сдвига. Используйте 0 для сдвига влево или 1 для сдвига вправо.\n");
    }
  }


int main() {
  print("hi\n");
  // char s[9] = "sin(4)*4";
  // char s[30] = "2mod4*88.348+12";
    int arrsize = 100;
  char s[ARR_SIZE] = "sin(+4.24)*--sin(1)*tan(2.421)*-tan(1)* 1245";
    /*
      крайние случаи обработки некорректной строки
       минус
    1    вначале строки - поставить между скобкой и минусом 0:  "-3*2(3)" - "0-3*2(3)"
    2    минус после скобки - поставить перед ним 0:  "3*2(-3)" - "3*2(0-3)"
    3    двойной минус - заменить на +: "3*2--3" - "3*2+3"
      плюс
    4    двойной плюс - заменить на один плюс: "3++2+2" - "3+2"
    5    плюс между - * / и функцией - убрать: "3-+sin(2)" - "3-sin(2)"
    6    плюс после скобки - убрать: "3*(+2)" - "3*(2)"

    */
  if(s[0] == '-') {
    shiftArray(s, 0, arrsize-1, 1,1);
    s[0]='0';
  }
    for(int i = 0; i < arrsize-1;++i) {
      if(s[i] == '-' && s[i+1] == '-') { // -- = +
        shiftArray(s, i, arrsize-1, 1,0);
        s[i] = '+';
        i--;
      }
    }
    for(int i = 0; i < arrsize-1;++i) {
      if(s[i] == '+' && s[i+1] == '+') {
        shiftArray(s, i, arrsize-1, 1,0);
        i--;
      }
    }

    if(s[0] == '+') {
      shiftArray(s, 0, arrsize-1, 1,1);
      s[0]='0';
    }
    for(int i = 0; i < arrsize-1; i++) {
      if (s[i] == '(' && s[i+1] == '-') {
        shiftArray(s, i, arrsize-1, 1,1);
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

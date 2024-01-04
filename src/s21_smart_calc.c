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

int main() {
  print("hi\n");
  // char s[9] = "sin(4)*4";
  // char s[30] = "2mod4*88.348+12";
  char s[150] = "1+1";
  // char s[9] = "(.)(.)"; ( 0 ) ( 0 ) is it correct?

  parseData* newexpression = {NULL};
  int size;
  newexpression = parser(s, &size);

  print("data:");
  printf(s);

  print("\nparsed data:\n");
  printParsedData(newexpression, size);
  print("\nnotation\n");
  stack * notation ;
  notation = evaluatePolishNotation(s);
  stackPrintAll(notation);
  free(notation);
  free(newexpression);
  return 0;
}

void printParsedData(parseData* data, int size) {
  for (int i = 0; i < size; ++i) {
    if (data[i].type == 1)
      printf("%Lg ", data[i].number);
    else if (data[i].type == 3)
      printf("%c ", data[i].op);
    else if (data[i].type == 4)
      printf("%s ", data[i].func);
    else if (data[i].type == 5)
      printf("%s ", data[i].varName);
  }
}

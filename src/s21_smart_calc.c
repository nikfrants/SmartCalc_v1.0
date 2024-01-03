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

int main() {

  print("hello, ");
  char s[9] = "sin(4)4+5";

  float n = atof(s);
  printf("n = %f", n);
  parseData* newexpression = {NULL};
  int size;
  ;
  print("\n\n\n");

  newexpression = parser(s, &size);

  for (int i = 0; i < size; ++i) {
    if (newexpression[i].type == 1)
      printf(" %Lg ", newexpression[i].number);
    else if (newexpression[i].type == 3)
      printf(" %c ", newexpression[i].op);
    else
      printf(" %s ", newexpression[i].func);
  }
  free(newexpression);
  return 0;
}

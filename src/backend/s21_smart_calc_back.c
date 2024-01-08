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
  stack st;
  stackInit(&st);
  push(&st,  initData(1, 0, 0,0));
  parseData node1;
  parseData node2;
  node1 = top(&st)->data;
  // ck_assert_int_eq(node1.number, 1); // TODO Error
  node2 = pop(&st);
    if(top(&st) != NULL)
  node1 = top(&st)->data;
  // ck_assert_int_eq(node2.type = E_STACK_UNDERFLOW,E_STACK_UNDERFLOW);
  // ck_assert_int_eq(node1.type, 0);
  // free(node1);
  // free(node2);
  freeStack(&st);
}


//
// Created by nikolay on 1/1/24.
//

#ifndef SMART_CALC_H
#define SMART_CALC_H

#endif  // SMART_CALC_H

#define REALLOC_SIZE 10
#define STACK_MAX_SIZE 1000
#define STACK_OWERFLOW -100
#define STACK_UNDERFLOW -101

typedef int T;

typedef struct {
  int head;
  int size;
  int alloc_size;
  T *data;
} stack;

void stackInit(stack *st);
int push(stack *st, T const val);
int pop(stack *st);

int allocate(stack *st, int const increase);


void print(char *string);
void stackPrintValue(const T value);
int stackPrintByIndex(const stack *st, int index);
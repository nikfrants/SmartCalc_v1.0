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

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// typedef int T;
// typedef struct {
//   int head;
//   int size;
//   int alloc_size;
//   T *data; // и тут маллочить
// } stack;
//
// typedef int tData;

typedef struct parseData {
  long double ldval;  // type 1
  float fval;         // type 2
  char operator;      // type 3
  char func[4];       // type 4
  int lenth;
  int type;
} parseData;

typedef struct sData {
  long double value;
  char operator;
  int type;
} stData;

typedef struct stNode {
  stData data;
  struct stNode *next;
} stNode;

typedef struct {
  stNode *root;
  size_t stSize;
} stack;

int push(stack *st, stData val);
stNode *pop(stack *st);
stNode *top(const stack *st);

void stackInit(stack *st);
stData initData(int val, char symbol, int type);
void freeStack(stack *st);
stData initData(int val, char symbol, int type);
void print(char *string);
void stackPrintValue(const stData value, int useName);
int stackPrintByIndex(const stack *st, int index);
void stackPrintAll(const stack *st);
int isEmpty(stack *st);
parseData *parser(char *str, int *idx);
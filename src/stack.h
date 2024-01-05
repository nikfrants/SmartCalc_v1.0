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

#define TYPE_DIGIT 1
#define TYPE_FUNCTION 4
#define TYPE_OPERATOR 3
#define TYPE_BRACKET 2
#define TYPE_VARIABLE 5

#define E_POLISH_NOTATION -200
#define INCORRECT_EXPRESSION -102
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
//
// typedef struct parseData {
//   long double ldval;  // type 1
//
//   char op;            // type 3 operator
//   char func[4];       // type 4
//   int lenth;
//   int type;
//   int priority;
//   //todo shift numeric to one rifht
//   // 1 2 2 3 3 4 5
//   // 0 1 1 2 2 3 4
//   // ( + - * / ^ ~
//   //
//   // 2 - mod - 3
//   // 5 - sin cos tan asin acos atan sqrt ln log - 6
//
// } parseData;

//   // 1 2 2 3 3 4 5
//   // 0 1 1 2 2 3 4
//   // ( + - * / ^ ~
//   //
//   // 2 - mod - 3
//   // 5 - sin cos tan asin acos atan sqrt ln log - 6
typedef struct parseData {
  long double number;  // type 1
  char op;             // type 3 operator
  int type;

  char func[5];     // type 4 func
  char varName[5];  // type 5 variable
  int lenth;
  int priority;
} parseData;

typedef struct stNode {
  parseData data;
  struct stNode *next;
} stNode;

typedef struct {
  stNode *root;
  size_t stSize;
  // size_t variables[1000];
  //  int variablesSize;
  //  write  in variables[]  adresses of variables that stored in parsered
  // array. impossible for now cos stack doesn't exist while we processing
  // parsing
} stack;

int push(stack *st, parseData val);
stNode *pop(stack *st);
stNode *top(const stack *st);
int isEmpty(stack *st);
void stackInit(stack *st);
parseData initData(int val, char symbol, int type, int priority);
void freeStack(stack *st);
void print(char *string);
void stackPrintValue(const parseData value, int useName);
int stackPrintByIndex(const stack *st, int index);
void stackPrintAll(const stack *st);
stack  evaluatePolishNotation(char* expression) ;
parseData *parser(char *str, int *idx);
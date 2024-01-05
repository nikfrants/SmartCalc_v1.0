//
// Created by nikolay on 1/5/24.
//
#include "stack.h"
long double calcDigits(parseData *data, long double a, long double b);

long double calcPolishNotation(stack *data) {  // ToDo leaks
  stack ans;
  stackInit(&ans);
  stNode *a = NULL;   // ToDo leaks
  stNode *b = NULL;   // ToDo leaks
  stNode *op = NULL;  // ToDo leaks
  long double calc = NAN;
  while (top(data)) {
    if (data->root->data.type == TYPE_DIGIT) {
      push(&ans, pop(data)->data);
    } else {
      b = pop(&ans);
      op = pop(data);
      if (op->data.op != '\000' && strchr("+-*/^m", op->data.op)) a = pop(&ans);
      if (a == NULL) {
        if (a) free(a);
        if (b) free(b);
        if (op) free(op);
        return NAN;
      };  // ToDo pass erorr incorrect polish notation
      calc = calcDigits(&op->data, a->data.number, b->data.number);
      if (calc == NAN) {
        if (a) free(a);
        if (b) free(b);
        if (op) free(op);
        return 1;
      };  // ToDo pass erorr incorrect calculation
      if (calc > 0 && calc < 1.0e-16) calc = 0;
      push(&ans, initData(calc, op->data.op, TYPE_DIGIT, 0));
    }
  }
  // if (a) free(a);    // ToDo leaks
  // if (b) free(b);    // ToDo leaks
  // if (op) free(op);  // ToDo leaks
  long double answer = ans.root->data.number;
  freeStack(&ans);
  return answer;
}

long double calcDigits(parseData *data, long double a, long double b) {
  if (data->type == TYPE_OPERATOR) {
    if (data->op == '+')
      return a + b;
    else if (data->op == '-')
      return a - b;
    else if (data->op == '*')
      return a * b;
    else if (data->op == '/')
      return b != 0 ? a / b : NAN;
    else if (data->op == '^')
      return pow(a, b);
    else if (data->op == 'm')
      return b != 0 ? fmodl(a, b) : NAN;
    else if (data->op == '~')
      return -b;
    else if (data->op == 'p')
      return b;
  }
  if (data->type == TYPE_FUNCTION) {
    if (strncmp(data->func, "cos", 3) == 0) {
      return cos(b);
    } else if (strncmp(data->func, "sin", 3) == 0) {
      return sin(b);
    } else if (strncmp(data->func, "asin", 4) == 0) {
      return fabsl(b) <= 1 ? asin(b) : NAN;
    } else if (strncmp(data->func, "acos", 4) == 0) {
      return fabsl(b) <= 1 ? acos(b) : NAN;
    } else if (strncmp(data->func, "tan", 3) == 0) {
      return cos(b) != 0 ? tan(b) : NAN;
    } else if (strncmp(data->func, "exp", 3) == 0) {
      return exp(b);
    } else if (strncmp(data->func, "ln", 2) == 0) {
      return b >= 0 ? logl(b) : NAN;
    } else if (strncmp(data->func, "log", 3) == 0) {
      return b >= 0 ? log10l(b) : NAN;
    } else if (strncmp(data->func, "sqrt", 4) == 0) {
      return sqrt(b);
    }
  }
  return NAN;
}
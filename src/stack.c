//
// Created by nikolay on 1/1/24.
//

// own implementation of stack

#include <stdio.h>
#include <stdlib.h>

#include "smart_calc.h"

int push(stack *st, int const val) {
  allocate(st, 1);
  st->data[st->size] = val;
  st->size++;
  return 0;
}
void stackInit(stack *st) {
  st->head = 0;
  st->size = 0;
  st->alloc_size = 0;
  st->data = NULL;
}

int pop(stack *st) {
  if (st->size > 0) {
    st->size--;
    allocate(st, 0);
    return st->data[st->size];
  }
  return STACK_UNDERFLOW;
}

// allocate memory if needed
int allocate(stack *st, int const increase) {
  if (increase == 1) {
    if (st->size == STACK_MAX_SIZE) return STACK_OWERFLOW;
    if (st->alloc_size == 0) {
      st->data = (T *)calloc(REALLOC_SIZE, sizeof(T));
      st->alloc_size = REALLOC_SIZE;
      st->head = 0;
    } else if (st->size == st->alloc_size) {
      st->data =
          (T *)realloc(st->data, (st->alloc_size + REALLOC_SIZE) * sizeof(T));
      st->alloc_size += REALLOC_SIZE;
    }

    if (st->data != NULL) return 0;
    return 1;
  }
  if (!increase && st->size + REALLOC_SIZE < st->alloc_size) {  // < или <= ?
    st->data =
        (T *)realloc(st->data, (st->alloc_size - REALLOC_SIZE) * sizeof(T));
    st->alloc_size -= REALLOC_SIZE;
  }
  return 0;
}

void stackPrintValue(const T value) { printf("%d", value); }
int stackPrintByIndex(const stack *st, int index) {
  if (index >= st->size) {
    fprintf(stderr,"index out of range");
    return 1;
  }

  stackPrintValue(st->data[index]);
  return 0;
}
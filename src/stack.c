//
// Created by nikolay on 1/1/24.
//

// own implementation of stack

#include "stack.h"

int isEmpty(stack *st) { return st->stSize == 0; }
void initNode(stNode *node, parseData val) {
  node->data.number = val.number;
  node->data.op = val.op;
  node->data.type = val.type;
  node->next = NULL;

  node->data.lenth = val.lenth;
  node->data.priority = val.priority;
  strcpy(node->data.func, val.func);
}
void stackInit(stack *st) {
  st->stSize = 0;
  st->root = (stNode *)malloc(sizeof(stNode));
  st->root->data = initData(0, 0, 0);
  st->root->next = NULL;
}

parseData initData(int val, char symbol, int type) {
  parseData data;
  data.number = val;
  data.op = symbol;
  data.type = type;
  data.lenth = 0;
  data.priority = 0;
  strcpy(data.func, "\000\000\000\000\000");
  return data;
}
stNode *creatNode(parseData data) {
  stNode *tmp = malloc(sizeof(stNode));
  tmp->data.number = data.number;
  tmp->data.op = data.op;
  tmp->data.type = data.type;
  tmp->data.lenth = data.lenth;
  tmp->data.priority = data.priority;
  strcpy(tmp->data.func, data.func);
  tmp->next = NULL;
  return tmp;
}

int push(stack *st, parseData val) {
  if (st->stSize == 0) {
    initNode(st->root, val);  // st->root
    st->stSize++;
    return 1;
  }
  stNode *new = creatNode(val);
  // nodeInit(new, val);
  new->next = st->root;
  st->root = new;
  st->stSize++;
  return 0;
}

stNode *pop(stack *st) {
  if (st->stSize > 0) {
    stNode *new = creatNode(st->root->data);  // st->root;//
    stNode *tmp = st->root;
    st->root = st->root->next;
    free(tmp);
    st->stSize--;
    return new;
  }
  return NULL;
}
stNode *top(const stack *st) {
  if (st->stSize > 0) {
    // stNode *new = creatNode(st->root->data);
    return st->root;
  }
  return NULL;
}

void freeStack(stack *st) {
  if (st->root != NULL) {
    stNode *temp = st->root;
    while (temp->next != NULL) {
      st->root = st->root->next;
      free(temp);
      temp = st->root;
    }
    free(temp);
    // free(st->root);
    st->stSize = 0;
  }
}

void stackPrintValue(const parseData value, int useName) {
  if (value.type == 0) {
    if (useName) print("N_");
    printf("%Lg ", value.number);
  }
  if (value.type == 1) {
    if (useName) print("O_");
    printf("%c ", value.op);
  }
}

int stackPrintByIndex(const stack *st, int index) {
  if ((size_t)index >= st->stSize) {
    fprintf(stderr, "index out of range");
    return 1;
  }
  stNode *temp = creatNode(st->root->data);
  temp->next = st->root->next;
  for (int i = 0; i < index - 1; ++i) {
    temp->next = temp->next->next;
  }
  stackPrintValue(temp->data, 0);
  free(temp);
  return 0;
}
void stackPrintAll(const stack *st) {
  stNode *temp = st->root;
  for (int i = 0; temp != NULL || (size_t)i < st->stSize; ++i) {
    stackPrintValue(temp->data, 0);
    temp = temp->next;
  }
}

void print(char *s) { printf("%s\n", s); }
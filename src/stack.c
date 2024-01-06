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
  node->prev = NULL;

  node->data.lenth = val.lenth;
  node->data.priority = val.priority;
  strcpy(node->data.func, val.func);
}
void stackInit(stack *st) {
  st->stSize = 0;
  st->root = NULL;
  ;  //(stNode *)malloc(sizeof(stNode));
     // st->root->data = initData(0, 0, 0, 0);
     // st->root->next = NULL;
  //  st->root->prev = NULL;
}

parseData initData(long double val, char symbol, int type, int priority) {
  parseData data;
  data.number = val;
  data.op = symbol;
  data.type = type;
  data.lenth = 0;
  data.priority = priority;
  strcpy(data.func, "\000\000\000\000\000");
  return data;
}
stNode *createNode(parseData data) {
  stNode *tmp = malloc(sizeof(stNode));
  tmp->data.number = data.number;
  tmp->data.op = data.op;
  tmp->data.type = data.type;
  tmp->data.lenth = data.lenth;
  tmp->data.priority = data.priority;
  strcpy(tmp->data.func, data.func);
  tmp->next = NULL;
  tmp->prev = NULL;
  return tmp;
}

int push(stack *st, stNode *node) {
  if (st->root != NULL) {
    node->next = st->root;
    st->root->prev = node;
  } else {
    st->last = node;
  }
  st->root = node;
  st->root->prev = NULL;
  st->stSize++;
  return 0;
}

stNode *pop(stack *st) {
  if (st->root != NULL) {
    stNode *nodetoreturn = st->root;
    //  initNode(&nodetoreturn, st->root);

    if (st->root->next) st->root = st->root->next;
    // free(st->root);
    // todo dont create node, return pointer to root
    // stNode *new ;//= creatNode(st->root->data);  // st->root;//
    // new = st->root;
    // stNode *tmp = st->root;
    // st->root = st->root->next;
    // if (st->root) st->root->prev = NULL;
    // free(tmp);
    st->stSize--;
    nodetoreturn->next = NULL;
    nodetoreturn->prev = NULL;
    return nodetoreturn;
  }
  // st->last == 0;
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
  if (st == NULL) {
    return;
  }
  stNode *current = st->root;
  while (current != NULL) {
    stNode *temp = current;
    current = current->next;
    free(temp);
  }
  st->root = NULL;
  st->last = NULL;
  st->stSize = 0;
}
// void freeStack(stack *st) {
//   stNode *ptr = st->root;
//
//   while (ptr) {
//     stNode *next = ptr->next;
//     free(ptr);
//     ptr = next;
//   }
//
//   st->root = NULL;

  // if (st->root != NULL) {
  //   stNode *temp = st->root;
  //   while (temp->next != NULL) {
  //     st->root = st->root->next;
  //     free(temp);
  //     temp = st->root;
  //   }
  //   if(temp)
  //    free(temp);
  //   // free(st->root);
  //   st->stSize = 0;
  // }
// }

void stackPrintValue(const parseData value, int useName) {
  if (value.type == 0) {
    if (useName) print("T0Numr_");
    printf("%Lg ", value.number);
  }
  if (value.type == 1) {
    if (useName) print("T1undefined_");
    printf("%Lg ", value.number);
  }
  if (value.type == 2) {
    if (useName) print("T2undefined_");
  } /* printf("%Lg ", value.number);*/
  if (value.type == 3) {
    if (useName) print("T3op_");
    printf("%c ", value.op);
  }
  if (value.type == 4) {
    if (useName) print("T4Func_");
    printf("%s ", value.func);
  }
  if (value.type == 5) {
    if (useName) print("T5Var_");
    printf("%s ", value.varName);
  }
}

int stackPrintByIndex(const stack *st, int index) {
  if ((size_t)index >= st->stSize) {
    fprintf(stderr, "index out of range");
    return 1;
  }
  stNode *temp = createNode(st->root->data);
  temp->next = st->root->next;
  for (int i = 0; i < index - 1; ++i) {
    temp->next = temp->next->next;
  }
  stackPrintValue(temp->data, 0);
  free(temp);
  return 0;
}
void stackPrintAll(const stack *st) {
  //  stack reversedSt;
  // stackInit(&reversedSt);
  stNode *temp = st->last;
  // while (st->stSize) push(&reversedSt, pop(st)->data);
  int i = 0;
  while (i < st->stSize) {
    stackPrintValue(temp->data, 0);
    temp = temp->prev;
    ++i;
  }
  // for (int i = 0; temp != NULL || (size_t)i < reversedSt.stSize; ++i) {
  //   stackPrintValue(temp->data, 0);
  //   temp = temp->next;
  // }
}

void print(char *s) { printf("%s\n", s); }
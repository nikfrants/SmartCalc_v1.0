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
  strcpy(node->data.varName, val.varName);
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
  strcpy(data.varName, "\000\000\000\000\000");
  return data;
}
void copyData(parseData *var, parseData data) {
  var->number = data.number;
  var->op = data.op;
  var->type = data.type;
  var->lenth = data.lenth;
  var->priority = data.priority;
  strcpy(var->func, data.func);
  strcpy(var->varName, data.varName);
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

// int push(stack *st, stNode *node) {
//   if (st->root != NULL) {
//     node->next = st->root;
//     st->root->prev = node;
//   } else {
//     st->last = node;
//   }
//   st->root = node;
//   st->root->prev = NULL;
//   st->stSize++;
//   return 0;
// }
int push(stack *st, parseData data) {
  stNode *node = malloc(sizeof(stNode));
  initNode(node, data);

  if (st->root != NULL) {
    node->next = st->root;
    st->root->prev = node;
  } else {
    st->last = node;
  }
  st->root = node;
  st->stSize++;
  return 0;
}

parseData pop(stack *st) {
  if (st->root != NULL) {
    parseData returndata;
    copyData(&returndata, st->root->data);
    stNode *tmp = st->root;
    st->root = st->root->next;
    free(tmp);
    st->stSize--;
    return returndata;
  }
  return initData(0, 0, E_STACK_UNDERFLOW, -10);
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
    printf("%0.40Lg ", value.number);
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
  stNode *temp = st->last;
  int i = 0;
  while ((size_t)i < st->stSize) {
    stackPrintValue(temp->data, 0);
    temp = temp->prev;
    ++i;
  }

}

void print(char *s) { printf("%s\n", s); }

void printParsedData(parseData *data, int size) {
  for (int i = 0; i < size; ++i) {
    if (data[i].type == TYPE_DIGIT) printf("%Lg ", data[i].number);
    if (data[i].type == TYPE_BRACKET)
      printf("%c ", data[i].op);
    else if (data[i].type == TYPE_OPERATOR)
      printf("%c ", data[i].op);
    else if (data[i].type == TYPE_FUNCTION)
      printf("%s ", data[i].func);
    else if (data[i].type == TYPE_VARIABLE)
      printf("%s ", data[i].varName);
  }
}

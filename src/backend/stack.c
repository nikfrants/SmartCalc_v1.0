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
stNode *top(const stack *st) { // Todo top return parseData as
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
  // ToDo without createNode
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

char *notationToString(char s[], char *str) {
  stack notation, reversed;
  stackInit(&notation);
  notation = evaluatePolishNotation(s);
 // char str[1000] = {0};
  //for(int i = 0; i < 1000; ++i) str[i] = '\000';
int idx  = 0;
  stNode *temp = notation.last;
  for (int i = 0; temp; ++i) {
    char buf[150];
      if (temp->data.type == TYPE_DIGIT)
        if (fmodl(temp->data.number, (int)temp->data.number) == 0)
          sprintf(buf, "%.0LF", temp->data.number);
        else
          sprintf(buf, "%.2LF", temp->data.number);
    if (temp->data.type == TYPE_FUNCTION) sprintf(buf, "%s", temp->data.func);
    if (temp->data.type == TYPE_VARIABLE)
      sprintf(buf, "%s", temp->data.varName);
    if (temp->data.type == TYPE_OPERATOR)
      sprintf(buf, "%c", temp->data.op);
    // strcpy(&str[i], buf);
    str[i - 1] = ' ';
    for (int j = 0; buf[j]; ++j, ++i)
      str[i] = buf[j];

    temp = temp->prev;
    idx=i;;
  }
  str[idx] = '\000';
  freeStack(&notation);
  return str;
}
char *parsedToString(char *str, parseData *data,int size) {
  int idx = 0;
  for (int i = 0; i<size; ) {
    char buf[150];
    if (data[i].type == TYPE_DIGIT)
      if (fmodl(data[i].number, (int)data[i].number) == 0)
        sprintf(buf, "%.0LF", data[i].number);
      else
        sprintf(buf, "%.10LF", data[i].number);
    if (data[i].type == TYPE_FUNCTION) sprintf(buf, "%s", data[i].func);
    if (data[i].type == TYPE_VARIABLE)
      sprintf(buf, "%s", data[i].varName);
    if (data[i].type == TYPE_OPERATOR)
      sprintf(buf, "%c", data[i].op);
//    *str[i - 1] = ' ';
//    strcpy((str+i), buf);
    for (int j = 0; buf[j]; ++j, ++i)
       str[i] = buf[j];
    idx=i;
  }
  str[idx] = '\000';
  return *str;
}
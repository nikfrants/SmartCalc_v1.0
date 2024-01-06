//
// Created by nikolay on 1/6/24.
//

#include "stack.h"

// int check_parsed_str(stack* st) {}

int check_brackets(stack* st) {
  stNode* curr = st->root;
  int balance = 0;
  while (curr != NULL) {
    if (curr->data.type == TYPE_BRACKET && curr->data.op == '(') {
      balance++;
    } else if (curr->data.type == TYPE_BRACKET && curr->data.op == ')') {
      balance--;
    }
    if (balance < 0) return 1; // ToDo pass error incorrect brackets sequence
    curr = curr->next;
  }
  return 0;
}

int check_operations(stack* st) {
  stNode* curr = st->root;
  while (curr->next != NULL) {
    if (curr->data.type == TYPE_OPERATOR &&
        curr->next->data.type == TYPE_OPERATOR &&
        ((curr->data.op == '*' && curr->next->data.op == '*') ||
         (curr->data.op == '/' && curr->next->data.op == '/') ||
         (curr->data.op == '^' && curr->next->data.op == '^') ||
         (curr->data.op == 'm' && curr->next->data.op == 'm'))) {
      return 1; // ToDo pass error nearbody operators * / ^ m
    }
    curr = curr->next;
  }


  return 0;
}


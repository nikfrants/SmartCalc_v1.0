//
// Created by nikolay on 1/3/24.
//
#include "stack.h"
int is_left_associative(char op) {
  if (op && (op == '^' || op == '~')) return 0;
  return 1;
}
// polish notation implementation on c
stack evaluatePolishNotation(char* expression) {
  int strIndex = 0;
  int size = 0;
  stack polishNotation;
  stackInit(&polishNotation);
  stack processed;
  stackInit(&processed);
  parseData* inputStr = parser(expression, &size);
  while (strIndex < size) {
    if (inputStr[strIndex].type == TYPE_DIGIT) {
      push(&polishNotation, inputStr[strIndex]);
      ++strIndex;
    }
    if (strIndex < size && (inputStr[strIndex].type == TYPE_FUNCTION ||
                            inputStr[strIndex].type == TYPE_BRACKET &&
                                inputStr[strIndex].op == '(')) {
      push(&processed, inputStr[strIndex]);
      ++strIndex;
    }
    if (strIndex < size && inputStr[strIndex].type == TYPE_OPERATOR) {
      while (processed.stSize &&
             (top(&processed)->data.priority > inputStr[strIndex].priority ||
              top(&processed)->data.priority == inputStr[strIndex].priority &&
                  is_left_associative(inputStr[strIndex].op))) {
        push(&polishNotation, pop(&processed));
      }
      push(&processed, inputStr[strIndex]);
      ++strIndex;
    }
    if (strIndex < size &&
        (inputStr[strIndex].type == TYPE_BRACKET &&
         inputStr[strIndex].op == ')')) {
      while (processed.root != NULL &&
             top(&processed)->data.type != TYPE_BRACKET &&
             top(&processed)->data.op !=
                 '(') {
        push(&polishNotation, pop(&processed));
      }
      if (processed.root != NULL) {
        pop(&processed); ++strIndex;
      }
      if (inputStr[strIndex].type == TYPE_FUNCTION) {
        push(&polishNotation, pop(&processed));
        ++strIndex;
      }
    }
  }
  if (strIndex == size) {
    while (processed.stSize > 0) {
      if (top(&processed)->data.type == TYPE_BRACKET &&
          (top(&processed)->data.op == ')' ||
           top(&processed)->data.op == '(')) {
        polishNotation.root->data.type = E_POLISH_NOTATION;
        return polishNotation;
      }
      push(&polishNotation, pop(&processed));
    }
  }

  freeStack(&processed);
  free(inputStr);
  return polishNotation;
}
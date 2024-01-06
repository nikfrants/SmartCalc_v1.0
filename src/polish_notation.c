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
  stNode* temp;
  parseData temp1;
  stack polishNotation;
  stackInit(&polishNotation);
  stack processed;
  stackInit(&processed);
  parseData* inputStr = parser(expression, &size);
  while (strIndex < size) {
    if (inputStr[strIndex].type == TYPE_DIGIT) {
      push(&polishNotation,createNode( inputStr[strIndex]));
      ++strIndex;
    }
    if (strIndex < size && (inputStr[strIndex].type == TYPE_FUNCTION ||
                            inputStr[strIndex].type == TYPE_BRACKET &&
                                inputStr[strIndex].op == '(')) {
      push(&processed,  createNode( inputStr[strIndex]));
      ++strIndex;
    }
    if (strIndex < size && inputStr[strIndex].type == TYPE_OPERATOR) {
      while (processed.stSize &&
             (top(&processed)->data.priority > inputStr[strIndex].priority ||
              top(&processed)->data.priority == inputStr[strIndex].priority &&
                  is_left_associative(inputStr[strIndex].op))) {
        push(&polishNotation, createNode((temp = pop(&processed))->data));
      }
      push(&processed,createNode( inputStr[strIndex]));
      ++strIndex;
    }
    if (strIndex < size &&
        (inputStr[strIndex].type == TYPE_BRACKET &&
         inputStr[strIndex].op == ')')) {
      while (processed.root != NULL &&
             top(&processed)->data.type != TYPE_BRACKET &&
             top(&processed)->data.op !=
                 '(') {
        push(&polishNotation, createNode(pop(&processed)->data));
      }
      if (processed.root != NULL) {
        pop(&processed);++strIndex;
      }
      if (inputStr[strIndex].type == TYPE_FUNCTION) {
        push(&polishNotation, createNode(pop(&processed)->data));
        ++strIndex;
      } // todo describe errors
    }
  }
  if (strIndex == size) {
    while (processed.stSize > 0) {
      if (top(&processed)->data.type == TYPE_BRACKET &&
          (top(&processed)->data.op == ')' ||
           top(&processed)->data.op == '(')) {
        polishNotation.root->data.type = E_POLISH_NOTATION;
        return polishNotation;  // todo describe errors
      } push(&polishNotation, createNode(pop(&processed)->data));

    }
  }

  freeStack(&processed);
  free(inputStr);
  return polishNotation;
}

/*// int get_priority(parseData data) {
//   if (data.type == 3) {
//     if (data.op == '(') return 0;
//     if (data.op == '+' || data.op == '-') return 1;
//     if (data.op == '*' || data.op == '/' || data.op == 'm') return 2;
//     if (data.op == '^') return 3;
//     if (data.op == '~') return 4;
//     return 0;
//   }
//   if (data.type == 4) return 5;
// }

// priority of operators
// 0 1 1 2 2 3 4
// ( + - * / ^ ~
//
// 2 - mod
// 5 - sin cos tan asin acos atan sqrt ln log

/* else if (parsedExpr[i].type == 2)
    //   push(&st, initData(parsedExpr[i].fval, 0, 2));
    // else if (parsedExpr[i].type == 3)
    //   push(&st, initData(0, parsedExpr[i].op, 3));
    // else if (parsedExpr[i].type == 4) {
    //   double operand2 = pop(&st);
    //   double operand1 = pop(&st);
    //   double result = operand1 + operand2;
       push(&st, initData(result, 0, 1));

   else if (expression[i] == '+' || expression[i] == '-' ||
//            expression[i] == '*' || expression[i] == '/') {
//     double operand2 = pop(&st);
//     double operand1 = pop(&st);
//     double result;
//     switch (expression[i]) {
//       case '+':
//         result = operand1 + operand2;
//         break;
//       case '-':
//         result = operand1 - operand2;
//         break;
//       case '*':
//         result = operand1 * operand2;
  //         break;
  //       case '/':
  //         result = operand1 / operand2;
  //         break;
  //     }
  //     push(&st, result);
  //     i++;
  //   }
  // }
  // double finalResult = pop(&stack);
  // return finalResult;




//
// if (parsedExpr[i].type == 3 && parsedExpr[i].op == ')') {
// }
// // Если в стеке не окажется
// // открывающая скобка - в выражении допущена ошибка.
// else if (parsedExpr[i].type == 3 && parsedExpr[i].op == ')') {
//   while (!isEmpty(&processed) && top(&processed)->data.op != '(') {
//     push(&output, pop(&processed));
//   }
//   pop(&processed);
// }*/
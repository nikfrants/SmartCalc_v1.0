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
  while (strIndex < size) {  //==1==//   // Если Число -> в ответ
    if (inputStr[strIndex].type == TYPE_DIGIT) {
      push(&polishNotation,
           inputStr[strIndex]);  // initData(inputStr[strIndex].number, 0, 1,-1)
      ++strIndex;
    }  //==2==// Если Функция или открывающая скобка -> в стек
    if (strIndex < size && (inputStr[strIndex].type == TYPE_FUNCTION ||
                            inputStr[strIndex].type == TYPE_BRACKET &&
                                inputStr[strIndex].op == '(')) {
      push(&processed, inputStr[strIndex]);
      ++strIndex;
    }                                                                  /*
                                                                   //==3==// Разделитель аргументов функции (например, запятая):
                                                                   // Перекладываем операторы из стека в выходную очередь пока лексемой на
                                                                   // вершине стека не станет открывающая скобка. Если в стеке не окажется
                                                                   // открывающей скобки - в выражении допущена ошибка.
                                                                   // todo described above
                                                                   // --------------
                                                                   // else if (parsedExpr[i].type == 3 && parsedExpr[i].op == ',') {
                                                                   //   while (top(&processed)->data.type != 3) {
                                                                   //     push(&output, pop(&processed)->data);
                                                                   //   }
                                                                   // }
                                                                   //----------------
                                                                   // if(inputStr[strIndex].type == TYPE_OPERATOR && inputStr[strIndex].op ==
                                                                   // ',') {
                                                                   //   while(top(&processed)->data.type != TYPE_OPERATOR ||
                                                                   //   top(&processed)->data.op != '(') {
                                                                   //     push(&polishNotation, pop(&processed)->data);
                                                                   //   }
                                                                   //   push(&processed, inputStr[strIndex]);
                                                                   //   ++strIndex;
                                                                   // } Оператор (O1):

                                                                   // Если Оператор (O1):
                                                                   //==4==//*/
    if (strIndex < size && inputStr[strIndex].type == TYPE_OPERATOR) { /*
      //==4.1==// Пока присутствует на вершине стека лексема-оператор (O2)
      //        чей приоритет выше приоритета O1,
      //        либо при равенстве приоритетов O1 является левоассоциативным:*/
      while (processed.stSize &&
             (top(&processed)->data.priority > inputStr[strIndex].priority ||
              top(&processed)->data.priority == inputStr[strIndex].priority &&
                  is_left_associative(inputStr[strIndex].op))) { /*
         //==4.1.1==// Перекладываем O2 из стека в выходную очередь */
        push(&polishNotation, (temp = pop(&processed))->data);
        if (temp)
          free(temp); /*
//  ++strIndex;*/
      }               /*
                     //==4.2==// Помещаем O1 в стек*/
      push(&processed, inputStr[strIndex]);
      ++strIndex;
    } /*
     //==5==// Если Закрывающая скобка:*/
    if (strIndex < size &&
        (inputStr[strIndex].type == TYPE_BRACKET &&
         inputStr[strIndex].op == ')')) { /*
//==5.1==// Пока лексема на вершине стека не станет открывающей скобкой,*/
      while (processed.root != NULL &&
             top(&processed)->data.type != TYPE_BRACKET &&
             top(&processed)->data.op !=
                 '(') { /*
//==5.1==// перекладываем лексемы-операторы из стека в выходную очередь.
// if (top(&processed)->data.type == TYPE_OPERATOR) {*/
        push(&polishNotation, (temp = pop(&processed))->data);
        if (temp != NULL)
          free(temp);             /*
     //    ++strIndex;
     //  }*/
      }                           /*

                                 //==5.2==// Удаляем из стека открывающую скобку.*/
      if (processed.root != NULL) /*// &&
      //     top(&processed)->data.type == TYPE_BRACKET &&
        //   top(&processed)->data.op == '(')*/
      {
        if (temp != NULL) free(temp);
        temp = pop(&processed);
        ++strIndex;
      }                                               /*
                                                     //==5.3==//   Если лексема на вершине стека — функция*/
      if (inputStr[strIndex].type == TYPE_FUNCTION) { /*
         //==5.3==// , перекладываем её в выходную очередь.*/
        push(&polishNotation, (temp = pop(&processed))->data);
        ++strIndex;
      }/*
      //==5.4==// Если стек закончился до того, как была встречена открывающая
      //      скобка - в выражении содержится ошибка
      // if (processed.stSize == 0) {
      //   polishNotation.root->data.type = E_POLISH_NOTATION;
      //   return polishNotation;
      // }*/  // todo describe errors
    }
  }                                /*
                                  //==6==//
                                  // Если во входной строке больше не осталось лексем:*/
  if (strIndex == size) {          /*
              //==6.1==//
              // Пока есть операторы в стеке:*/
    while (processed.stSize > 0) { /*
       //==6.1.1==//
       //   Если на вершине стека скобка - в выражении допущена ошибка.*/
      if (top(&processed)->data.type == TYPE_BRACKET &&
          (top(&processed)->data.op == ')' ||
           top(&processed)->data.op == '(')) {
        polishNotation.root->data.type = E_POLISH_NOTATION;
        return polishNotation;  // todo describe errors
      }                         /*
                               //==6.1.2==//
                               //  Перекладываем оператор из стека в выходную очередь*/
      push(&polishNotation, (temp = pop(&processed))->data);
      if (temp != NULL) free(temp);
      /*
      // ++strIndex;*/
    }
  }
  if (temp != NULL) free(temp);
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
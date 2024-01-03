//
// Created by nikolay on 1/3/24.
//
#include "stack.h"
int is_left_associative(char op) {
  if (op && (op == '^' || op == '~')) return 1;
  return 0;
}
// polish notation implementation on c
stack * evaluatePolishNotation(char* expression) {
  int i = 0;
  int size = 0;
  stack output;
  stackInit(&output);
  stack processed;
  stackInit(&processed);
  parseData* parsedExpr = parser(expression, &i);
  while (i != size) {
    // Если Число - добавляем в строку вывода.
    if (parsedExpr[i].priority == 0)
      push(&output, initData(parsedExpr[i].number, 0, 1));
    // Если Функция или открывающая скобка - помещаем в стек.
    else if (parsedExpr[i].priority == TYPE_FUNCTION ||
             parsedExpr[i].type == TYPE_OPERATOR && parsedExpr[i].op == '(')
      push(&processed, parsedExpr[i]);
    // Разделитель аргументов функции (например, запятая):
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
    // Пока присутствует на вершине стека лексема-оператор (O2) чей приоритет
    // выше приоритета O1, либо при равенстве приоритетов O1 является
    // левоассоциативным:
    // Перекладываем O2 из стека в выходную очередь
    while (top(&processed)->data.priority >= parsedExpr[i].priority ||
           top(&processed)->data.priority == parsedExpr[i].priority &&
               is_left_associative(parsedExpr[i].op)) {
      push(&output, pop(&processed)->data);
    }
    // Помещаем O1 в стек
    push(&processed, parsedExpr[i]);
    // Если Закрывающая скобка:
    // Пока лексема на вершине стека не станет открывающей скобкой,
    // перекладываем лексемы-операторы из стека в выходную очередь.
    if (parsedExpr[i].type == TYPE_OPERATOR && parsedExpr[i].op == ')') {
      while (top(&processed)->data.type != 3 &&
             top(&processed)->data.op != '(') {
        push(&output, pop(&processed)->data);
      }
      pop(&processed);
    }
    // Удаляем из стека открывающую скобку.
    if (parsedExpr[i].type == TYPE_OPERATOR && parsedExpr[i].op == '(') {
      pop(&processed);
    }
    // Если лексема на вершине стека — функция, перекладываем её в выходную
    // очередь.
    while (parsedExpr[i].type == TYPE_FUNCTION) {
      //      Если стек закончился до того, как была встречена открывающая
      //      скобка - в выражении содержится ошибка
      if (processed.stSize == 0) return 1;  // todo describe errors
      push(&output, pop(&processed)->data);
      if (processed.root->data.type == TYPE_OPERATOR &&
          processed.root->data.op == ')')
        break;
    }
  //Если во входной строке больше не осталось лексем:
    if(i != size) {
      //Пока есть операторы в стеке:
      //  Если на вершине стека скобка - в выражении допущена ошибка.
      if (top(&processed)->data.type == TYPE_OPERATOR &&(
        top(&processed)->data.op == ')' || top(&processed)->data.op == '(')) return 1;
      //  Перекладываем оператор из стека в выходную очередь
      push(&output, pop(&processed)->data);
    }
  }
  return &output;
}

// int get_priority(parseData data) {
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
       push(&st, initData(result, 0, 1));*/

/*   else if (expression[i] == '+' || expression[i] == '-' ||
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
  // return finalResult; */




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
// }
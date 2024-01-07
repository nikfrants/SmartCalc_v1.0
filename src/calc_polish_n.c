//
// Created by nikolay on 1/5/24.
//
#include "stack.h"

const char *errortexts[] = {
    "No errors",                                                     // 0
    "Stack overflow",                                                // 1
    "Stack underflow",                                               // 2
    "Division by zero",                                              // 3
    "Encountered zero inside tangent function",                      // 4
    "Negative argument inside natural logarithm function",           // 5
    "Negative argument inside base 10 logarithm function",           // 6
    "Negative argument inside square root function",                 // 7
    "Value not in the domain of arccosine function",                 // 8
    "Value not in the domain of arcsine function",                   // 9
    "Encountered unknown or unsupported operation",                  // 10
    "Incorrect polish notation",                                     // 11
    "Expected operation but got digit while processing expression",  // 12
    "Function does not exist",                                       // 13
    "Error during conversion to Polish notation",                    // 14
    "Expression is incorrect",                                       // 15
    "Two operators near each other",                                 // 16
    "Two functions near each other",                                 // 17
    "Incorrect brackets sequence",                                   // 18
    "Two multiples near each other",                                 // 19
    "Two powers near each other",                                    // 20
    "Two divisions near each other",                                 // 21
    "Two mod near each other",                                       // 22
    "Two dots near each other",                                      // 23
    "Mod has one numbers",                                           // 24
    "No digits in str",                                              // 25
    "No digits near dot",                                            // 26
    "Only digits in str"                                             // 27
};

calc_s calcDigits(parseData *data, calc_s a, calc_s b);

calc_s new_calc_s(long double n, int err) {
  calc_s calc;
  calc.n = n;
  calc.e = err;
  return calc;
}

calc_s calcPolishNotation(stack *data) {
  struct variables varsArray[100] = {0};
  int arrsize = 0;
  variables* arr;
  arr = searchVariable(data, varsArray, &arrsize);
  if (arrsize >= 0) {
    arr = askVariables(arr, arrsize);
    fillvariables(data, arr, arrsize);
  }
  stack ans;
  calc_s calc;
  stackInit(&ans);
  parseData a, b, op;
  // long double calc = NAN;
  while (top(data)) {
    if (data->root->data.type == TYPE_DIGIT ||
        data->root->data.type == TYPE_VARIABLE) {
      if (data->root->data.type == TYPE_VARIABLE) {
        parseData temp = pop(data);
        //  temp.number = get_variable(temp.varName);
        temp.type = TYPE_DIGIT;
        temp.priority = -1;
        push(&ans, temp);
      } else
        push(&ans, pop(data));
    } else {
      b = pop(&ans);
      op = pop(data);
      if (op.op != '\000' && strchr("+-*/^m", op.op))
        a = pop(&ans);
      else
        a = initData(NAN, 0, 0, 0);
      if (a.type == E_STACK_UNDERFLOW)
        return new_calc_s(NAN, E_INCORRECT_POLISH_NOTATION);

      calc = calcDigits(&op, new_calc_s(a.number, 0), new_calc_s(b.number, 0));

      if (isnan(calc.n)) return calc;
      if (calc.n > -ROUND && calc.n < ROUND) calc.n = 0;
      push(&ans, initData(calc.n, op.op, TYPE_DIGIT, 0));
    }
  }

  const calc_s answer = new_calc_s(top(&ans)->data.number, 0);
  freeStack(&ans);
  return answer;
}

// Todo DONE      multiple variables
// Todo           multiple repeated variables
// void searchVariable(stack *st, variables array[], int index) {
//   stNode *temp = st->last;
//   int stackindex = 0;
//   int arrindex = 0;
//   while ((size_t)stackindex < st->stSize) {
//     if (temp->data.type == TYPE_VARIABLE) {
//       stNode *searchvar = temp;
//       strcpy( array[arrindex].name, temp->data.varName);
//       if (strcmp(array[arrindex].name, temp->data.varName) == 0) {
//         int adrressindex = 0;
//         while (searchvar->prev != NULL) {
//           if (strcmp(array[arrindex].name, searchvar->data.varName) == 0) {
//             array[arrindex].adress[adrressindex] = &temp->data.number;
//             adrressindex++;
//           }
//         }
//       }
//     }
//
//     temp = temp->prev;
//     ++stackindex;
//   }
// }
// void askVariables(variables array[][], int size) {
//   for (int i = 0; i < size; ++i) {
//     long double var = get_variable(array[i][0].name);
//
//     strcpy(array[i][0].name, "");
//   }
// }
// void fillvariables(stack *st, variables *array, int size) {
//   stNode *temp = st->last;
//   for (int i = 0; i < size; ++i) {
//     for (int j = 0; array(i * j) > 0; ++j) {
//       *array(i * j).adress = array->value;
//     }
//   }
// }
// variables getListVariables(stack *st, variables array[][], int *size) {
//   stNode *temp = st->last;
//   int i = 0;
//   *size = 0;
//   while ((size_t)i < st->stSize) {
//     if (temp->data.type == TYPE_VARIABLE) {
//       strcpy(array[*size][].name, temp->data.varName);
//       ++*size;
//     }
//     temp = temp->prev;
//     ++i;
//   }
//   return array;
// }

int var_in_array(variables array[], char *name) {
  for (int i = 0; i < 100; ++i) {
    if (strcmp(array[i].name, name) == 0) {
      return 1;
    }
  }
  return 0;
}
variables*  askVariables(variables array[], int size) {
  for (int i = 0; i <= size; ++i) {
    long double var = get_variable(array[i].name);
    for (int j = 0; array[i].adress[j] != 0; ++j) {
      array[i].value = var;
    }
  }
  return array;
}

void fillvariables(stack *st, variables array[], int size) {
  for (int i = 0; i <= size; ++i) {
    for (int j = 0; array[i].adress[j] != 0; ++j) {
      *array[i].adress[j] = array[i].value;
    }
  }
}

variables* searchVariable(stack *st, variables array[],int *arrayindex) {
  /*
  search in stack new variable name
      if name not in variable arrays
        add it and
        search in stack this variable adress by name
        if matched
           add it to array.adress[i]
  */
  stNode *temp = st->root;
   *arrayindex = -1;
  int addressidx = 0;
  while (temp != NULL) {
    if (temp->data.type == TYPE_VARIABLE) {
      if (!var_in_array(array, temp->data.varName)) {
        ++*arrayindex;
        stNode *searchvar = temp;
        strcpy(array[*arrayindex].name, temp->data.varName);
        addressidx = 0;
        while (searchvar != NULL) {
          if (searchvar->data.type == TYPE_VARIABLE &&
              strcmp(array[*arrayindex].name, searchvar->data.varName) == 0) {
            array[*arrayindex].adress[addressidx] = &searchvar->data.number;
            ++addressidx;
          }
        searchvar = searchvar->next;
      }
    }
  }

  temp = temp->next;
}
return array;
}

long double get_variable(char *name) {
  long double var;
  printf("input variable %s = ", name);
  scanf("%Lf", &var);
  return var;
}
calc_s calcDigits(parseData *data, calc_s a, calc_s b) {
  calc_s ans;
  if (data->type == TYPE_OPERATOR) return calcDigitsOp(data, a, b);
  if (data->type == TYPE_FUNCTION) return calcDigitsFunc(data, a, b);
  return new_calc_s(NAN, E_EXPECTED_OPERATION_GOT_DIGIT);
}
calc_s calcDigitsOp(parseData *data, calc_s a, calc_s b) {
  calc_s ans;
  if (data->op == '+') return new_calc_s(a.n + b.n, 0);
  if (data->op == '-') return new_calc_s(a.n - b.n, 0);
  if (data->op == '*') return new_calc_s(a.n * b.n, 0);
  if (data->op == '/')
    return b.n != 0 ? new_calc_s(a.n / b.n, 0) : new_calc_s(NAN, E_DIV_BY_ZERO);
  if (data->op == '^') return new_calc_s(powl(a.n, b.n), 0);
  if (data->op == 'm')
    return b.n != 0 ? new_calc_s(fmodl(a.n, b.n), 0)
                    : new_calc_s(NAN, E_DIV_BY_ZERO);
  if (data->op == '~') return new_calc_s(-b.n, 0);
  if (data->op == 'p') return new_calc_s(+b.n, 0);
  return new_calc_s(NAN, E_UNEXIST_OPERATION);
}
calc_s calcDigitsFunc(parseData *data, calc_s a, calc_s b) {
  calc_s ans;

  if (strncmp(data->func, "cos", 3) == 0) {
    return new_calc_s(cosl(b.n), 0);
  } else if (strncmp(data->func, "sin", 3) == 0) {
    return new_calc_s(sinl(b.n), 0);
  } else if (strncmp(data->func, "asin", 4) == 0) {
    return fabsl(b.n) <= 1 ? new_calc_s(asinl(b.n), 0)
                           : new_calc_s(NAN, E_NOT_IN_SCOPE_ASIN);
  } else if (strncmp(data->func, "acos", 4) == 0) {
    return fabsl(b.n) <= 1 ? new_calc_s(acosl(b.n), 0)
                           : new_calc_s(NAN, E_NOT_IN_SCOPE_ACOS);
  } else if (strncmp(data->func, "tan", 3) == 0) {
    return cosl(b.n) != 0 ? new_calc_s(tanl(b.n), 0)
                          : new_calc_s(NAN, E_DIV_BY_ZERO);
  } else if (strncmp(data->func, "ln", 2) == 0) {
    return b.n >= 0 ? new_calc_s(logl(b.n), 0) : new_calc_s(NAN, E_NERATIVE_LN);
  } else if (strncmp(data->func, "log", 3) == 0) {
    return b.n >= 0 ? new_calc_s(log10l(b.n), 0)
                    : new_calc_s(NAN, E_NERATIVE_LOG10);
  } else if (strncmp(data->func, "sqrt", 4) == 0) {
    return b.n >= 0 ? new_calc_s(sqrtl(b.n), 0)
                    : new_calc_s(NAN, E_NERATIVE_SQRT);
  }
  // } else if (strncmp(data->func, "exp", 3) == 0) {
  //   return expl(b);
  return new_calc_s(NAN, E_UNEXIST_FUNCTION);
}
char *errorDescription(int error) {
  int code = -error - 100;
  return errortexts[code];
}
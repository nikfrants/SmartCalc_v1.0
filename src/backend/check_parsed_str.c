//
// Created by nikolay on 1/6/24.
//

#include "stack.h"


int check(parseData* data, int size, char* str) {
  if (data[0].type == E_INCORRECT_EXPRESSION) {
    return E_INCORRECT_EXPRESSION;
  }
  int error = E_NO_ERRORS;
  error = check_brackets(data, size);
  if (error != E_NO_ERRORS) return error;
  error = check_operations(data, size);
  if (error != E_NO_ERRORS) return error;
  error = check_digits_near_dot(str);
  if (error != E_NO_ERRORS) return error;
  error = check_digits_in_str(str);
  if (error != E_NO_ERRORS) return error;
  return error;
}

int check_brackets(parseData* data, int size) {
  int balance = 0;
  for (int idx = 0; idx < size; ++idx) {
    if (data[idx].type == TYPE_BRACKET && data[idx].op == '(') {
      balance++;
    } else if (data[idx].type == TYPE_BRACKET && data[idx].op == ')') {
      balance--;
    }
    if (balance < 0) return E_INCORRECT_BRACKETS_SEQUENE;
  }
  if (balance != 0) return E_INCORRECT_BRACKETS_SEQUENE;
  return E_NO_ERRORS;
}

int check_operations(parseData* data, int size) {
  if ((data[size - 1].type == TYPE_OPERATOR || data[0].type == TYPE_OPERATOR) &&
      data[size - 1].op == 'm')
    return E_MOD_HAS_ONE_NUMBERS;
  for (int idx = 0; idx < size; ++idx) {
    if (data[idx].type == TYPE_OPERATOR &&
        data[idx + 1].type == TYPE_OPERATOR) {
      if (data[idx].op == '*' && data[idx + 1].op == '*')
        return E_TWO_MULTIPLES_NEARBODY;
      if (data[idx].op == '^' && data[idx + 1].op == '^')
        return E_TWO_POW_NEARBODY;
      if (data[idx].op == '/' && data[idx + 1].op == '/')
        return E_TWO_DIVISION_NEARBODY;
      if (data[idx].op == 'm' && data[idx + 1].op == 'm')
        return E_TWO_MOD_NEARBODY;
      if( data[idx].op == '+' &&data[idx+1].op == 'm' )
        return E_MOD_HAS_ONE_NUMBERS;
    }  // return E_TWO_OPERATORS_NEARBODY;
    if (data[idx].type == TYPE_FUNCTION &&
        data[idx + 1].type == TYPE_FUNCTION) {
      return E_TWO_FUNCTIONS_NEARBODY;
    }
  }
  return E_NO_ERRORS;
}
int check_digits_near_dot(char* str) {
  char* str1 = str;
  while (*(str1 + 1)) {
    if (*str1 == '.' && *(str1 + 1) == '.') return E_TWO_DOT_NEARBODY;
    str1++;
  }
  str++;
  while (*(str + 1)) {
    if (*str == '.' && ((*(str - 1) < '0' || *(str - 1) > '9') ||
                        (*(str + 1) < '0' || *(str + 1) > '9')))
      return E_NO_DIGITS_NEAR_DOT;
    str++;
  }
  return E_NO_ERRORS;
}
int check_digits_in_str(char* str) {
  int flag_numbers_exist = 0;
  int flag_operators_exist = 0;
  int flag_funcs_exist = 0;
  char* str1 = str;
  while (*str1) {
    if ((*str1 >= '0' && *str1 <= '9') || (*str1 >= 'a' && *str1 <= 'z') ||
        (*str1 >= 'A' && *str1 <= 'Z')) {
      flag_numbers_exist = 1;
      break;
    }
    str1++;
  }
  str1 = str;
  while (*str1) {
    if (strchr("+p~-*/^", *str1) != NULL) {
      flag_operators_exist = 1;
      break;
    }
    str1++;
  }
  str1 = str;
  char* strfuncs[] = {"sin",  "cos",  "tan", "asin", "acos",
                      "atan", "sqrt", "ln",  "log",  "mod"};

  for (int i = 0; i < (int)(sizeof(strfuncs)/sizeof(strfuncs[0])); i++) {
    if (strstr(str1, strfuncs[i]) != NULL) {
      flag_funcs_exist = 1;
      break; // Если функция найдена, выходим из цикла
    }
  }
  if (!flag_numbers_exist) return E_NO_DIGITS_IN_STR;
  if (!flag_operators_exist && !flag_funcs_exist) return E_ONLY_DIGITS_EXIST;
  return E_NO_ERRORS;
}

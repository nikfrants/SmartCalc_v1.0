//
// Created by nikolay on 1/1/24.
//

// parse string
// and return array of separeted elements

#include "stack.h"

int isDigit(char* ch, parseData* currstr, int* parseidx,
            int* stringParseindex) {
  if (*ch == '\000') {
    return 0;
  }
  currstr[*parseidx].lenth = 0;
  if ((*ch >= '0' && *ch <= '9') || *ch == '.') {
    char string[300] = {'\0'};
    int idx1 = 0;
    while ((*ch >= '0' && *ch <= '9') || *ch == '.') {
      string[idx1] = *ch;
      ch++;
      currstr[*parseidx].lenth++;
      idx1++;
    }
    string[idx1] = '\0';
    currstr[*parseidx].number = atoll(string);
    currstr[*parseidx].type = 1;
    currstr[*parseidx].priority =
        -1;  // 0 //todo change to 0. shift numericto right
    *stringParseindex += currstr[*parseidx].lenth;
    ++*parseidx;
    return 1;
  }
  return 0;
}
int isFunction(char* ch, parseData* currstr, int* parseidx,
               int* stringParseindex) {
  if (*ch == '\000') {
    return 0;
  }
  currstr[*parseidx].lenth = 0;
  if (*ch == 'c' || *ch == 's' || *ch == 't' || *ch == 'a' || *ch == 'l') {
    if (*ch == 'c') {
      strcpy(currstr[*parseidx].func, "cos");
      currstr[*parseidx].lenth = 3;
      ch += 3;
    } else if (*ch == 't') {
      strcpy(currstr[*parseidx].func, "tan");
      currstr[*parseidx].lenth = 3;
      ch += 3;
    } else if (*(ch + 1) == 'i') {
      strcpy(currstr[*parseidx].func, "sin");
      currstr[*parseidx].lenth = 3;
      ch = ch + 3;
      //   ch += 3;
    } else if (*(ch + 1) == 'c') {
      strcpy(currstr[*parseidx].func, "acos");
      currstr[*parseidx].lenth = 4;
      ch += 4;
    } else if (*(ch + 1) == 's') {
      strcpy(currstr[*parseidx].func, "asin");
      currstr[*parseidx].lenth = 4;
      ch += 4;
    } else if (*(ch + 1) == 't') {
      strcpy(currstr[*parseidx].func, "atan");
      currstr[*parseidx].lenth = 4;
      ch += 4;
    } else if (*(ch + 1) == 'q') {
      strcpy(currstr[*parseidx].func, "sqrt");
      currstr[*parseidx].lenth = 4;
      ch += 4;
    } else if (*(ch + 1) == 'n') {
      strcpy(currstr[*parseidx].func, "ln");
      currstr[*parseidx].lenth = 2;
      ch += 2;
    } else if (*ch == 'l' && *(ch + 1) == 'o') {
      strcpy(currstr[*parseidx].func, "log");
      currstr[*parseidx].lenth = 3;
      ch += 3;
    }
    currstr[*parseidx].priority = 5;
    *stringParseindex += currstr[*parseidx].lenth;
    ++*parseidx;
    return 1;
  }
  return 0;
}
int isOperator(char* ch, parseData* currstr, int* parseidx,
               int* stringParseindex) {
  if (*ch == '\000') {
    return 0;
  }
  currstr[*parseidx].lenth = 0;
  if (*ch == '+' || *ch == '-' || *ch == '*' || *ch == '/' || *ch == '^' ||
      *ch == '~' || *ch == 'm' || *ch == '(' || *ch == ')') {
    int increaseIfMod = 0;
    if (*ch == 'm') increaseIfMod = 2;
    currstr[*parseidx].op = *ch;
    currstr[*parseidx].type = 3;
    switch (*ch) {
      case '(':
        currstr[*parseidx].priority = 0;
        break;
      case '+':
      case '-':
        currstr[*parseidx].priority = 1;
        break;
      case '/':
      case '*':
        currstr[*parseidx].priority = 2;
        break;
      case '^':
        currstr[*parseidx].priority = 3;
        break;
      case '~':
        currstr[*parseidx].priority = 4;
        break;
      case 'm':
        currstr[*parseidx].priority = 2;
        break;
      default:
        currstr[*parseidx].priority = -2; // error?
    }
    ch = ch + 1 + increaseIfMod;
    currstr[*parseidx].lenth += 1 + increaseIfMod;
    *stringParseindex += currstr[*parseidx].lenth;
    ++*parseidx;
    return 1;
  }
  return 0;
}
parseData* parser(char* str, int* stringParseindex) {
  *stringParseindex = 0;
  parseData* data = malloc(100 * sizeof(parseData));
  int parseidx = 0;
  while ((long unsigned int)*stringParseindex < strlen(str)) {
    isDigit((str + *stringParseindex), data, &parseidx, stringParseindex);
    isOperator((str + *stringParseindex), data, &parseidx, stringParseindex);
    isFunction((str + *stringParseindex), data, &parseidx, stringParseindex);
  }
  return data;
}

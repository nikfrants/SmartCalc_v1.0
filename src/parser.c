//
// Created by nikolay on 1/1/24.
//

// parse string
// and return array of separeted elements

#include <math.h>

#include "stack.h"

long double atold(char m[]) {
  int i = 0;
  long double number = 0.0;
  int sign = 1;

  if (m[i] == '-') {
    sign = -1;
    i++;
  }

  for (; m[i] != '.'; i++) {
    number = number * 10 + (m[i] - '0');
  }

  long double fraction = 1.0l;
  for (i = i + 1; m[i] != '\0'; i++) {
    fraction /= 10;
    number = number + (m[i] - '0') * fraction;
  }

  return sign * number;
}

int isDigit(char* ch, parseData* currstr, int* parseidx,
            int* stringParseindex) {
  if (*ch == '\000') {
    return 0;
  }
  currstr[0].lenth = 0;
  if ((*ch >= '0' && *ch <= '9') || *ch == '.') {
    char string[300] = {'\0'};
    int flagfloat = 0;
    int idx1 = 0;

    while ((*ch >= '0' && *ch <= '9') || *ch == '.') {
      if (*ch == '.') flagfloat = 1;
      string[idx1] = *ch;
      ch++;
      currstr[0].lenth++;
      idx1++;
    }
    string[idx1] = '\0';
    if (flagfloat)
      currstr[0].number = atold(string);
    else
      currstr[0].number = atoll(string);
    currstr[0].type = 1;
    currstr[0].priority = -1;
    // 0 //todo change to 0. shift numericto right
    *stringParseindex += currstr[0].lenth;
    ++*parseidx;
    return 0;
  }
  return 1;
}
int isFunction(char* ch, parseData* currstr, int* parseidx,
               int* stringParseindex) {
  if (*ch == '\000') {
    return 0;
  }
  currstr[0].lenth = 0;
  if (*ch == 'c' || *ch == 's' || *ch == 't' || *ch == 'a' || *ch == 'l') {
    if (*ch == 'c') {
      strcpy(currstr[0].func, "cos");
      currstr[0].lenth = 3;
      ch += 3;
    } else if (*ch == 't') {
      strcpy(currstr[0].func, "tan");
      currstr[0].lenth = 3;
      ch += 3;
    } else if (*(ch + 1) == 'i') {
      strcpy(currstr[0].func, "sin");
      currstr[0].lenth = 3;
      ch = ch + 3;
      //   ch += 3;
    } else if (*(ch + 1) == 'c') {
      strcpy(currstr[0].func, "acos");
      currstr[0].lenth = 4;
      ch += 4;
    } else if (*(ch + 1) == 's') {
      strcpy(currstr[0].func, "asin");
      currstr[0].lenth = 4;
      ch += 4;
    } else if (*(ch + 1) == 't') {
      strcpy(currstr[0].func, "atan");
      currstr[0].lenth = 4;
      ch += 4;
    } else if (*(ch + 1) == 'q') {
      strcpy(currstr[0].func, "sqrt");
      currstr[0].lenth = 4;
      ch += 4;
    } else if (*ch == 'l' && *(ch + 1) == 'n') {
      strcpy(currstr[0].func, "ln");
      currstr[0].lenth = 2;
      ch += 2;
    } else if (*ch == 'l' && *(ch + 1) == 'o') {
      strcpy(currstr[0].func, "log");
      currstr[0].lenth = 3;
      ch += 3;
    }
    currstr[0].priority = 5;
    currstr[0].type = 4;
    *stringParseindex += currstr[0].lenth;
    ++*parseidx;
    return 0;
  }
  return 1;
}
int isOperator(char* ch, parseData* currstr, int* parseidx,
               int* stringParseindex) {
  if (*ch == '\000') {
    return 0;
  }
  currstr[0].lenth = 0;
  if (*ch == '+' || *ch == '-' || *ch == '*' || *ch == '/' || *ch == '^' ||
      *ch == '~' || *ch == 'm' || *ch == '(' || *ch == ')') {
    int increaseIfMod = 0;
    if (*ch == 'm') increaseIfMod = 2;
    currstr[0].op = *ch;
    currstr[0].type = 3;
    switch (*ch) {
      case '(':
        currstr[0].priority = 0;
        break;
      case '+':
      case '-':
        currstr[0].priority = 1;
        break;
      case '/':
      case '*':
        currstr[0].priority = 2;
        break;
      case '^':
        currstr[0].priority = 3;
        break;
      case '~':
        currstr[0].priority = 4;
        break;
      case 'm':
        currstr[0].priority = 2;
        break;
      default:
        currstr[0].priority = -2;  // error?
    }
    ch = ch + 1 + increaseIfMod;
    currstr[0].lenth += 1 + increaseIfMod;
    *stringParseindex += currstr[0].lenth;
    ++*parseidx;
    return 0;
  }
  return 1;
}
int Other(char* ch, parseData* currstr, int* parseidx, int* stringParseindex) {
  if (*ch == '\000') {
    return 0;
  }
  if (*ch == ' ') {
    ++*stringParseindex;
    return 0;
  }
  if (*ch == 'e') {
    currstr[0].type = 1;
    currstr[0].number = M_E;
    *stringParseindex += 1;
    ++*parseidx;
    return 0;
  }
  if (*ch == 'p' && *(ch + 1) == 'i') {
    currstr[0].type = 1;
    currstr[0].number = M_PI;
    *stringParseindex += 2;
    ++*parseidx;
    return 0;
  }
  if (*ch > 'a' && *ch < 'z' || *ch > 'A' && *ch < 'Z') {
    int index = 0;
    for (; index < 5 && (*(ch + index) >= 'a' && *(ch + index) <= 'z' ||
                         *(ch + index) >= 'A' && *(ch + index) <= 'Z');
         ++index)
      currstr->varName[index] = *(ch + index);

    currstr[0].type = 5;
    currstr[0].number = 0;
    currstr[0].lenth = index;
    *stringParseindex += currstr[0].lenth;
    ++*parseidx;
    return 0;
  }
  // todo
  //   else incorrect expression  error
  return 1;
}
parseData* parser(char* str, int* strPrsidx) {
  *strPrsidx = 0;
  parseData* data = malloc(100 * sizeof(parseData));
  int prseidx = 0;
  while ((long unsigned int)*strPrsidx < strlen(str)) {
    int other = 0;
    other += isDigit(str + *strPrsidx, data + prseidx, &prseidx, strPrsidx);
    other += isOperator(str + *strPrsidx, data + prseidx, &prseidx, strPrsidx);
    other += isFunction(str + *strPrsidx, data + prseidx, &prseidx, strPrsidx);
    if (other == 3)
      Other(str + *strPrsidx, data + prseidx, &prseidx, strPrsidx);
  }
  return data;
}

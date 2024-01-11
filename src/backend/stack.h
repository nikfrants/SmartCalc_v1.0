//
// Created by nikolay on 1/1/24.
//

#ifndef SMART_CALC_H
#define SMART_CALC_H

#endif  // SMART_CALC_H

// constants
#define E 2.71828182845904523536
#define PI 3.141592653589793238462643383279
#define REALLOC_SIZE 10
// #define STACK_MAX_SIZE 1000
#define ROUND 1.0e-35 // e.g. 4e-15 - variable near 0 with ( 4/10^15 ) will be implemented as zero
// errors
#define E_NO_ERRORS -100
//      stack
#define E_STACK_OWERFLOW -101
#define E_STACK_UNDERFLOW -102

// #define E_STACK_UNDERFLOW_DATA initData(0,0,STACK_UNDERFLOW,-10)
//      calculate polish notation
#define E_DIV_BY_ZERO -103
#define E_ZERO_IN_TAN -104
#define E_NERATIVE_LN -105
#define E_NERATIVE_LOG10 -106
#define E_NERATIVE_SQRT -107
#define E_NOT_IN_SCOPE_ACOS -108
#define E_NOT_IN_SCOPE_ASIN -109
#define E_UNEXIST_OPERATION -110
#define E_INCORRECT_POLISH_NOTATION -111
#define E_EXPECTED_OPERATION_GOT_DIGIT -112
#define E_UNEXIST_FUNCTION -113
//      infix to polish notation
#define E_POLISH_NOTATION -114
//      parser errors
#define E_INCORRECT_EXPRESSION -115
//      check parsed str
#define E_TWO_OPERATORS_NEARBODY -116
#define E_TWO_FUNCTIONS_NEARBODY -117
#define E_INCORRECT_BRACKETS_SEQUENE -118
#define E_TWO_MULTIPLES_NEARBODY -119
#define E_TWO_POW_NEARBODY -120
#define E_TWO_DIVISION_NEARBODY -121
#define E_TWO_MOD_NEARBODY -122

#define E_TWO_DOT_NEARBODY -123
#define E_MOD_HAS_ONE_NUMBERS -124
#define E_NO_DIGITS_IN_STR -125
#define E_NO_DIGITS_NEAR_DOT -126

#define E_ONLY_DIGITS_EXIST -127
#define E_INCORRECT_VARIABLES -128
// data types
#define TYPE_DIGIT 1
#define TYPE_FUNCTION 4
#define TYPE_OPERATOR 3
#define TYPE_BRACKET 2
#define TYPE_VARIABLE 5




#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//   // 1 2 2 3 3 4 5
//   // 0 1 1 2 2 3 4
//   // ( + - * / ^ ~
//   //
//   // 2 - mod - 3
//   // 5 - sin cos tan asin acos atan sqrt ln log - 6

typedef struct calc_s {
  long double n;
  int e;
} calc_s;
typedef struct variables {
  char name[5];
  long double value;
  long double *adress[10];
  int adresscount;
} variables;

typedef struct parseData {
  long double number;  // type 1
  char op;             // type 3 operator
  int type;

  char func[5];     // type 4 func
  char varName[5];  // type 5 variable
  int lenth;
  int priority;
} parseData;

typedef struct stNode {
  parseData data;
  struct stNode *next;
  struct stNode *prev;
} stNode;

typedef struct {
  stNode *root;
  stNode *last;
  size_t stSize;
  // size_t variables[1000];
  //  int variablesSize;
  //  write  in variables[]  adresses of variables that stored in parsered
  // array. impossible for now cos stack doesn't exist while we processing
  // parsing
} stack;
int push(stack *st, parseData data);
parseData pop(stack *st);
stNode *top(const stack *st);
int isEmpty(stack *st);
void stackInit(stack *st);
stNode *createNode(parseData data);
void initNode(stNode *node, parseData val);
parseData initData(long double val, char symbol, int type, int priority);
void freeStack(stack *st);
void print(char *string);
void stackPrintValue(parseData value, int useName);
int stackPrintByIndex(const stack *st, int index);
void stackPrintAll(const stack *st);
stack evaluatePolishNotation(char *expression);
parseData *parser(char *str, int *idx);
calc_s calcPolishNotation(stack *data) ;
void printParsedData(parseData *data, int size);
calc_s calcDigits(parseData *data, calc_s a, calc_s b);
calc_s new_calc_s(long double n, int err);
char *errorDescription(int error);
int check_brackets(parseData *data, int size);
int check_operations(parseData *data, int size);
calc_s calcDigitsOp(parseData *data, calc_s a, calc_s b);
calc_s calcDigitsFunc(parseData *data, calc_s b);
int check_digits_in_str(char *str);
int check_digits_near_dot(char *str);
long double get_variable(char* name);
void fillvariables(stack *st, variables *array[], int size) ;
variables*  askVariables(variables array[], int size);
int var_in_array(variables array[], char *name);
variables* searchVariable(stack *st, variables array[],int *arrayindex);
int check(parseData* data, int size, char* str);
char *notationToString(char s[], char *str );
calc_s calculate(char s[], variables vars_In_Notatation[]) ;
char * getPolish(char s[],char polish[]);
variables * getVariablesParsed( char s[],variables vars_In_Notatation[],int *size) ;
int containsVariables(parseData* data, int size);
char *parsedToString(char *str, parseData *data,int size);

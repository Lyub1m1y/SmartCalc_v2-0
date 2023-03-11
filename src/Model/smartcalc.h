#ifndef SMARTCALC_H_
#define SMARTCALC_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef OK
#define OK 0
#endif

#ifndef FAIL
#define FAIL 1
#endif

typedef enum type_t {
  NUMBER = 1,
  PLUS,
  MINUS,
  MUL,
  DIV,
  POW,
  MOD,
  OPENBRACKET,
  CLOSEBRACKET,
  LN,
  SQRT,
  SIN,
  COS,
  TAN,
  LOG,
  ASIN,
  ACOS,
  ATAN,
  UNPLUS,
  UNMINUS,
  DOT
} type_t;

/* priority
 0 - |'0-9'|, |'.'|,'('|, |')'|;
 1 - |'+'|, |'-'|;
 1 - |'*'|, |'/'|, |"mod"|;
 3 - |'^'|;
 4 - |'sin'|, |'cos'|, ...;
 */

// stack preEntity
typedef struct stack_tt {
  double value;
  int priority;
  type_t type;
  struct stack_tt* next;
} stack_tt;

int entryPoint(char* text, double* double_result, double x_value);
int validator(char* text);
void parser(char* text, stack_tt** reverseTokens, double x_value);
void reversePolishNotation(stack_tt* stack, stack_tt** numStack);
void calculate(stack_tt** stack);
int isNumber(char* str);
int isDot(char* dot);
int isSign(char* text, int* i, int* dotCount);
int isOper(char symb);
void chToTZ(char* text, int length, int need);
void setCloseBracket(char* text, stack_tt** input, int* flagPow,
                     int flagOpenBracket);
int checkCorrectOperator(char* text, int* i);
int checkRatioBrackets(char* text, int text_length);
int checkSupport(stack_tt* helpStack, int priority);
int funcsParentheses(char* text, int* i, int sum);
void calcLexems(stack_tt** stack, stack_tt* tmp_1, stack_tt* tmp_2,
                stack_tt* tmp_3);
void calcFuncs(stack_tt** stack, stack_tt* tmp_2, stack_tt* tmp_3);

// stack funcs
void stack_push_(double value, int priority, type_t type, stack_tt** stack);
void stack_pop_(stack_tt** last);
void stack_reverse_(stack_tt** stack, stack_tt** reverse_stack);
type_t stack_peekType_(stack_tt* list);
void delStack(stack_tt** result, stack_tt* tmp);
stack_tt* stack_free_(stack_tt* list);

#endif  // SMARTCALC_H_

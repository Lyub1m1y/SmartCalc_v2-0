#include "smartcalc.h"

int entryPoint(char* text, double* double_result, double x_value) {
  int status = OK;
  if (validator(text) == OK) {
    stack_tt* reverseTokens = NULL;
    parser(text, &reverseTokens, x_value);
    stack_tt* tokens = NULL;
    stack_reverse_(&tokens, &reverseTokens);

    stack_tt* reverseOutput = NULL;
    reversePolishNotation(tokens, &reverseOutput);
    stack_tt* output = NULL;
    stack_reverse_(&output, &reverseOutput);

    calculate(&output);
    *double_result = output->value;

    stack_free_(reverseTokens);
    stack_free_(tokens);
    stack_free_(reverseOutput);
    stack_free_(output);
  } else {
    status = FAIL;
  }
  return status;
}

int validator(char* text) {
  int status = OK;
  int text_length = strlen(text);
  if (checkRatioBrackets(text, text_length) == OK) {
    int dotCount = 0;
    for (int i = 0; i < text_length && status != FAIL; i++) {
      if (isdigit(text[i]) == 0) {
        if (isSign(text, &i, &dotCount) == FAIL) {
          if (funcsParentheses(text, &i, 0) == FAIL) {
            status = FAIL;
          }
        }
      }
      if (dotCount == 2) {
        status = FAIL;
      }
    }
  } else {
    status = FAIL;
  }
  return status;
}

void parser(char* text, stack_tt** reverseTokens, double x_value) {
  int text_length = strlen(text);
  int flagPow = 0;
  int flagOpenBracket = 0;
  for (int i = 0; i < text_length; i++) {
    if (isdigit(text[i]) != 0) {
      char number[255] = {0};
      double value = 0.0;
      int j = 0;
      while ((isdigit(text[i]) != 0) || (isDot(&text[i]) == OK)) {
        number[j] = text[i];
        j++;
        i++;
      }
      i--;
      sscanf(number, "%lf", &value);
      stack_push_(value, 0, NUMBER, reverseTokens);
      setCloseBracket(&text[i], reverseTokens, &flagPow, flagOpenBracket);
    } else if (text[i] == 'x') {
      stack_push_(x_value, 0, NUMBER, reverseTokens);
      setCloseBracket(&text[i], reverseTokens, &flagPow, flagOpenBracket);
    } else if (text[i] == '(') {
      stack_push_(0, 0, OPENBRACKET, reverseTokens);
      if (flagPow != 0) {
        flagOpenBracket++;
      }
    } else if (text[i] == ')') {
      stack_push_(0, 0, CLOSEBRACKET, reverseTokens);
      if (flagOpenBracket > 0) {
        flagOpenBracket--;
      }
      while (flagPow > 0) {
        stack_push_(0, 0, CLOSEBRACKET, reverseTokens);
        flagPow--;
      }
    } else if (text[i] == '*') {
      stack_push_(0, 2, MUL, reverseTokens);
    } else if (text[i] == '/') {
      stack_push_(0, 2, DIV, reverseTokens);
    } else if (text[i] == 'm') {
      stack_push_(0, 2, MOD, reverseTokens);
      i += 2;
    } else if (text[i] == '^') {
      stack_push_(0, 3, POW, reverseTokens);
      stack_push_(0, 0, OPENBRACKET, reverseTokens);
      flagPow++;
    } else if (text[i] == 's') {
      if (text[i + 1] == 'i') {
        stack_push_(0, 4, SIN, reverseTokens);
        i += 2;
      } else if (text[i + 1] == 'q') {
        stack_push_(0, 4, SQRT, reverseTokens);
        i += 3;
      }
    } else if (text[i] == 'l') {
      if (text[i + 1] == 'n') {
        stack_push_(0, 4, LN, reverseTokens);
        i += 1;
      } else if (text[i + 1] == 'o') {
        stack_push_(0, 4, LOG, reverseTokens);
        i += 2;
      }
    } else if (text[i] == 'c') {
      stack_push_(0, 4, COS, reverseTokens);
      i += 2;
    } else if (text[i] == 't') {
      stack_push_(0, 4, TAN, reverseTokens);
      i += 2;
    } else if (text[i] == 'a') {
      if (text[i + 1] == 's') {
        stack_push_(0, 4, ASIN, reverseTokens);
        i += 3;
      } else if (text[i + 1] == 'c') {
        stack_push_(0, 4, ACOS, reverseTokens);
        i += 3;
      } else if (text[i + 1] == 't') {
        stack_push_(0, 4, ATAN, reverseTokens);
        i += 3;
      }
    } else if (text[i] == '+') {
      if ((i == 0) || (text[i - 1] == '(')) {
        stack_push_(0, 1, UNPLUS, reverseTokens);
      } else {
        stack_push_(0, 1, PLUS, reverseTokens);
      }
    } else if (text[i] == '-') {
      if ((i == 0) || (text[i - 1] == '(')) {
        stack_push_(0, 1, UNMINUS, reverseTokens);
      } else {
        stack_push_(0, 1, MINUS, reverseTokens);
      }
    }
  }
}

void reversePolishNotation(stack_tt* stack, stack_tt** numStack) {
  stack_tt* supportStack = {0};
  while (stack) {
    if (stack_peekType_(stack) != CLOSEBRACKET) {
      if (stack_peekType_(stack) == NUMBER) {
        stack_push_(stack->value, stack->priority, stack_peekType_(stack),
                    numStack);
      } else {
        while (1) {
          if ((checkSupport(supportStack, stack->priority)) ||
              stack_peekType_(stack) == OPENBRACKET) {
            stack_push_(stack->value, stack->priority, stack_peekType_(stack),
                        &supportStack);
            break;
          } else {
            stack_push_(supportStack->value, supportStack->priority,
                        supportStack->type, numStack);
            stack_pop_(&supportStack);
          }
        }
      }
    } else {
      while (supportStack->type != OPENBRACKET) {
        stack_push_(supportStack->value, supportStack->priority,
                    supportStack->type, numStack);
        stack_pop_(&supportStack);
      }
      stack_pop_(&supportStack);
    }
    stack = stack->next;
  }
  while (supportStack) {
    stack_push_(supportStack->value, supportStack->priority, supportStack->type,
                numStack);
    stack_pop_(&supportStack);
  }
}

void calculate(stack_tt** stack) {
  while ((*stack)->next != NULL) {
    stack_tt *tmp_1 = {0}, *tmp_2 = {0}, *tmp_3 = {0};
    tmp_1 = *stack;
    tmp_2 = tmp_1->next;
    if (tmp_2->next != NULL) {
      tmp_3 = tmp_2->next;
    }
    if (tmp_2->type == NUMBER) {
      while (!tmp_3->priority) {
        tmp_1 = tmp_2;
        tmp_2 = tmp_1->next;
        tmp_3 = tmp_2->next;
      }
      if (stack_peekType_(tmp_3) > 1 && stack_peekType_(tmp_3) < 8) {
        calcLexems(stack, tmp_1, tmp_2, tmp_3);
      } else {
        calcFuncs(stack, tmp_2, tmp_3);
      }
    } else {
      calcFuncs(stack, tmp_1, tmp_2);
    }
  }
}

void calcLexems(stack_tt** stack, stack_tt* tmp_1, stack_tt* tmp_2,
                stack_tt* tmp_3) {
  double numStack = 0;
  double a = tmp_1->value;
  double b = tmp_2->value;
  if (stack_peekType_(tmp_3) == PLUS) {
    numStack = a + b;
  } else if (stack_peekType_(tmp_3) == MINUS) {
    numStack = a - b;
  } else if (stack_peekType_(tmp_3) == MUL) {
    numStack = a * b;
  } else if (stack_peekType_(tmp_3) == DIV) {
    numStack = a / b;
  } else if (stack_peekType_(tmp_3) == POW) {
    numStack = pow(a, b);
  } else if (stack_peekType_(tmp_3) == MOD) {
    numStack = fmod(a, b);
  }
  tmp_1->priority = 0;
  tmp_1->type = NUMBER;
  tmp_1->value = numStack;
  delStack(stack, tmp_3);
  delStack(stack, tmp_2);
}

void calcFuncs(stack_tt** stack, stack_tt* tmp_2, stack_tt* tmp_3) {
  double a = 0;
  double numStack = 0;
  a = tmp_2->value;
  if (stack_peekType_(tmp_3) == UNPLUS) {
    numStack = +a;
  } else if (stack_peekType_(tmp_3) == UNMINUS) {
    numStack = -a;
  } else if (stack_peekType_(tmp_3) == SIN) {
    numStack = sin(a);
  } else if (stack_peekType_(tmp_3) == COS) {
    numStack = cos(a);
  } else if (stack_peekType_(tmp_3) == TAN) {
    numStack = tan(a);
  } else if (stack_peekType_(tmp_3) == ASIN) {
    numStack = asin(a);
  } else if (stack_peekType_(tmp_3) == ACOS) {
    numStack = acos(a);
  } else if (stack_peekType_(tmp_3) == ATAN) {
    numStack = atan(a);
  } else if (stack_peekType_(tmp_3) == LN) {
    numStack = log(a);
  } else if (stack_peekType_(tmp_3) == LOG) {
    numStack = log10(a);
  } else if (stack_peekType_(tmp_3) == SQRT) {
    numStack = sqrt(a);
  }
  tmp_2->priority = 0;
  tmp_2->type = NUMBER;
  tmp_2->value = numStack;
  delStack(stack, tmp_3);
}

void delStack(stack_tt** result, stack_tt* tmp) {
  stack_tt* tmp_in_function = {0};
  tmp_in_function = *result;
  if (*result == tmp) {
    tmp_in_function = (*result)->next;
    free(*result);
    *result = tmp_in_function;
  } else {
    while (tmp_in_function->next != tmp) {
      tmp_in_function = tmp_in_function->next;
    }
    tmp_in_function->next = tmp->next;
    free(tmp);
  }
}

// Эта функция для проверки строки(var x) число это или чтобы заменить x
// начисло
int isNumber(char* str) {
  int status = OK;
  int dotCount = 0;
  int text_length = strlen(str);
  for (int i = 0; i < text_length && status != FAIL; i++) {
    if (isdigit(str[i]) == OK) {
      if (str[i] != '.') {
        status = FAIL;
      } else {
        dotCount++;
        if (dotCount > 1) {
          status = FAIL;
        }
      }
    }
  }
  return status;
}

void setCloseBracket(char* text, stack_tt** input, int* flagPow,
                     int flagOpenBracket) {
  if (*(text + 1) != '^' && flagPow != 0 && flagOpenBracket == 0) {
    while (*flagPow > 0) {
      stack_push_(0, 0, CLOSEBRACKET, input);
      *flagPow = *flagPow - 1;
    }
  }
}

void chToTZ(char* text, int length, int need) {
  for (int i = need; i > 0; i--) {
    text[length - i] = '\0';
  }
}

int isDot(char* dot) {
  int status = FAIL;
  if (*dot == '.') {
    status = OK;
  }
  return status;
}

int funcsParentheses(char* text, int* i, int sum) {
  int status = FAIL;
  char symb = text[(*i) + sum];
  char next = text[(*i) + sum + 1];
  if (symb == 'x') {
    status = OK;
  }
  if (symb == 'l') {
    if (next == 'n') {
      status = OK;
      (*i) += 3;
    }
    if (next == 'o') {
      status = OK;
      (*i) += 4;
    }
  }
  if (symb == 's') {
    if (next == 'q') {
      status = OK;
      (*i) += 5;
    }
    if (next == 'i') {
      status = OK;
      (*i) += 4;
    }
  }
  if (symb == 'c') {
    status = OK;
    (*i) += 4;
  }
  if (symb == 'm') {
    status = OK;
    (*i) += 3;
  }
  if (symb == 't') {
    status = OK;
    (*i) += 4;
  }
  if (symb == 'a') {
    if (next == 's') {
      status = OK;
      (*i) += 5;
    }
    if (next == 'c') {
      status = OK;
      (*i) += 5;
    }
    if (next == 't') {
      status = OK;
      (*i) += 5;
    }
  }
  return status;
}

int checkCorrectOperator(char* text, int* i) {
  int status = FAIL;
  char prev;
  if ((*i) == 0) {
    prev = '\0';
  } else {
    prev = text[(*i) - 1];
  }
  char next = text[(*i) + 1];
  if ((prev == 'x') || (isdigit(prev) != 0) || (prev != '\0')) {
    if ((funcsParentheses(text, i, 1) == OK) || (isdigit(next) != 0) ||
        (next != '\0')) {
      if ((next != ')')) {
        status = OK;
      }
    }
  }
  return status;
}

int isSign(char* text, int* i, int* dotCount) {
  int status = FAIL;
  char symb = text[(*i)];
  if (symb == '+') {
    if (checkCorrectOperator(text, i) == 0) {
      status = OK;
      (*dotCount) = 0;
    }
  }
  if (symb == '-') {
    if ((checkCorrectOperator(text, i) == 0) || ((*i) == 0)) {
      status = OK;
      (*dotCount) = 0;
    }
  }
  if (symb == '*') {
    if (checkCorrectOperator(text, i) == 0) {
      status = OK;
      (*dotCount) = 0;
    }
  }
  if (symb == '/') {
    if (checkCorrectOperator(text, i) == 0) {
      status = OK;
      (*dotCount) = 0;
    }
  }
  if (symb == '^') {
    if (checkCorrectOperator(text, i) == 0) {
      status = OK;
      (*dotCount) = 0;
    }
  }
  if (symb == '.') {
    if (checkCorrectOperator(text, i) == 0) {
      status = OK;
      (*dotCount) += 1;
    }
  }

  if (symb == '(') {
    status = OK;
  }

  if (symb == ')') {
    status = OK;
  }
  return status;
}

int isOper(char symb) {
  int status = FAIL;
  if (symb == '+') {
    status = OK;
  }
  if (symb == '-') {
    status = OK;
  }
  if (symb == '*') {
    status = OK;
  }
  if (symb == '/') {
    status = OK;
  }
  if (symb == '^') {
    status = OK;
  }
  return status;
}

int checkRatioBrackets(char* text, int text_length) {
  int status = FAIL;
  int countL = 0;  // '('
  int countR = 0;  // ')'
  for (int i = 0; i < text_length; i++) {
    if (text[i] == '(') {
      countL++;
    }
    if (text[i] == ')') {
      countR++;
    }
  }
  if (countL == countR) {
    status = OK;
  }
  return status;
}

void stack_push_(double value, int priority, type_t type, stack_tt** stack) {
  stack_tt* newStack = (stack_tt*)malloc(sizeof(stack_tt));
  if (newStack != NULL) {
    newStack->value = value;
    newStack->priority = priority;
    newStack->type = type;
    newStack->next = *stack;
    *stack = newStack;
  }
}

void stack_pop_(stack_tt** last) {
  if (*last != NULL) {
    stack_tt* tmp = (*last)->next;
    free(*last);
    *last = tmp;
  }
}

void stack_reverse_(stack_tt** stack, stack_tt** reverse_stack) {
  while (*reverse_stack) {
    stack_push_((*reverse_stack)->value, (*reverse_stack)->priority,
                (*reverse_stack)->type, stack);
    stack_pop_(reverse_stack);
  }
}

type_t stack_peekType_(stack_tt* stack) { return stack->type; }

int checkSupport(stack_tt* helpStack, int priority) {
  int numStack = 0;
  if (helpStack != NULL) {
    if (priority > helpStack->priority) {
      numStack = 1;
    }
  } else {
    numStack = 1;
  }
  return numStack;
}

stack_tt* stack_free_(stack_tt* list) {
  while (list != NULL) {
    stack_tt* temporary = list;
    list = list->next;
    free(temporary);
  }
  return NULL;
}

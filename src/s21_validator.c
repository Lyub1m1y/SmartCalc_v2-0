#include <string.h>
/// @brief Обработчик ошибок
/// @param str
/// @return 1 - ok 0 - error
int s21_validator(char *str) {
  int res = 1, i = 0, scob = 0;
  while (i != (int)strlen(str)) {
    if (str[i] == 'x' && i != 0 && i != (int)strlen(str)) {
      if (str[i - 1] == ')' || str[i + 1] == '(' ||
          (str[i - 1] <= '9' && str[i - 1] >= '0') ||
          (str[i + 1] <= '9' && str[i + 1] >= '0') || str[i + 1] == 's' ||
          str[i + 1] == 'c' || str[i + 1] == 't' || str[i + 1] == 'a' ||
          str[i + 1] == 'l' || str[i + 1] == 'm' || str[i + 1] == 'i' ||
          str[i + 1] == 'o' || str[i + 1] == 'q' || str[i + 1] == 'n') {
        res = 0;
      }
    }
    if (str[i] == '.') {
      if (i == 0 || i == (int)strlen(str) - 1) {
        res = 0;
      } else {
        if ((str[i - 1] >= '9' && str[i - 1] <= '0') ||
            (str[i + 1] >= '9' && str[i + 1] <= '0')) {
          res = 0;
        }
      }
    } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' ||
               str[i] == '/' || str[i] == '^') {
      if (i == 0) {
        if (str[i] != '-') {
          res = 0;
        } else if (str[i] == '-' && str[i + 1] <= '0' && str[i + 1] >= '9') {
          res = 0;
        } else if (i == (int)strlen(str) - 1) {
          res = 0;
        } else {
          if ((str[i - 1] != ')' && str[i - 1] > '9' && str[i - 1] < '0') ||
              (str[i + 1] < '0' && str[i + 1] > '9') || str[i + 1] == 'm' ||
              str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' ||
              str[i + 1] == '/' || str[i + 1] == '^') {
            res = 0;
          }
        }
      }
    } else if (str[i] == ')') {
      scob -= 1;
      if (scob == -1) {
        res = 0;
      }
      if (i != 0) {
        if (str[i - 1] == '+' || str[i - 1] == '/' || str[i - 1] == '*' ||
            str[i - 1] == '-' || str[i - 1] == '^' || str[i - 1] == '(') {
          res = 0;
        }
        if ((str[i + 1] == 's' && str[i + 2] == 'i' && str[i + 3] == 'n') ||
            (str[i + 1] == 'c' && str[i + 2] == 'o' && str[i + 3] == 's') ||
            (str[i + 1] == 't' && str[i + 2] == 'a' && str[i + 3] == 'n') ||
            (str[i + 1] == 'a' && str[i + 2] == 's' && str[i + 3] == 'i' &&
             str[i + 4] == 'n') ||
            (str[i + 1] == 'a' && str[i + 2] == 'c' && str[i + 3] == 'o' &&
             str[i + 4] == 's') ||
            (str[i + 1] == 'l' && str[i + 2] == 'n') ||
            (str[i + 1] == 'l' && str[i + 2] == 'o' && str[i + 3] == 'g') ||
            (str[i + 1] == 'a' && str[i + 2] == 't' && str[i + 3] == 'a' &&
             str[i + 4] == 'n') ||
            (str[i + 1] == 's' && str[i + 2] == 'q' && str[i + 3] == 'r' &&
             str[i + 4] == 't') ||
            (str[i + 1] == 'm' && str[i + 2] == 'o' && str[i + 3] == 'd')) {
          res = 0;
        }
      } else {
        res = 0;
      }
    } else if (str[i] == '(') {
      scob += 1;
      if (i != (int)strlen(str) - 1) {
        if (str[i + 1] == '+' || str[i + 1] == '/' || str[i + 1] == '*' ||
            str[i + 1] == '^' || str[i + 1] == ')') {
          res = 0;
        }
        if (str[i - 1] <= '9' && str[i - 1] >= '0') {
          res = 0;
        }
      } else {
        res = 0;
      }
    } else if ((str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') ||
               (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') ||
               (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') ||
               (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
                str[i + 3] == 'n') ||
               (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
                str[i + 3] == 's') ||
               (str[i] == 'l' && str[i + 1] == 'n') ||
               (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') ||
               (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
                str[i + 3] == 'n') ||
               (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
                str[i + 3] == 't')) {
      if ((i != 0 && str[i - 1] == ')') ||
          (str[i - 1] <= '9' && str[i - 1] >= '0')) {
        res = 0;
      }
    } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
      if ((i == 0 && str[i] == 'm') ||
          (str[i] == 'd' && i == (int)strlen(str) - 1)) {
        res = 0;
      } else if (i != 0 && str[i] == 'm' &&
                 (str[i - 1] == '(' || str[i - 1] == '+' || str[i - 1] == '/' ||
                  str[i - 1] == '*' || str[i - 1] == '-' ||
                  str[i - 1] == '^')) {
        res = 0;
      } else if (i != (int)strlen(str) - 1 && str[i] == 'd' &&
                 (str[i + 1] == '+' || str[i + 1] == '/' || str[i + 1] == '*' ||
                  str[i + 1] == '-' || str[i + 1] == '^')) {
        res = 0;
      }
    }
    i++;
  }
  if (scob != 0) {
    res = 0;
  }
  return res;
}

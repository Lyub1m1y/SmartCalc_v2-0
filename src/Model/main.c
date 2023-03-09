#include <stdio.h>

#include "s21_validator.c"

int main() {
  char str[] = "hfghgjl";
  printf("%d", s21_validator(str));
  return 0;
}
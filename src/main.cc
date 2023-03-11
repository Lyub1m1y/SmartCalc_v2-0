//----Prod----
//#include <QApplication>

// #include "../View/view.h"

// int main(int argc, char *argv[]) {
//   QApplication a(argc, argv);
//   View w;
//   w.show();
//   return a.exec();
// }

//----TEST----
#include <iostream>

extern "C" {
#include "Model/smartcalc.c"
}

int main() {
  char str[] = "2^2^3";
  double result = 0.0;
  double x = 0.0;

  std::cout << "str: " << str << std::endl;
  std::cout << "result: " << result << std::endl;
  std::cout << "x: " << x << std::endl;
  std::cout << "------------------------------------" << std::endl;
  if (entryPoint(str, &result, x) == OK) {
    std::cout << "str: " << str << std::endl;
    std::cout << "result: " << result << std::endl;
  }

  return 0;
}

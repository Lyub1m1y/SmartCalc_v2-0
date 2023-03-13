//----Prod----
// #include <QApplication>

// #include "../View/view.h"

// int main(int argc, char *argv[]) {
//   QApplication a(argc, argv);
//   View w;
//   w.show();
//   return a.exec();
// }

//----TEST----
#include <iostream>

#include "Model/model.h"

extern "C" {
// #include "Model/smartcalc.c"
}

int main() {
  // char str[] = "cos(x)";
  // double result = 0.0;
  // double x = 1.0;

  // std::cout << "str: " << str << std::endl;
  // std::cout << "result: " << result << std::endl;
  // std::cout << "x: " << x << std::endl;
  // std::cout << "---------Old-----------------" << std::endl;

  // if (entryPoint(str, &result, x) == OK) {
  //   std::cout << "str: " << str << std::endl;
  //   std::cout << "result: " << result << std::endl;
  // } else {
  //   std::cout << "ERROR!" << std::endl;
  // }

  // -----------------------------------------------------------------------
  std::stack<Node> stack_;
  Node v2 = {0, 0, NUMBER};
  // stack_.push(v1);
  // stack_.push(*v2);
  // std::cout << stack_.top().value << std::endl;
  // stack_.pop();
  std::cout << v2.value << std::endl;

  // s21::ModelDefault model;
  // std::cout << "str: " << str << std::endl;
  // std::cout << "result: " << result << std::endl;
  // std::cout << "x: " << x << std::endl;
  // std::cout << "------------Model--------------" << std::endl;

  // if (model.entryPoint(str, &result, x) == OK) {
  //   std::cout << "str: " << str << std::endl;
  //   std::cout << "result: " << result << std::endl;
  // } else {
  //   std::cout << "ERROR!" << std::endl;
  // }

  return 0;
}

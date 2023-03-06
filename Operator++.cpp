#include <iostream>

class Test {
public:
  int a = 0;
  int b = 0;

  void operator++(int) {
    this->a = this->a + 1;
    std::cout << "test++(1)  =  " << this->a << std::endl;
  }

  void operator++() {
    this->b = this->b + 2;
    std::cout << "(2)++test  =  " << this->b << std::endl;
  }
};

int main() {
  Test test;

  test++;
  test++;
  ++test;
  ++test;

  return 0;
}
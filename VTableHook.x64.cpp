#include <iostream>

class VTF {
public:
  virtual void func0() { std::cout << "func0" << std::endl; }
  virtual void func1() { std::cout << "func1" << std::endl; }
  virtual int func2(int num) { return num; }
};

typedef void (*Func)(void);
typedef int (*Func2)(VTF *obj, int num);

int main() {
  VTF obj;

  unsigned long long *obj_p = (unsigned long long *)&obj;
  unsigned long long *obj_vtable = (unsigned long long *)*obj_p;

  // [ ]
  Func func0 = (Func)obj_vtable[0];
  func0();
  func0 = (Func)(unsigned long long)(*obj_vtable);
  func0();

  // [ ]
  Func func1 = (Func)obj_vtable[1];
  func1();
  func1 = (Func)(unsigned long long)(*obj_vtable + 64);
  func1();

  // [ ]
  Func2 func2 = (Func2)obj_vtable[2];
  std::cout << func2((VTF *)obj_vtable, 1212) << std::endl;

  func2 = (Func2)(unsigned long long)(*obj_vtable + 128);
  std::cout << func2((VTF *)obj_vtable, 1313) << std::endl;

  return 0;
}
#include <iostream>
#include <string>
#include <vector>

#include "class_test.h"
#include "string_test.h"
#include "values_test.h"
#include "func_test.h"

// 这个文件根据config.h.in自动生成  在build目录
#include <config.h>

#include "app.h"

using namespace std;

#ifdef USE_MACRO
void print()
{
  cout << "USE_MACRO1" << endl;
}
#else
void print()
{
  cout << "USE_MACRO2" << endl;
}
#endif

int main()
{
  cout << "Hello, World!" << endl;

  print();

  run_class_test();

  run_string_test();

  run_values_test();

  run_func_test();

  flushBridgeTask();
  
  printString("str to object-c");

  return 0;
}
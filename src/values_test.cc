#include <iostream>
#include <string>

#include "values_test.h"

using namespace std;

void run_values_test()
{
  // 值类型数据处理
  int a = 99;
  int *aPtr = &a; // 指针
  int &aRef = a;  // 引用
  cout << "aPtr=" << *aPtr << " a=" << a << " aRef=" << aRef << endl;
  *aPtr = 100; // 修改指针的值 会修改原始a的值
  cout << "aPtr=" << *aPtr << " a=" << a << " aRef=" << aRef << endl;
  aRef = 110; // 修改引用的值  会修改原始的值
  cout << "aPtr=" << *aPtr << " a=" << a << " aRef=" << aRef << endl;
}
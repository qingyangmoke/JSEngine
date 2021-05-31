#include <iostream>
#include <string>

#include "string_test.h"

using namespace std;

void run_string_test()
{
  string str = "str1";
  string *strPtr = &str; // 指针
  string &strRef = str; // 引用
  strPtr->append("xxx");
  cout << "strPtr=" << strPtr->c_str() << "  str=" << str << "  strRef=" << strRef << endl;
  strRef = "str2";
  cout << "strPtr=" << strPtr->c_str() << "  str=" << str << "  strRef=" << strRef << endl;
}
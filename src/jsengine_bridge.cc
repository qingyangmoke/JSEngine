#include "include/jsengine_bridge.h"
#include <iostream>
#include <string>

using namespace JSEngineNS;

int flushBridgeTask()
{
  Engine *engine = Engine::instance();
  std::cout << "engine.version=" << engine->version << std::endl;
  std::cout << "flushBridgeTask from c++" << std::endl;
  return 99;
}

int testStruct(PTR_OBJECT target)
{
  NativeString *str = static_cast<NativeString *>(target);
  std::cout << "printNativeString string=" << str->string << ", length=" << str->length << std::endl;
  return 1;
}

int printString(PTR_C_STR str)
{
  std::cout << "printString string=" << str << std::endl;
  return 1;
}

void testCallback(PTR_C_STR str, ResultCallback callback, PTR_OBJECT target)
{
  std::cout << "testCallback C++ str=" << str << std::endl;
  std::string result;
  result.append(str);
  result.append("+ C++ callback");
  callback(result.c_str(), target);
}

Student::Student(const std::string &name, const int age)
{
  this->name = name;
  this->age = age;
}

void Student::say()
{
  std::cout << "name=" << name << ", age=" << age << std::endl;
}
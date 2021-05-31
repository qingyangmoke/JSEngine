#include <iostream>
#include <string>

#include "func_test.h"
#include "apps/hello.h"

using namespace std;

void callBackTest(MyCallBack callback)
{
  callback(10);
}

void callbackResult(int a)
{
  cout << "callbackResult=" << a << endl;
}

class Obj : public IPrinter
{
public:
  Obj(string name);

public:
  void print(int a) override;

private:
  string _name;
};

Obj::Obj(string name)
{
  this->_name = name;
}

void Obj::print(int a)
{
  cout << this->_name << ","
       << "callbackResult=" << a << endl;
}

void doPrint(void *printerPtr)
{
  IPrinter *obj = static_cast<IPrinter *>(printerPtr);
  obj->print(99);
}

void run_func_test()
{
  string helloResponse = getHelloResponse("hello");
  cout << "getHelloResponse: " << helloResponse << endl;
  callBackTest(callbackResult);

  Obj obj("test");
  doPrint(&obj);
}
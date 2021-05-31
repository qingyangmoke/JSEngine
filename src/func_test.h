#pragma once

typedef void (*MyCallBack)(int a);

class IPrinter
{
public:
  virtual void print(int a) = 0;
};

void callBackTest(MyCallBack callback);

void run_func_test();
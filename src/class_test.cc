#include <iostream>
#include <string>
#include "apps/Animal.h"
#include "apps/Dog.h"
using namespace std;
using namespace CPlusDemo;

void run_class_test()
{
  // 不需要手动释放，会自动释放
  Animal animal = Animal("animal");
  animal.say();

  // 不需要手动释放，会自动释放
  Animal dog = Dog();
  dog.say();

  // 这样的初始化方式 系统不会自动释放  需要自己主动释放
  Animal *cat = new Animal("cat");
  cat->say();
  delete (cat);

  // 不需要手动释放，会自动释放
  Animal monkey("monkey");
  monkey.say();

  // name为默认值
  Animal cc;
  cc.say();

  cout << "cc == animal => " << (cc == animal) << endl;
  cout << "cc == cat  => " << (&cc == cat) << endl;
}
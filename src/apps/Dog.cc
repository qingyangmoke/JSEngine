#include <iostream>
#include "Dog.h"

using namespace std;
using namespace CPlusDemo;

Dog::Dog() : Animal("dog") {}

void Dog::say()
{
  Animal::say();
}

Dog::~Dog()
{
  cout << "Dog -> dog 被释放" << endl;
}

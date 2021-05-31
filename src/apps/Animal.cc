#include <iostream>
#include <stdio.h>
#include <string.h>

#include "Animal.h"

using namespace std;
using namespace CPlusDemo;

Animal::Animal(string name)
{
  this->name = name;
}

void Animal::say()
{
  cout << "hi, my name is " << this->name << endl;
}

Animal::~Animal()
{
  cout << "RRAnimal name=" << this->name << " 被释放" << endl;
}

// bool Animal::operator==(const Animal& a)
// {
//   return a.name == this->name;
// }

bool CPlusDemo::operator==(const Animal &a, const Animal &b)
{
  return a.name == b.name;
}
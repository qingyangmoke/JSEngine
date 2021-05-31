#pragma once

#include "Animal.h"

namespace CPlusDemo
{
  class Dog : public CPlusDemo::Animal
  {
  public:
    Dog();
    virtual void say();
    ~Dog();
  };
}
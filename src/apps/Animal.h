#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace CPlusDemo
{
  class Animal
  {
  public:
    std::string name;
    virtual void say();
    Animal(std::string name = "animal");
    // bool operator==(const Animal& b);
    ~Animal();
  };
  bool operator==(const Animal &a, const Animal &b);
}

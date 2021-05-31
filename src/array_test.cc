#include <iostream>
#include <string>
#include <vector>

#include "array_test.h"

using namespace std;

template <class T>
int array_length(T &arr)
{
  return sizeof(arr) > 0 ? end(arr) - begin(arr) : 0;
}

// 打印静态数组
template <class T>
void array_print(T &arr)
{
  for (auto i : arr)
  {
    cout << i << endl;
  }
}

// 打印可变数组
template <class T>
void print_vector(vector<T> &arr)
{
  std::vector<int>::iterator i;
  for (i = arr.begin(); i < arr.end(); i++)
  {
    cout << *i << endl;
  }
}

void run_array_test()
{
  int arr1[2];
  arr1[0] = 1;
  arr1[1] = 3;
  int len = array_length(arr1);
  cout << "数组长度:" << len << endl;

  array_print(arr1);

  std::vector<int> vect;
  vect.insert(vect.begin(), 10);
  vect.push_back(1);

  print_vector(vect);
}
#include <iostream>
#include "TernaryNumber.hpp"

int main()
{
  // Проверка правильности работы оператора ==
  try
  {
    TernaryNumber num1("102210");
    TernaryNumber num2("102210");
  
    if(num1 == num2)
    {
      return 0;
    }
  }
  catch(std::exception &e)
  {
    std::cout<<e.what();
    return 1;
  }
  
  return 1;
}
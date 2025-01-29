#include <iostream>
#include "TernaryNumber.hpp"

int main()
{
  // Проверка правильности выполнения XOR
  try
  {
    TernaryNumber num1("10222");
    TernaryNumber num2("11021");
    TernaryNumber res("21210");
  
    if( (num1 ^ num2) == res )
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

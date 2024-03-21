#include<iostream>
#include"../inc/compositor.h"
#include<string>

int main()
{
  std::cout << "Hello World" << std::endl;

  Object t1;
  Datum<std::string> text;
  Behavior<void()> print =
  {
    [&](Object* object)
    {
      std::cout << text[object] << std::endl;
    }
  };

  t1 + text = "Some tests";
  t1 += print;
  
  return 0;
}

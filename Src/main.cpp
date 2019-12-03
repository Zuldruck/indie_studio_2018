#include "Core.hpp"
#include <iostream>
#include "Utils.hpp"

int main()
{
   ind::Core core;

   std::srand(std::time(nullptr));
   core.setUp();
   core.run();
   return (0);
}

#include <iostream>
#include <boost/filesystem.hpp>

#include "Hello.h"

int main(int argc, char* argv[])
{
  // trivial use of Hello class
  Hello hi;
  hi.print();

  // trivial use of boost filesystem
  boost::filesystem::path path = "/usr/share/cmake/modules";
  if (path.is_relative())
  {
    std::cout << "Path is relative" << std::endl;
  }
  else
  {
    std::cout << "Path is not relative" << std::endl;
  }

  return 0;
}

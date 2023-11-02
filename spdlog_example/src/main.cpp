#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_sinks.h"

struct UserClass
{
};
std::ostream& operator<<(std::ostream& os, const UserClass& c) { return os << "My class"; }

int main()
{
  UserClass c;
  spdlog::info("Hello, World: {}!", c);

  return 0;
}

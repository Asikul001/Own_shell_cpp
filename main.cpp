#include "./src/headers/predefined_header.hpp"
#include "./src/headers/main_variable_declear.hpp"


int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  entry_point();
  return 0;
}

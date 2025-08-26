#include "./headers/predefined_header.hpp"

void check_type(std::string &input) {
  const int TYPE_LEN = 5;
  std::string text = input.substr(TYPE_LEN);
  if (select_command(text) != command::nothing)
    std::cout << text << " is a shell builtin";
  else {
    std::string hold_path = valid_relative_path(text);
    if (hold_path != "")
      std::cout << text << " is " << hold_path;
    else
      std::cout << text << ": not found";
  }
  std::cout << std::endl;
};

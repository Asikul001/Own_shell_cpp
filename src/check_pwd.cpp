#include "./headers/predefined_header.hpp"
void check_pwd() {
  std::cout << std::filesystem::current_path().string() << std::endl;
};
#include "./headers/predefined_header.hpp"
#include "./headers/global_variable.hpp"

void check_switch(std::string first_command, std::string &input)
{
  switch (select_command(first_command))
  {
  case command::echo:
  {
    check_echo(input);
    break;
  }
  case command::type:
  {
    check_type(input);
    break;
  }
  case command::pwd:
  {
    check_pwd();
    break;
  }
  case command::history:
  {
    check_history(input);
    break;
  }
  case command::cd:
  {
    check_cd(input);
    break;
  }
  default:
    check_command(input);
  }
}
#include "./headers/predefined_header.hpp"
#include "./headers/global_variable.hpp"

command select_command(std::string str_data)
{
  if (str_data == "echo")
    return command::echo;
  if (str_data == "type")
    return command::type;
  if (str_data == "pwd")
    return command::pwd;
  if (str_data == "exit")
    return command::exit;
  if (str_data == "history")
    return command::history;
  if (str_data == "cd")
    return command::cd;
  return command::nothing;
};
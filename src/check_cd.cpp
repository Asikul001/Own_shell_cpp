#include "./headers/predefined_header.hpp"
#include "./headers/global_variable.hpp"

void check_cd(std::string hold_command) {
  std::stringstream string_stream(hold_command);
  std::string first_command, second_command;
  string_stream >> first_command >> second_command;
  if (std::filesystem::exists(second_command)) {
    std::filesystem::current_path(second_command);
  } else {
    if (second_command[0] == '~') {
      std::string home_path = getenv("HOME");
      second_command.erase(0, 1);
      home_path += second_command;
      if (std::filesystem::exists(home_path))
        std::filesystem::current_path(home_path);
      else
        std::cout << first_command << ": " << second_command
                  << ": No such file or directory" << std::endl;

    } else
      std::cout << first_command << ": " << second_command
                << ": No such file or directory" << std::endl;
  }
}

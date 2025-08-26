#include "./headers/predefined_header.hpp"
#include "./headers/global_variable.hpp"

void entry_point()
{
using_history();
  rl_bind_key('\t', auto_complete);
  rl_bind_keyseq("\e[A", rl_get_previous_history);
  rl_bind_keyseq("\e[B", rl_get_next_history);
  char *env_path = std::getenv("HISTFILE");
  std::string hold_path = "";
  if (env_path != nullptr)
  {
    hold_path = env_path;
    read_history(hold_path);
  }
  // std::cout << "problem" << std::endl;
  char *hold_data = readline("$ ");
  std::string input = hold_data;
  history.push_back(input);
  add_history(input.c_str());

  while (input.find("exit") != 0)
  {
    std::stringstream hold_command(input);
    std::string first_command;
    hold_command >> first_command;

    if (input.find("|") != std::string::npos)
    {
      check_pipe(input);
    }
    else
    {
      check_switch(first_command, input);
    }

    hold_data = readline("$ ");
    input = hold_data;
    history.push_back(input);
    add_history(input.c_str());
    auto_complete_check = 0;
    check_count_match_data = 0;
    if (input == "exit 0" && env_path != nullptr)
      append_history(hold_path);
  }
}
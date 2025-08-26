#include "./headers/predefined_header.hpp"
#include "./headers/global_variable.hpp"

void check_pipe(std::string &input_str)
{
  std::stringstream input_stream(input_str);
  std::string hold_input;
  std::vector<std::string> command;

  // Split commands by '|'
  while (std::getline(input_stream, hold_input, '|'))
  {
    while (!hold_input.empty() && hold_input.front() == ' ')
      hold_input.erase(0, 1);
    while (!hold_input.empty() && hold_input.back() == ' ')
      hold_input.pop_back();
    command.push_back(hold_input);
  }

  int n = command.size() - 1;
  int fd[n][2];
  for (int i = 0; i < n; i++)
  {
    if (pipe(fd[i]) == -1)
    {
      perror("pipe");
      exit(1);
    }
  }

  std::vector<pid_t> pids;

  for (int i = 0; i < command.size(); i++)
  {
    std::vector<std::string> temp_hold_all_command;
    std::vector<char *> command_all_part;
    put_data(command[i], command_all_part, temp_hold_all_command);

    std::string first_command = "";
    std::stringstream hold_temp_stream(command[i]);
    std::getline(hold_temp_stream, first_command, ' ');

    if (select_command(first_command) != command::nothing)
    {
      pid_t pid = fork();
      if (pid == 0)
      {
        if (i < n)
        { // not last command
          dup2(fd[i][1], STDOUT_FILENO);
        }
        // Close all pipes in child
        for (int j = 0; j < n; j++)
        {
          close(fd[j][0]);
          close(fd[j][1]);
        }
        check_switch(first_command, command[i]);
        std::fflush(stdout);
        exit(0);
      }
      pids.push_back(pid);
    }
    else
    {
      pid_t pid = fork();

      if (pid == 0)
      { // child
        if (i > 0)
        { // not first command
          dup2(fd[i - 1][0], STDIN_FILENO);
        }
        if (i < n)
        { // not last command
          dup2(fd[i][1], STDOUT_FILENO);
        }
        // Close all pipes in child
        for (int j = 0; j < n; j++)
        {
          close(fd[j][0]);
          close(fd[j][1]);
        }
        execvp(command_all_part[0], command_all_part.data());
        perror("execvp");
        exit(1);
      }
      pids.push_back(pid);
    }
    // Parent closes used pipe ends immediately
    if (i > 0)
      close(fd[i - 1][0]);
    if (i < n)
      close(fd[i][1]);
  }
  // Wait for all children
  for (pid_t pid : pids)
  {
    waitpid(pid, NULL, 0);
  }
}

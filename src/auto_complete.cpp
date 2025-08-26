#include "./headers/predefined_header.hpp"
#include "./headers/global_variable.hpp"



int check_match_data(std::vector<std::string> list_match_data_temp)
{
  std::string hold = list_match_data_temp[0];
  for (int i = 1; i < list_match_data_temp.size(); i++)
  {
    if (list_match_data_temp[i].find(hold) != 0)
      return 0;
  }
  return 1;
}

int auto_complete(int count, int key)
{
  std::vector<std::string> hold_auto_complete = {"exit", "echo"};
  auto_complete_check++;
  std::string final_string = "";
  std::string hold = rl_line_buffer;
  while (hold[0] == ' ')
    hold.erase(0, 1);
  if (auto_complete_check > 0)
  {
    for (int i = 0; i < hold_auto_complete.size(); i++)
    {
      auto hold_position = hold_auto_complete[i].find(hold);
      if (hold_position == 0)
      {
        final_string = hold_auto_complete[i] + " ";
      }
    }
    if (final_string == "")
    {
      std::string hold_env = std::getenv("PATH");
      std::stringstream env(hold_env);
      std::vector<std::string> list_match_data_temp;
      std::string list_match_data = "";
      while (!env.eof())
      {
        std::string hold_data = "";
        std::getline(env, hold_data, ':');
        for (const auto &iterator :
             std::filesystem::directory_iterator(hold_data))
        {
          std::string hold_path = iterator.path().string();
          if (hold_path.substr(hold_data.size() + 1).find(hold) == 0)
          {
            if (list_match_data_temp.size() == 0)
            {
              std::string crop = hold_path.substr(hold_data.size() + 1);
              list_match_data_temp.push_back(crop);
            }
            else
            {
              std::string crop = hold_path.substr(hold_data.size() + 1);
              list_match_data_temp.push_back(crop);
            }
          }
        }
      }
      sort(list_match_data_temp.begin(), list_match_data_temp.end());
      if (list_match_data_temp.size() > 1 &&
          (list_match_data_temp[1].find(list_match_data_temp[0]) == 0))
      {
        if (check_match_data(list_match_data_temp))
        {
          final_string = list_match_data_temp[0];
          auto_complete_check--;
        }
        check_count_match_data++;
      }
      if (final_string == "")
      {
        for (int i = 0; i < list_match_data_temp.size(); i++)
        {
          if (list_match_data == "")
          {
            list_match_data = list_match_data_temp[i];
          }
          else
          {
            store_auto_string = hold;
            list_match_data += "  " + list_match_data_temp[i];
          }
        }
        if (list_match_data != "" &&
            list_match_data.find(' ') == std::string::npos)
        {
          final_string = list_match_data + " ";
        }
        else if (list_match_data != "")
        {
          if (auto_complete_check < 2)
          {
            std::cout << "\a";
            final_string = hold;
          }
          else if (auto_complete_check == 2)
          {
            std::string print_string = "\n" + list_match_data + "\n";
            std::cout << print_string;
            rl_on_new_line();
            final_string = store_auto_string;
            store_auto_string = "";
          }
        }
      }
    }
    if (final_string == "")
    {
      std::cout << "\a";
    }
    else
    {
      rl_replace_line(&final_string[0], 1);
      rl_point = strlen(&final_string[0]);
    }
  }
  return 0;
}
int put_data(std::string hold_input, std::vector<char *> &args,
             std::vector<std::string> &temp_hold)
{
  std::string hold_data = "";
  while (hold_input[0] == ' ')
  {
    hold_input.erase(0, 1);
  }
  std::stringstream stream_input(hold_input);
  while (!stream_input.eof() && std::getline(stream_input, hold_data, ' '))
  {
    if (temp_hold.size() == 0)
    {
      std::string hold = valid_relative_path(hold_data);
      if (hold != "")
      {
        temp_hold.push_back(hold);
        continue;
      }
    }
    else
    {
      if (hold_data[0] == '"')
      {
        hold_data.erase(0, 1);
        hold_data.pop_back();
        temp_hold.push_back(hold_data);
      }
      else
      {
        temp_hold.push_back(hold_data);
      }
    }
  }
  for (int i = 0; i < temp_hold.size(); i++)
  {
    args.push_back(&temp_hold[i][0]);
  }
  args.push_back(nullptr);
  return 0;
};

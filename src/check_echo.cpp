#include "./headers/predefined_header.hpp"


std::string escape_charecter(std::string print_data) {
  std::stringstream hold_new_stream(print_data);
  std::string print_new_data = "";
  std::string hold_data = "";
  std::getline(hold_new_stream, hold_data, '\\');
  print_new_data += hold_data;
  while (!hold_new_stream.eof()) {
    std::getline(hold_new_stream, hold_data, '\\');
    if (hold_data == "")
      print_new_data += "\\";
    print_new_data += hold_data;
  }
  return print_new_data;
}  

std::string remain_string(std::string &text) {
  std::stringstream hold_stream(text);
  std::string print_data = "";
  while (!hold_stream.eof()) {
    std::string hold = "";
    std::getline(hold_stream, hold, ' ');
    if (hold != "" && print_data != "")
      print_data = print_data + " " + hold;
    if (print_data == "" && hold != "")
      print_data = hold;
  }
  print_data = escape_charecter(print_data);
  return print_data;
}

std::string valid_relative_path(std::string text) {
  std::string hold_value = std::getenv("PATH");
  std::stringstream env(hold_value);
  while (!env.eof()) {
    std::string valid_path;
    std::getline(env, valid_path, ':');
    std::string check_path = valid_path + "/" + text;
    if (std::filesystem::exists(check_path)) {
      std::filesystem::perms permission =
          std::filesystem::status(check_path).permissions();
      if ((permission & std::filesystem::perms::owner_exec) ==
          std::filesystem::perms::owner_exec) {
        return check_path;
      }
    }
  }
  return "";
};

std::string check_single_code(std::string value) {
  int check = 0, j = 0;
  for (int i = 0; i < value.size(); i++) {
    if (check == 0) {
      if (value[i] == '\'') {
        value.erase(i, 1);
        check++;
        i--;
        j = 0;
      } else if (value[i] == ' ' && j == 0) {
        j++;
      } else if (value[i] == ' ' && j == 1) {
        value.erase(i, 1);
        i--;
        continue;
      }
    } else if (value[i] != '\'' && i == value.size() - 1) {
      std::string next_data = "";
      std::cout << ">";
      while (std::getline(std::cin, next_data) &&
             next_data[next_data.size() - 1] != '"') {
        check_single_code(next_data);
        value += "\n" + next_data;
      }
      check_single_code(next_data);
      value += "\n" + next_data;
    } else if (value[i] == '\'' && check == 1) {
      check--;
      value.erase(i, 1);
      i--;
    }
  }
  return value;
};

std::string check_double_code(std::string value) {
  int check = 0, j = 0;
  for (int i = 0; i < value.size(); i++) {
    if (check == 0 && value[i] != '\\') {
      if (value[i] == '"') {
        value.erase(i, 1);
        check++;
        i--;
        j = 0;
      } else if (value[i] == ' ' && j == 0) {
        j++;
      } else if (value[i] == ' ' && j == 1) {
        value.erase(i, 1);
        i--;
        continue;
      }
    } else if (value[i] == '\\') {
      if ((i + 1) != value.size() - 1 || check == 0) {
        if (value[i + 1] == '\"' || value[i + 1] == '\'' ||
            value[i + 1] == ' ' || value[i + 1] == '\\') {
          value.erase(i, 1);
          continue;
        }
        continue;
      }
      value.erase(i, 1);
      std::string next_data = "";
      std::cout << ">";
      while (std::getline(std::cin, next_data) &&
             next_data[next_data.size() - 1] != '"') {
        check_double_code(next_data);
        value += "\n" + next_data;
      }
      check_double_code(next_data);
      value += "\n" + next_data;
    } else if (value[i] == '"' && check == 1) {
      check--;
      value.erase(i, 1);
      i--;
    }
  }
  return value;
}


void append_echo(std::string &text) {
  std::string hold_path_loc = "";
  if (text.find(">>") != std::string::npos) {
    int len = text.size() - (text.find(">") + 3);
    hold_path_loc = text.substr(text.find(">") + 3, len);
  } else {
    int len = text.size() - (text.find(">") + 2);
    hold_path_loc = text.substr(text.find(">") + 2, len);
  }

  text.erase(text.find(">") - 1, 1);
  std::stringstream sstream(text);
  std::string hold = "";
  std::getline(sstream, hold, '>');
  if (hold[0] == '"') {
    std::string pick = check_double_code(hold);
    if (text.find(">>") != std::string::npos) {
      std::fstream file(hold_path_loc, std::ios::app);
      if (file.tellg() != 0)
        file << "\n";
      file << pick;
      file.close();
    } else {
      std::fstream file(hold_path_loc, std::ios::out);
      file << pick;
      file.close();
    }

  } else if (hold[0] == '\'') {
    std::string pick = check_single_code(hold);
    if (text.find(">>") != std::string::npos) {
      std::fstream file(hold_path_loc, std::ios::app);
      if (file.tellg() != 0)
        file << "\n";
      file << pick;
      file.close();
    } else {
      std::fstream file(hold_path_loc, std::ios::out);
      file << pick;
      file.close();
    }
  } else {
    std::string pick = remain_string(hold);
    if (text.find(">>") != std::string::npos) {
      std::fstream file(hold_path_loc, std::ios::app);
      if (file.tellg() != 0)
        file << "\n";
      file << pick;
      file.close();
    } else {
      std::fstream file(hold_path_loc, std::ios::out);
      file << pick;
      file.close();
    }
  }
};

void check_echo(std::string &input) {
  std::string text = input.substr(5);
  if (text.find("2>") != std::string::npos) {

    int hold_pos = text.find(">");
    int len = text.size() - (hold_pos + 2);
    std::string hold_file_path = text.substr(hold_pos + 2, len);

    std::stringstream sstream(text);
    std::string hold = "";
    std::getline(sstream, hold, ' ');
    if (hold[0] == '\'' || hold[0] == '"') {
      std::string second_hold = "";
      std::getline(sstream, second_hold, hold[0]);
      hold += " " + second_hold;
      hold.erase(0, 1);
    }
    std::fstream file(hold_file_path, std::ios::out);
    file.close();
    std::cout << hold << std::endl;
    // return hold;
  } else if (text.find("1>") != std::string::npos ||
             text.find(">") != std::string::npos ||
             text.find("1>>") != std::string::npos) {
    if (text.find("1>") != std::string::npos)
      text.erase(text.find("1>"), 1);
    if (text.find("1>>") != std::string::npos)
      text.erase(text.find("1>>"), 1);
    append_echo(text);
  } else if (text[0] == '"') {
    std::string final_data = check_double_code(text);
    std::cout << final_data << std::endl;
  } else if (text[0] == '\'') {
    std::string final_data = check_single_code(text);
    std::cout << final_data << std::endl;
  } else {
    std::string final_data = remain_string(text);
    std::cout << final_data << std::endl;
  }
};

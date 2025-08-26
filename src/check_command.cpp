#include "./headers/predefined_header.hpp"
#include "./headers/global_variable.hpp"


std::string send_ls_data(std::string current_path, int flag) {
  std::string send_path = "";
  std::vector<std::filesystem::directory_entry> hold;
  for (const auto &hold_path :
       std::filesystem::directory_iterator(current_path)) {
    hold.push_back(hold_path);
  }
  std::sort(hold.begin(), hold.end());
  if (flag == 1) {
    for (int i = 0; i < hold.size(); i++) {
      if (send_path != "")
        send_path += "\n";
      send_path += hold[i].path().string().substr(current_path.size() + 1);
    }
  } else {
    for (int i = 0; i < hold.size(); i++) {
      if (send_path != "")
        send_path += " ";
      send_path += hold[i].path().string().substr(current_path.size() + 1);
    }
  }
  return send_path;
}

void check_ls(std::string input) {
  while (input[input.size() - 1] == ' ')
    input.erase((input.size() - 1), 1);
  if (input.size() == 2) {
    std::string hold_path = std::filesystem::current_path().string();
    std::cout << send_ls_data(hold_path, 0) << std::endl;
  } else {
    std::stringstream sstream(input.substr(3));
    std::string hold = "";
    std::getline(sstream, hold, ' ');
    if (input.find(">>") != std::string::npos ||
        input.find("1>") != std::string::npos ||
        input.find("2>") != std::string::npos ||
        input.find(">") != std::string::npos) {
      int flag = 0;
      int check = 0;
      if (hold == "-1") {
        flag = 1;
        std::getline(sstream, hold, ' ');
      }
      if (input.find(">>") != std::string::npos ||
          input.find("2>>") != std::string::npos) {
        if (input.find("2>>") != std::string::npos) {
          check = 1;
          input.erase(input.find("2>>"), 1);
        }
        int len = input.size() - (input.find(">>") + 3);
        std::string path = input.substr(input.find(">>") + 3, len);
        if (std::filesystem::exists(hold) && check == 0) {
          std::fstream file(path, std::ios::app);
          if (file.tellg() != 0)
            file << "\n";
          std::string hold_data = send_ls_data(hold, flag);
          file << hold_data;
          file.close();
        } else {
          if (check == 1) {
            std::fstream file(path, std::ios::app);
            if (file.tellg() != 0)
              file << "\n";
            std::string mess = "ls: " + hold + ": No such file or directory";
            file << mess;
            file.close();
          } else {
            std::fstream file(path, std::ios::out);
            file.close();
            std::string mess = "ls: " + hold + ": No such file or directory";
            std::cout << mess << std::endl;
          }
        }
      } else if (input.find("2>") != std::string::npos) {
        int len = input.size() - (input.find("2>") + 3);
        std::string path = input.substr(input.find("2>") + 3, len);
        if (std::filesystem::exists(hold)) {
          std::cout << send_ls_data(hold, flag) << std::endl;
          std::fstream file(path, std::ios::out);
          file.close();
        } else {
          std::fstream file(path, std::ios::out);
          std::string mess = "ls: " + hold + ": No such file or directory";
          file << mess;
          file.close();
        }
      } else if (input.find(">") != std::string::npos) {
        if (input.find(">") != std::string::npos ||
            input.find("1>") != std::string::npos) {
          if (input.find("1>") != std::string::npos)
            input.erase(input.find("1>"), 1);
          int len = input.size() - (input.find(">") + 2);
          std::string path = input.substr(input.find(">") + 2, len);
          if (std::filesystem::exists(hold)) {
            std::fstream file(path, std::ios::out);
            file << send_ls_data(hold, flag);
            file.close();
          } else {
            std::fstream file(path);
            file.close();
            std::string mess = "ls: " + hold + ": No such file or directory";
            std::cout << mess << std::endl;
          }
        } else {
          std::getline(sstream, hold, ' ');
          std::string mess = "ls: " + hold + ": No such file or directory";
          std::cout << mess << std::endl;
        }
      }
    } else {
      int flag = 0;
      if (hold == "-1") {
        flag = 1;
        if (sstream.eof()) {
          std::string path = std::filesystem::current_path().string();
          std::cout << send_ls_data(path, flag) << std::endl;
        } else {
          std::getline(sstream, hold, ' ');
          if (sstream.eof()) {
            if (std::filesystem::exists(hold))
              std::cout << send_ls_data(hold, flag) << std::endl;
            else {
              std::string mess = "ls: " + hold + ": No such file or directory";
              std::cout << mess << std::endl;
            }
          } else {
            std::getline(sstream, hold, ' ');
            std::string mess = "ls: " + hold + ": No such file or directory";
            std::cout << mess << std::endl;
          }
        }
      } else {
        if (sstream.eof()) {
          if (std::filesystem::exists(hold))
            std::cout << send_ls_data(hold, flag) << std::endl;
          else {
            std::string mess = "ls: " + hold + ": No such file or directory";
            std::cout << mess << std::endl;
          }
        } else {
          std::getline(sstream, hold, ' ');
          std::string mess = "ls: " + hold + ": No such file or directory";
          std::cout << mess << std::endl;
        }
      }
    }
  }
}


std::string print_file_data(std::string hold_data) {
  std::string file_data = "";
  std::fstream file(hold_data);
  std::string hold = "";
  while (std::getline(file, hold, '\n')) {
    if (file_data != "")
      file_data += "\n";
    file_data += hold;
  }
  file.close();
  return file_data;
}

void check_cat(std::string input) {
  std::string path = input.substr(4);
  std::string put_path = "";
  if (path.find("2>") != std::string::npos ||
      path.find("2>>") != std::string::npos) {
    int check = 0;
    if (path.find("2>>") != std::string::npos) {
      path.erase(path.find("2>>") + 2, 1);
      check = 1;
    }
    int hold = path.find(">");
    int len = path.size() - (hold + 2);
    std::string hold_file_path = path.substr(hold + 2, len);
    std::stringstream sstream(path);
    std::string hold_data = "";
    std::getline(sstream, hold_data, ' ');
    while (hold_data != "2>") {
      if (hold_data[0] == '"' || hold_data[0] == '\'') {
        hold_data.erase(0, 1);
        hold_data.erase(hold_data.size() - 1, 1);
      }
      if (std::filesystem::exists(hold_data)) {
        std::cout << print_file_data(hold_data) << std::endl;
      } else {
        if (check == 1) {
          std::fstream file(hold_file_path, std::ios::app);
          if (file.tellg() != 0)
            file << "\n";
          std::string mess =
              "cat: " + hold_data + ": No such file or directory";
          file << mess;
          file.close();
        } else {
          std::fstream file(hold_file_path, std::ios::out);
          file << "cat: " << hold_data << ": No such file or directory"
               << std::endl;
          file.close();
        }
      }
      std::getline(sstream, hold_data, ' ');
    }
    return;
  }
  if (path.find("1>") != std::string::npos ||
      path.find(">") != std::string::npos) {
    if (path.find("1>") != std::string::npos)
      path.erase(path.find("1>"), 1);
    put_path = path.substr(path.find(">") + 2);
    if (put_path[0] == '\'')
      put_path = check_single_code(put_path);
    else if (put_path[0] == '"')
      put_path = check_double_code(put_path);
  }
  std::stringstream sstream(path);
  std::string add_all_data = "";
  while (!sstream.eof()) {
    std::string hold_data = "";
    std::getline(sstream, hold_data, ' ');
    if (hold_data == " ")
      continue;
    std::string temp_hold = "";
    if (hold_data[0] == '\'') { // checking for single code
      while (hold_data[hold_data.size() - 1] != '\'') {
        temp_hold += hold_data + " ";
        std::getline(sstream, hold_data, ' ');
        continue;
      }
      temp_hold += hold_data;
      std::string hold = check_single_code(temp_hold);
      if (put_path == "") {
        std::cout << print_file_data(hold);
        if (sstream.eof())
          std::cout << std::endl;
      } else if (std::filesystem::exists(hold)) {
        std::fstream file(put_path, std::ios::app);
        if (file.is_open())
          file << print_file_data(hold);
      } else {
        std::string data = "cat: " + hold_data + ": No such file or directory";
        std::cout << data << std::endl;
      }
      temp_hold = "";
      continue;
    }
    if (hold_data[0] == '"') { // for double code checking
      while (hold_data[hold_data.size() - 1] != '"') {
        temp_hold += hold_data + " ";
        std::getline(sstream, hold_data, ' ');
      }
      temp_hold += hold_data;
      if (put_path == "") {
        temp_hold.erase(0, 1);
        temp_hold.erase(temp_hold.size() - 1, 1);
        std::cout << print_file_data(temp_hold);
      } else if (std::filesystem::exists(temp_hold)) {
        std::fstream file(put_path, std::ios::app);
        if (file.is_open())
          file << print_file_data(temp_hold);
      } else {
        std::string data = "cat: " + hold_data + ": No such file or directory";
        add_all_data += data;
      }
      if (sstream.eof())
        std::cout << std::endl;
      continue;
    }
    if (hold_data == ">") {
      break;
    } else {
      if (put_path == "") {
        if (std::filesystem::exists(hold_data))
          std::cout << print_file_data(hold_data) << std::endl;
        else
          std::cout << "cat: " << hold_data << ": No such file or directory"
                    << std::endl;
      } else {
        if (std::filesystem::exists(hold_data)) {
          std::fstream file(put_path, std::ios::app);
          file << print_file_data(hold_data);
        } else {
          std::cout << "cat: " << hold_data << ": No such file or directory"
                    << std::endl;
        }
      }
    }
  }
}

void check_command(std::string input) {
  std::stringstream s_stream(input);
  std::string first, hold = "";
  std::getline(s_stream, first, ' ');
  if (first[0] == '\'' || first[0] == '"') {
    if (first[first.size() - 1] != first[0]) {
      std::getline(s_stream, hold, first[0]);
      first += " " + hold;
    }
    first.erase(0, 1);
  }
  std::string get_string = valid_relative_path(first);
  if ((first == "cat" || first == "ls")) {
    if (first == "cat")
      check_cat(input);
    else
      check_ls(input);
  } else if (get_string != "") {
    if (get_string.find("exe ") != std::string::npos) {
      hold = input.substr(first.size() - 1);
      check_cat(hold);
    } else {
      system(input.c_str());
    }
  } else {
    std::cout << input << ": command not found" << std::endl;
  }
}


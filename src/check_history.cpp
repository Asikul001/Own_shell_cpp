#include "./headers/predefined_header.hpp"
#include "./headers/global_variable.hpp"

//read history function
void read_history(std::string hold_data) {
  std::fstream file(hold_data);
  if (file.is_open()) {
    std::string hold = "";
    while (!file.eof() && std::getline(file, hold)) {
      count_history++;
      history.push_back(hold);
    }
  } else {
    std::cout << "file is not open" << std::endl;
  }
  file.close();
}

// append history
void append_history(std::string hold_data) {
  std::fstream file(hold_data, std::ios::app);
  if (file.is_open()) {
    int hold = count_history;
    for (; count_history < history.size(); count_history++) {
      if (count_history == hold)
        file << history[count_history];
      else
        file << "\n" << history[count_history];
    }
    file << "\n";
  } else
    std::cout << "file is not open\n";
  file.close();
}

// write history function
void write_history(std::string hold_data) {
  std::fstream file(hold_data, std::ios::app);
  if (file.is_open()) {
    for (int i = 0; i < history.size(); i++) {
      if (std::filesystem::file_size(hold_data) == 0)
        file << history[i];
      else
        file << "\n" << history[i];
      file.flush();
    }
    file << "\n";
  } else
    std::cout << "file is not open\n";
  file.close();
}

// check history function
void check_history(std::string input) {
  int count = 0;
  input.erase(0, 7);
  while (input.size() > 0 && input[0] == ' ')
    input.erase(0, 1);
  std::stringstream sstream(input);
  std::string hold_data = "";
  std::getline(sstream, hold_data, ' ');
  int z = input.size();
  if (hold_data == "-r") {
    std::getline(sstream, hold_data, ' ');
    read_history(hold_data);
  } else if (hold_data == "-w") {
    std::getline(sstream, hold_data, ' ');
    write_history(hold_data);
  } else if (hold_data == "-a") {
    std::getline(sstream, hold_data, ' ');
    append_history(hold_data);
  } else {
    if (z > 0) {

      while (input[input.size() - 1] == ' ')
        input.erase(input[input.size() - 1], 1);
      count = std::stoi(input);
      count = history.size() - count;
    }
    for (int i = count; i < history.size(); i++) {
      std::cout << "\t" << i + 1 << " " << history[i] << std::endl;
    }
  }
}
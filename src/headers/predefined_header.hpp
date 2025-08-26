#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <readline/history.h>
#include <readline/readline.h>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <variant>
#include <vector>


#ifndef ENUM_HPP
#define ENUM_HPP
enum class command { echo, type, pwd, exit, cd, history, nothing };
#endif

//function declaration
void check_echo(std::string &);
void append_echo(std::string &);
std::string check_double_code(std::string);
std::string check_single_code(std::string);
std::string remain_string(std::string &);
std::string valid_relative_path(std::string);
void check_type(std::string &);
void check_pwd(void);
void check_history(std::string);
void read_history(std::string);
void write_history(std::string);
void append_history(std::string);
command select_command(std::string);
void check_cd(std::string);
void check_command(std::string);
void check_cat(std::string);
std::string print_file_data(std::string);
void check_ls(std::string);
std::string send_ls_data(std::string,int);
void check_switch(std::string,std::string&);
void check_pipe(std::string &);
int auto_complete(int,int);
int check_match_data(std::vector<std::string>);
int put_data(std::string , std::vector<char *> &,
             std::vector<std::string> &);

command select_command(std::string );
void check_switch(std::string, std::string &);
void entry_point(void);





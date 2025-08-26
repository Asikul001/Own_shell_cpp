cmake_minimum_required(VERSION 3.13)

project(own_shell)

file(GLOB SRC "./src/*.cpp")
set( SOURCE ./main.cpp ${SRC} )
add_executable(own_shell ${SOURCE})



target_link_libraries(own_shell PRIVATE readline)
#!/bin/bash
set -e
 
# directory name
build_name="BUILD"

# cretae build directory
if [[ ! -d $build_name ]]; then
    mkdir $build_name;
fi

# Move into build directory
cd $build_name

# check readline exists or not
if [[ ! -d /usr/include/readline ]];
then
    sudo apt install libreadline-dev

fi

# Run cmake to generate Makefiles
cmake ..
make

# Run the program (optional, adjust executable name)
if [[ -f "./own_shell" ]]; then
    clear;
    echo "Running program..."
    ./own_shell
else
    echo "Build complete. Executable not found in build/."
fi


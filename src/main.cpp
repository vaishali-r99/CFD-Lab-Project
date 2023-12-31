#include <iostream>
#include <string>

#include "Case.hpp"


// soem space
//

int main(int argn, char **args) {

    std::cout << "jbakbf";
    if (argn > 1) {
        std::string file_name{args[1]};
        Case problem(file_name, argn, args);
        problem.simulate();

    } else {
        std::cout << "Error: No input file is provided to fluidchen." << std::endl;
        std::cout << "Example usage: /path/to/fluidchen /path/to/input_data.dat" << std::endl;
    }
}

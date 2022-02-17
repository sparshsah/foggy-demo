/*
you can compile this (printing warnings) by e.g.
$ clang++ {sourcefile_name}.cpp -std=c++2a -Wall -o {outfile_name}.out
*/

#include <iostream>


int main(int argc, char* argv[]) {
    std::string greeting = "Hello world";
    /* for (char* arg : argv) {
        greeting += "and " + str(arg);
    } */
    greeting += "!\n";
    std::cout << greeting;
    return 0;
}

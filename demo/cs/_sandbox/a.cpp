/*
you can compile this (using beta C++20 standard support and printing all warnings) by e.g.
$ clang++ {sourcefile_name}.cpp -std=c++2a -Wall -o {outfile_name}.out
*/

#include <vector>
// #include <format>  // this is gonna be so useful in C++20...
#include <iostream>


int main(int argc, char* argv[]) {
    // don't include the invoked name
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string greeting = "Hello world";
    for (std::string arg : args) {
        greeting += " and " + arg;
    }
    greeting += "!\n";
    std::cout << greeting;
    return 0;
}

/*
you can compile this (using beta C++20 standard support and printing all warnings) by e.g.
$ clang++ -std=gnu++2a -Wall {sourcefile_name}.cpp -o {sourcefile_name}.exe
*/

#include <vector>
// #include <format>  // this is gonna be so useful in C++20...
#include <iostream>


int main(int argc, char* argv[]) {
    // don't include the invoked name
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string greeting = "Hello world";
    for (std::string arg : args) {
        // greeting = std::vformat("{} and {}", greeting, arg);
        greeting += " and " + arg;
    }
    greeting += "!\n";
    std::cout << greeting;
    return 0;
}

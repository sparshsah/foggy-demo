/*
MACHINE ORGANIZATION AND SYSTEMS PROGRAMMING: A LITTLE CHEATSHEET

The goal here is NOT to be an idiomatic example of writing C++ code,
but rather to be a quick-and-dirty self-contained field guide
to help remind you how memory is laid out,
what the lifetime of objects is, etc.

You can compile this (using C++20 standard support and printing all warnings) by e.g.
`clang++ -std=gnu++2a -Wall {sourcefile_name}.cpp -o {sourcefile_name}.exe`.
*/

#include <vector>
// #include <format>  // this is gonna be so useful in C++20...
#include <iostream>


int main(int argc, char* argv[]) {
    // Initialize a vector of strings, using the constructor that takes in an array,
    // and covers `n` elements of it.
    // If we didn't already know the length of the array, we'd have to
    // divide the size of the array by the size of the data type it holds:
    // `n = sizeof(arr) / sizeof(arr[0])`.
    // Don't include the invoked name (`argv[0]`).
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

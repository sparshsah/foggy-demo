/***********************************************************************************************************************
********* MACHINE ORGANIZATION AND SYSTEMS PROGRAMMING: A LITTLE CHEATSHEET ********************************************
***********************************************************************************************************************/
/*
The goal here is NOT to be an idiomatic, efficient, or even correct example of C++ code,
but rather to be a quick-and-dirty self-contained field guide
to help remind you how memory is laid out,
what the lifetime of objects is, etc.
We use C++ simply as a convenient entry point into *NIX machines.
If some of the syntax invokes undefined behavior, my apologies...
but modern compilers are usually quite forgiving when it comes to undefined behavior,
and the underlying idea will still be clear.

You can compile this (using C++20 standard support and printing all warnings) by e.g.
`clang++ -std=gnu++2a -Wall {sourcefile_name}.cpp -o {sourcefile_name}.exe`.
*/

#include <vector>
// #include <format>  // this is gonna be so useful in C++20...
#include <iostream>


// Google's style guide insists that we wrap everything in a namespace
namespace mosp {


// define a type alias
/*
A C-style string is an array of chararacters.
And an array is identified by the pointer to its head element.
In other words, a C-style string "is" just a pointer to a character.

Now, remember that the precondition when you
use a "pointer to a character" as a "C-style string",
is that the array of characters ends with the character `0`,
that is, that the string is null-terminated.
*/
using cstring = char*;
using intArray1 = int[1];

// accept any generic type
template<typename T>
void print(const T& arg, bool cerr = false, bool endl = true) {
    if (cerr) {
        if (endl) {
            // `endl` is better than "\n" because it flushes the stream
            std::cerr << arg << std::endl;
        } else {
            std::cerr << arg;
        }
    } else {
        if (endl) {
            std::cout << arg << std::endl;
        } else {
            std::cout << arg;
        }
    }
}

template<typename T>
void maybe_print(const T& arg, bool cerr = false, bool endl = true, bool whether = true) {
    if (whether) {
        print("arg", cerr, endl);
    }
}

// overload this
void print(bool cerr = false) {
    if (cerr) {
        std::cerr << std::endl;
    } else {
        std::cout << std::endl;
    }
}


/***********************************************************************************************************************
********* HELLO WORLD **************************************************************************************************
***********************************************************************************************************************/

std::string _greet(std::vector<std::string> greetees) {
    std::string greeting = "Hello world";
    for (std::string greetee : greetees) {
        // greeting = std::vformat("{} and {}", greeting, greetee)
        greeting += " and " + greetee;
    }
    greeting += "!";
    return greeting;
}

void greet(std::vector<std::string> greetees) {
    print(_greet(greetees));
}


/***********************************************************************************************************************
********* VALUE, REFERENCE, AND POINTER ********************************************************************************
***********************************************************************************************************************/

char* _showPassByValue(char argv[]) {
    // clunky, and annoying
    // precondition: len(argv) > 0
    argv[0] = 'B';
    return argv;
}

char* _showPassByPtr(char* argv) {
    // still clunky, and even more annoying
    // precondition: len(array pointed to by argv) > 0
    argv[0] = 'C';
    return argv;
}

intArray1& _showPassByRef1(intArray1& argv) {
    // precondition: len(array pointed to by argv) = 1
    argv[0] = 'D';
    return argv;
}

// now this shit is about to get confusing, but it's useful in general
template<size_t N, size_t M>
char(&
    _showPassByRefNM(
        char(& argv )[N]  // reference to N-dimensional char array
    )
)[M] {  // return type: reference to M-dimensional char array
    // precondition: len(array pointed to by argv) > 0
    argv[0] = 'E';
    return argv;
}

template<size_t N>
char _showPassByConstRef(
        const char(& argv )[N],  // non-mutation-allowing reference to (possibly-non-const) N-dimensional char array
        bool noisy = true
    ) {
    try {
        argv[0] = 'F';
    } catch (...) {
        if (noisy) {
            print();
        }
    }
}

void showPassing() {

}


/***********************************************************************************************************************
********* MEMORY LAYOUT AND OBJECT LIFETIME ****************************************************************************
***********************************************************************************************************************/


/***********************************************************************************************************************
********* SMART POINTERS ***********************************************************************************************
***********************************************************************************************************************/


/***********************************************************************************************************************
********* POINTER ALIGNMENT AND STRUCT PADDING *************************************************************************
***********************************************************************************************************************/


/***********************************************************************************************************************
********* POINTER ARITHMETIC *******************************************************************************************
***********************************************************************************************************************/

void showPtrArith(int argc, cstring argv[]) {
    if (argc < 2) {
        print("Please pass at least 2 args!", true);
        throw 1;
    }
    /*
    cstring* ptr_to_head_elt = argv;
    cstring head_elt_gotten_manually = 0;
    print(argc);
    print(argv);
    print(sizeof(argv));
    print(sizeof(ptr_to_head_elt));
    print(ptr_to_head_elt);
    */
}


/***********************************************************************************************************************
********* SIZING *******************************************************************************************************
***********************************************************************************************************************/

size_t _getSzElt(int elt) {
    return sizeof(elt);
}

void showSzElt() {
    print(">>> For a primitive type, sizeof is the same whether you're here or passed.");

    int elt = 314;
    print("Element: " + std::to_string(elt));

    size_t szEltHere = sizeof(elt);
    size_t szEltPassed = _getSzElt(elt);
    print("Size of element, here: " + std::to_string(szEltHere));
    print("Size of element, passed: " + std::to_string(szEltPassed));
}


size_t _getSzArrPassedAsPtr(int* arrPassedAsPtr, bool noisy = true) {
    if (noisy) {
        print(">>> I'm about to calculate the size of this array passed as a pointer: ");
        print(arrPassedAsPtr);
    }
    return sizeof(arrPassedAsPtr);
}

template<int N>
size_t _getSzArrPassedAsRef(
        const int (&arrPassedAsRef)[N],  // ref to N-dimensional int array
        bool noisy = true
    ) {
    if (noisy) {
        print(">>> I'm about to calculate the size of this array passed as a reference: ");
        print(arrPassedAsRef);
    }
    return sizeof(arrPassedAsRef);
}

size_t _getSzArrPassedAsArr(int arrPassedAsArr[], bool noisy = true) {
    if (noisy) {
        print(">>> I'm about to calculate the size of this array passed as an array: ");
        print(arrPassedAsArr);
    }
    return sizeof(arrPassedAsArr);
}

void showSzArr() {
    print(">>> For an array, sizeof needs to be handled very mindfully!");

    int headElt = 314;
    size_t szElt = sizeof(headElt);
    print("Head element: " + std::to_string(headElt));
    print("Size of each element: " + std::to_string(szElt));

    // could also let compiler infer sizeof(arr) with `int arr[] = ...`
    const size_t n = 3;
    int arrAsArr[n] = {headElt, 272, 162};
    int(& arrAsRef )[n] = arrAsArr;  // reference to `n`-dimensional int array
    // notice: we can turn an int[] into an int* no problem... because,
    // and int[] "IS" just the pointer to its head element!
    int* arrAsPtr = arrAsArr;
    print("Array as array, here: ");
    print(arrAsArr);
    print("Array as reference, here: ");
    print(arrAsRef);
    print("Array as pointer, here: ");
    print(arrAsPtr);

    size_t szArrAsArrHere = sizeof(arrAsArr);
    float lenArr = szArrAsArrHere *1./ szElt;
    print("Size of array as array, here: " + std::to_string(szArrAsArrHere));
    print("Hence, length of array (as a float so you know we're not rounding): " + std::to_string(lenArr));
    size_t szArrAsRefHere = sizeof(arrAsRef);
    print("Size of array as reference, here... still works: " + std::to_string(szArrAsRefHere));

    print(">>> BUT... this stops working as soon as you either");
    print(">>> (a) Cast the array to what it truly is, i.e. a pointer to the head element;");
    print(">>> or, equivalently,");
    print(">>> (b) pass the array into a function.");
    print(">>> To wit:");
    //
    size_t szArrAsPtrHere = sizeof(arrAsPtr);
    print("Size of array as pointer, here: " + std::to_string(szArrAsPtrHere));
    //
    size_t szArrPassedAsArr = _getSzArrPassedAsArr(arrAsArr);
    print("Size of array PASSED as array: " + std::to_string(szArrPassedAsArr));
    //
    size_t szArrPassedAsRef = _getSzArrPassedAsRef(arrAsArr);
    print("Size of array PASSED by reference: " + std::to_string(szArrPassedAsRef));
    //
    size_t szArrPassedAsPtr = _getSzArrPassedAsPtr(arrAsPtr);
    print("Size of array PASSED as pointer: " + std::to_string(szArrPassedAsPtr));
    //
    print(">>> We simply get the length of the pointer itself!");
    print(">>> (On a 64bit machine: 64 bits / (8 bits per byte) = 8 bytes.)");
    print(">>> Hence, functions that accept arrays usually also demand to know the LENGTH of the array.");
}


void showSz() {
    showSzElt();
    print();
    showSzArr();
}


/***********************************************************************************************************************
********* CONCURRENCY, THREADS, AND SYNCHRONIZATION ********************************************************************
***********************************************************************************************************************/


}  // mosp namespace end


/***********************************************************************************************************************
********* MAIN *********************************************************************************************************
***********************************************************************************************************************/

int main(int argc, mosp::cstring argv[]) {
    mosp::print("\n>>> Here we go!");

    // the {...} enforces variable scope
    {
        /*
        Initialize a vector of strings, using the constructor that takes in an array,
        and covers `n` elements of it.

        In our case, we DON'T want to include "./mosp.exe" (`argv[0]`),
        so our "array" is `argv+1` (pointer arithmetic!).
        Hence we want to cover the last `argc-1` elements.
        If we didn't already know the length of the array, we'd have to
        divide the size of the array by the size of the data type it holds:
        `n = sizeof(arr) / sizeof(arr[0])`.

        Annoyingly, the actual constructor demands NOT `n` as its second argument,
        but rather a pointer to the last element.
        So in our case, the pointer to the last element is
        argv+1 + (argc-1) = argv + argc.

        By the way, notice how slick that pointer arithmetic was!
        Instead of giving us the memory address `(uint64_t)ptr + n`,
        which is some useless address that probably points straight into the middle
        of one of the array's elements, `ptr + n` gives us the memory address
        `(uint64_t)ptr + sz * n`, where `sz` is the size of each element.
        */
        std::vector<std::string> greetees(argv + 1, argv + argc);
        // it's safe to pass `greetees` because it wont be free'd until the `}` kills this scope
        mosp::greet(greetees);
    }
    mosp::print();

    mosp::showPassing();
    mosp::print();

    mosp::showSz();
    mosp::print();

    mosp::print(">>> All done :) Good luck out there!");
    return 0;
}

/***********************************************************************************************************************
************************************************************************************************************************
********* MACHINE ORGANIZATION AND SYSTEMS PROGRAMMING: A LITTLE CHEATSHEET ********************************************
************************************************************************************************************************
***********************************************************************************************************************/
/*
A quick-and-dirty self-contained field guide to help remind you
how memory is laid out, what the lifetime of objects is, etc.

We use C simply as a convenient entry point into a x86_64 *NIX machine.
The goal here is NOT to be an elegant, modular, idiomatic, efficient, or even correct example of C code.
If some of the syntax invokes undefined behavior, my apologies...
but modern compilers are usually quite forgiving when it comes to undefined behavior,
so the underlying idea should still be clear.

You can compile this e.g. (printing all warnings) with `clang -Wall mosp.c -o mosp.exe`,
then run it with `./mosp.exe`.
*/


/***********************************************************************************************************************
********* ARCANE INCANTATIONS ******************************************************************************************
***********************************************************************************************************************/

#include <sys/types.h>
#include <string.h>
#include <stdio.h>

// in C++, you could use `template<typename T>` to represent a generic type
typedef void T;
typedef T* ptr_t;
typedef char* char_ptr;
typedef char_ptr char_arr;
// CAUTION: if you want to use this "as" a C-style string, then you MUST null-terminate!
typedef char_arr cstring;

const size_t MAX_LINE_LEN = 120;
// if you're typing out a string over multiple lines, reconsider...
const size_t _MAX_STR_LEN = MAX_LINE_LEN;
const size_t MAX_STR_LEN = _MAX_STR_LEN + 1;

const size_t _DIV_LEN = MAX_LINE_LEN;
const size_t DIV_LEN = _DIV_LEN + 1;  // leave a byte of space to null-terminate
const char DIV_C = '=';

// unused non-static globals are fine, since they might be used outside this file...
// but compiler will warn about unused static variables, since they are unusable outside this file!
static const char INIT_STATIC_GLOBAL_CONST_CHAR = 'A';
static char INIT_STATIC_GLOBAL_CHAR = 'B';
const char INIT_GLOBAL_CONST_CHAR = 'C';
char INIT_GLOBAL_CHAR = 'D';
static const char UNINIT_STATIC_GLOBAL_CONST_CHAR;
static char UNINIT_STATIC_GLOBAL_CHAR;
// this is silly, since const's can be assigned a value only at initialization...
const char UNINIT_GLOBAL_CONST_CHAR;
char UNINIT_GLOBAL_CHAR;

ptr_t getAddrOfParamVal(char c) {
    ptr_t addr = &c;
    return addr;
}

char getValOfParamVal(char c) {
    return c;
}

ptr_t getAddrOfParamPtr(char_ptr c) {
    ptr_t addr = &c;
    return addr;
}

char_ptr getValOfParamPtr(char_ptr c) {
    return c;
}

char getTgtOfParamPtr(char_ptr c) {
    char v = *c;
    return v;
}


void printDiv() {
    // in C++, thanks to default args, we could have parametrized `n` and `d`,
    // while still retaining the convenience of an arg-less call
    char div[DIV_LEN];
    for (int i = 0; i < sizeof(div); i++) {
        div[i] = DIV_C;
    }
    div[sizeof(div) - 1] = '\0';  // null-terminate
    printf("%s\n", div);
}


/***********************************************************************************************************************
********* VALUE, POINTER, AND REFERENCE ********************************************************************************
***********************************************************************************************************************/

char* _showPassByVal(char argv[]) {
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

// in C++, we'd also have the option to pass by reference


void showPassing() {
    print(">>> No matter how you pass an array, it is mutable!");
    const char a = 'A';
    print("Original element: ");
    print(a);
    const size_t n = 1;

    print(">>> Now, we'll show the element from the \"original\" and \"returned\" arrays, once the function has run");
    //
    char arrForVal[n] = {a};
    char* arrFromVal = _showPassByVal(arrForVal);
    print(">>> Passed by value:");
    char eltForVal = arrForVal[0];
    print(eltForVal);
    char eltFromVal = arrFromVal[0];
    print(eltFromVal);
    //
    char arrForPtr[n] = {a};
    char* arrFromPtr = _showPassByPtr(arrForPtr);
    print(">>> Passed by pointer:");
    char eltForPtr = arrForPtr[0];
    print(eltForPtr);
    char eltFromPtr = arrFromPtr[0];
    print(eltFromPtr);
}


/***********************************************************************************************************************
********* (VIRTUAL) MEMORY LAYOUT AND OBJECT LIFETIME ******************************************************************
***********************************************************************************************************************/

/* For an x86_64 *NIX machine:

[------------------------------------------------------------*
0xFFFFFFFF: "High addresses"                                 |
·                                                            |
·                                                            |
·                                                            |
----------- KERNEL SPACE ------------------------------------↑
----------- USER   SPACE ------------------------------------↓
                               HEAP                          |
                               ↓                             |
                               ↓                             |
                               ↓                             |
                               -------------------------------
                               ···                           |
                               UNALLOCATED MEMORY            |
                               ···                           |
                               -------------------------------
                               ↑                             |
                               ↑                             |
                               ↑                             |
                               STACK                         |
                               -------------------------------
                               ···                           |
                               UNINITIALIZED GLOBALS ("BSS") |
                               -------------------------------
                               ···                           |
                               INITIALIZED GLOBALS ("DATA")  |
                               -------------------------------
                               ···                           |
                               CODE ("TEXT")                 |
                               -------------------------------
0x00000000: "Low addresses" :  NULL                          |
[------------------------------------------------------------*

*/

void showMemLayout() {
    void* nullPtr = NULL;
    print(">>> Address of `NULL`, the null pointer");
    print(">>> ... Notice I said THE null pointer, meaning that EVERY null pointer IS exactly this:");
    print(nullPtr);
    //
    const int* ptr_staticGlobalConstInitInt = &staticGlobalConstInitInt;
    print(">>> Address of static global constant initialized int:");
    print(ptr_staticGlobalConstInitInt);
    //
    const int* ptr_staticGlobalInitInt = &staticGlobalInitInt;
    const int* ptr_globalConstInitInt = &globalConstInitInt;
    const int* ptr_globalInitInt = &globalInitInt;
    const int* ptr_staticGlobalUninitInt = &staticGlobalUninitInt;
    const int* ptr_globalUninitInt = &globalUninitInt;
}


/***********************************************************************************************************************
********* SMART POINTERS ***********************************************************************************************
***********************************************************************************************************************/

// TODO(sparshsah)


/***********************************************************************************************************************
********* POINTER ALIGNMENT AND STRUCT PADDING *************************************************************************
***********************************************************************************************************************/

// TODO(sparshsah)


/***********************************************************************************************************************
********* POINTER ARITHMETIC *******************************************************************************************
***********************************************************************************************************************/

// TODO(sparshsah


/***********************************************************************************************************************
********* SIZING *******************************************************************************************************
***********************************************************************************************************************/


/***********************************************************************************************************************
********* CONCURRENCY, THREADS, AND SYNCHRONIZATION ********************************************************************
***********************************************************************************************************************/

// TODO(sparshsah)


/***********************************************************************************************************************
********* MAIN *********************************************************************************************************
***********************************************************************************************************************/



size_t _getSzElt(int elt) {
    return sizeof(elt);
}

void showSzElt() {
    print(">>> For a primitive type, sizeof is the same whether you're here or passed.");

    int elt = 42;
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
    // notice: we can turn an int[] into an int* no problem... because,
    // and int[] "IS" just the pointer to its head element!
    int* arrAsPtr = arrAsArr;
    print(">>> Array as array, here: ");
    print(arrAsArr);
    print(">>> Array as reference, here: ");
    print(arrAsRef);
    print(">>> Array as pointer, here: ");
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


int main() {
    printf("\n");
    printDiv();
    printf("# Hello world!\n");

    printf("# Good luck out there!\n");
    printDiv();

    // silence unused-variable warnings
    (T) INIT_STATIC_GLOBAL_CONST_CHAR;
    (T) INIT_STATIC_GLOBAL_CHAR;
    (T) UNINIT_STATIC_GLOBAL_CONST_CHAR;
    (T) UNINIT_STATIC_GLOBAL_CHAR;
    return 0;
}

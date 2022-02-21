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
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// in C++, you could use `template<typename T>` to represent a generic type
typedef void T;
typedef T* ptr_t;
// just to make it painfully explicit when a char* is actually pointing to a char ARRAY
typedef char* char_arr;
typedef int* int_arr;
// CAUTION: if you want to use this "as" a C-style string, then you MUST null-terminate!
typedef char_arr _null_terminated_char_arr;
typedef _null_terminated_char_arr cstring;

typedef struct CharHolder {
    char c;
    bool full;
} CharHolder;

const size_t MAX_LINE_LEN = 120;
// if you're typing out a string over multiple lines, reconsider...
const size_t _MAX_STR_LEN = MAX_LINE_LEN;
const size_t MAX_STR_LEN = _MAX_STR_LEN + 1;

const size_t _DIV_LEN = MAX_LINE_LEN;
const size_t DIV_LEN = _DIV_LEN + 1;  // leave a byte of space to null-terminate
const char DIV_C = '=';
const char SUBDIV_C = '-';

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

ptr_t getAddrOfParamPtr(char* c) {
    ptr_t addr = &c;
    return addr;
}

char* getValOfParamPtr(char* c) {
    return c;
}

char getTgtOfParamPtr(char* c) {
    char v = *c;
    return v;
}


void printDiv() {
    // in C++, thanks to default args, we could have parametrized `len` and `c`,
    // while still retaining the convenience of an arg-less call
    char _div[DIV_LEN];
    for (int i = 0; i < sizeof(_div); i++) {
        _div[i] = DIV_C;
    }
    _div[sizeof(_div) - 1] = '\0';  // null-terminate
    cstring div = _div;
    printf("%s\n", div);
}

void printSubDiv() {
    char _div[DIV_LEN];
    for (int i = 0; i < sizeof(_div); i++) {
        _div[i] = SUBDIV_C;
    }
    _div[0] = '\n';
    _div[sizeof(_div) - 2] = '\n';
    _div[sizeof(_div) - 1] = '\0';  // null-terminate
    cstring div = _div;
    printf("%s\n", div);
}


/***********************************************************************************************************************
********* POINTER, VALUE, AND REFERENCE ********************************************************************************
***********************************************************************************************************************/

CharHolder* _showPassByPtr(CharHolder* c) {
    printf("    Explicit address of parameter object, INSIDE function:\t\t`%p`\n", c);
    c->c = 'B';  // syntactic sugar for `(*c).c = 'C';`
    printf("    Explicit address of output object, INSIDE function:\t\t\t`%p`\n", c);
    return c;
}

CharHolder _showPassByVal(CharHolder c) {
    printf("    Implicit address of parameter object, INSIDE function:\t\t`%p`\n", &c);
    c.c = 'b';
    printf("    Implicit address of output object, INSIDE function:\t\t\t`%p`\n", &c);
    return c;
}

// in C++, we'd additionally have the option to pass by reference, sorta the best of both worlds


void showPassing() {
    printf(">>> Let's play with passing by value vs pointer.\n");
    printf("\n");

    const char _c = 'A';
    printf("    Original element:\t\t\t\t\t\t\t'%c'\n", _c);

    printf("\n");

    printf(">>> When you pass an object by pointer, it can be mutated:\n");
    CharHolder _cp = { .c = _c, .full = true };
    CharHolder* cp = &_cp;
    printf("    Explicit address of input object, pre-passing:\t\t\t`%p`\n", cp);
    printf("    Element from input object, pre-passing:\t\t\t\t'%c'\n", cp->c);
    CharHolder* cp_ = _showPassByPtr(cp);
    printf("    Explicit address of \"input\" object, having been passed by pointer:\t`%p`\n", cp);
    printf("    Element from \"input\" object, having been passed by pointer:\t\t'%c'\n", cp->c);
    printf("    Explicit address of \"output\" object:\t\t\t\t`%p`\n", cp_);
    printf("    Element from \"output\" object:\t\t\t\t\t'%c'\n", cp_->c);

    printf("\n");

    printf(">>> When you pass an object by value,\n");
    printf(">>> at the space+time cost of pass-time copying,\n");
    printf(">>> it can't be mutated:\n");
    CharHolder cv = { .c = _c, .full = true };
    printf("    Implicit address of input object, pre-passing:\t\t\t`%p`\n", &cv);
    CharHolder cv_ = _showPassByVal(cv);
    printf("    Implicit address of \"input\" object, having been passed by value:\t`%p`\n", &cv);
    printf("    Element from \"input\" object, having been passed by value:\t\t'%c'\n", cv.c);
    printf("    Implicit address of \"output\" object:\t\t\t\t`%p`\n", &cv_);
    printf("    Element from \"output\" object:\t\t\t\t\t'%c'\n", cv_.c);

    printf("\n");

    printf(">>> ASIDE: Here's a silly anecdote, that happens to\n");
    printf(">>> illustrate a couple useful things about C's memory management.\n");
    printf(">>> I had originally (naively) thought that,\n");
    printf(">>> for the sake of illustration,\n");
    printf(">>> I had been willing to invoke undefined behavior.\n");
    printf(">>> A parameter stack variable created inside\n");
    printf(">>> a called function has automatic lifetime, hence\n");
    printf(">>> the memory allocated for it is free'd\n");
    printf(">>> as soon as the function return's.\n");
    printf(">>> Indeed, the called function's entire stackframe is \"gone\".\n");
    printf(">>> However, I'm running a very linear single-thread process,\n");
    printf(">>> so the chance that the memory has been overwritten is slim.\n");
    printf(">>> The memory is not safe to access,\n");
    printf(">>> but if I insist on accessing it,\n");
    printf(">>> it will probably still contain what it used to contain\n");
    printf(">>> just before the called function return'ed.\n");
    printf(">>> Or so I thought... it turns out, returning a struct in C\n");
    printf(">>> is actually no more dangerous than\n");
    printf(">>> returning a primitive int!\n");
    printf(">>> To wit, notice that the address of the output struct\n");
    printf(">>> inside the called function (which was the same as the address\n");
    printf(">>> of the parameter struct inside the called function,\n");
    printf(">>> since the input struct passed by value had been\n");
    printf(">>> copied into the highest address\n");
    printf(">>> of the called function's stackframe)\n");
    printf(">>> is different, in particular lower, than\n");
    printf(">>> the address of the \"output\" struct once returned!\n");
    printf(">>> When the called function return'ed,\n");
    printf(">>> the struct it was return'ing was copied onto\n");
    printf(">>> the calling function's stackframe\n");
    printf(">>> (and indeed, as expected, copied into a lower address\n");
    printf(">>> than the local stack variables created by\n");
    printf(">>> the calling function before it called the called function.\n");
    printf(">>> So: Very space+time expensive, but also very convenient!\n");
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
    printf(">>> Let's play with memory layout.\n");
    printf("\n");

    ptr_t nullPtr = NULL;
    printf(">>> ... Notice I will say THE null pointer, meaning that ANY null pointer is located exactly there!\n");
    printf("Address OF the null pointer, `NULL`: `%p`\n", &nullPtr);
    printf("Address STORED IN the null pointer, i.e. located at the address just above: `%p`\n", nullPtr);
    printf("Value POINTED TO BY the null pointer, i.e. located at the address just above:\n");
    printf(">>> ... I didn't get you, did I? NEVER follow the null pointer!\n");
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
/*
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
*/

/***********************************************************************************************************************
********* CONCURRENCY, THREADS, AND SYNCHRONIZATION ********************************************************************
***********************************************************************************************************************/

// TODO(sparshsah)


/***********************************************************************************************************************
********* MAIN *********************************************************************************************************
***********************************************************************************************************************/

int main() {
    printf("\n\n");
    printDiv();
    printf(">>> Hello world!\n");

    printSubDiv();

    showPassing();

    printSubDiv();

    showMemLayout();

    printSubDiv();

    printf(">>> Good luck out there!\n");
    printDiv();
    printf("\n\n");

    // silence unused-variable warnings
    (T) INIT_STATIC_GLOBAL_CONST_CHAR;
    (T) INIT_STATIC_GLOBAL_CHAR;
    (T) UNINIT_STATIC_GLOBAL_CONST_CHAR;
    (T) UNINIT_STATIC_GLOBAL_CHAR;
    return 0;
}

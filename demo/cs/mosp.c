/***********************************************************************************************************************
********* MACHINE ORGANIZATION AND SYSTEMS PROGRAMMING: A LITTLE CHEATSHEET ********************************************
***********************************************************************************************************************/
/*
This is a quick-and-dirty self-contained field guide to help remind you
how memory is laid out, what the lifetime of objects is, etc.

We use C simply as a convenient entry point into x86_64 *NIX machines.
The goal here is NOT to be an elegant, modular, idiomatic, efficient, or even correct example of C code.
If some of the syntax invokes undefined behavior, my apologies...
but modern compilers are usually quite forgiving when it comes to undefined behavior,
so the underlying idea should still be clear.

You can compile this e.g. (printing all warnings) with `clang -Wall mosp.c -o mosp.exe`,
then run it with `./mosp.exe`.
*/

#include <sys/types.h>
#include <string.h>
#include <stdio.h>

typedef void T;
typedef T* ptr_t;
typedef char* char_ptr;
typedef char_ptr char_arr;
// CAUTION: if you want to use this "as" a C-style string, then you MUST null-terminate!
typedef char_arr cstring;

const size_t MAX_LINE_LEN = 120;

// 120 is the line-length limit, so it should be plenty enough for a string...
// long enough to be ample, short enough to be efficient
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
const char UNINIT_GLOBAL_CONST_CHAR ;
char UNINIT_GLOBAL_CHAR;

ptr_t getAddrOfParam(char c) {
    ptr_t addr = &c;
    return addr;
}

ptr_t getAddrOfParamPtr(char_ptr c) {
    ptr_t addr = &c;
    return addr;
}

char getValPointedToByParamPtr(char_ptr c) {
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

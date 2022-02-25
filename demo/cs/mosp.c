/***********************************************************************************************************************
************************************************************************************************************************
********* MACHINE ORGANIZATION AND SYSTEMS PROGRAMMING: A LITTLE FIELD GUIDE *******************************************
************************************************************************************************************************
***********************************************************************************************************************/
/*
A quick-and-dirty self-contained cheatsheet to help remind you
how memory is laid out, what the lifetime of objects is, etc.

You can compile this e.g. (printing all warnings) with `clang -Wall mosp.c -o mosp.exe`,
then run it with `./mosp.exe`.
*/


/***********************************************************************************************************************
********* ARCANE INCANTATIONS ******************************************************************************************
***********************************************************************************************************************/

// feel free to ignore this setup code... the goal here isn't to learn C boilerplate

#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// in C++, you could use `template<typename T>` to represent a generic type
typedef void T;
typedef T* ptr_t;
// just to make it painfully explicit when a char* is actually pointing to the head element of a char ARRAY
typedef char* char_arr;
typedef int* int_arr;
// CAUTION: if you want to use this "as" a C-style string, then you MUST null-terminate!
// this named type is simply a reminder, and does NOT enforce that condition!
typedef char_arr _null_terminated_char_arr;
typedef _null_terminated_char_arr cstring;

typedef struct S {
    int i1;
    size_t sz;
    int i2;
} S;
typedef struct CompactS {
    int i1;
    int i2;
    size_t sz;
} CompactS;

typedef struct CharHolder {
    char c;
    size_t numTimesChanged;
} CharHolder;


const size_t MAX_LINE_LEN = 120;
// if you're typing out a string over multiple lines, reconsider...
const size_t _MAX_STR_LEN = MAX_LINE_LEN;
const size_t MAX_STR_SZ = _MAX_STR_LEN +1;  // add a byte of space to null-terminate

const cstring HEADER_HEAD = "//#  ";
const cstring SUBHEADER_HEAD = HEADER_HEAD;
const char HEADLINE_C = '-';
const size_t _DIV_LEN = MAX_LINE_LEN;
const size_t DIV_SZ = _DIV_LEN +1;
const char DIV_C = '=';
const char SUBDIV_C = '~';
const cstring COMMENT_HEAD = "//* ";

// unused non-static globals are fine, since they might be used outside this file...
// but compiler will warn about unused static variables, since they are unusable outside this file!
static const char INIT_STATIC_GLOBAL_CONST_CHAR = 'A';
static char INIT_STATIC_GLOBAL_CHAR = 'B';
const char INIT_GLOBAL_CONST_CHAR = 'C';
char INIT_GLOBAL_CHAR = 'D';
// this is silly, since const's can be assigned a value only at initialization... but OK
static const char UNINIT_STATIC_GLOBAL_CONST_CHAR;
static char UNINIT_STATIC_GLOBAL_CHAR;
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


void _printDiv(size_t sz, const char c, bool skip_before, bool skip_after) {
    char _div[sz];
    for (int i = 0; i < sizeof(_div); i++) {
        _div[i] = c;
    }
    if (skip_before) {
        _div[0] = '\n';
    }
    if (skip_after) {
        _div[sizeof(_div) -2] = '\n';
    }
    _div[sizeof(_div) -1] = '\0';  // null-terminate
    cstring div = _div;  // not necessary, just to be explicit
    printf("%s\n", div);
}

void printDiv(bool skip_before, bool skip_after) {
    _printDiv(DIV_SZ, DIV_C, skip_before, skip_after);
}

void printSubDiv() {
    _printDiv(DIV_SZ, SUBDIV_C, true, true);
}

void _printHeader(const cstring header, const cstring head) {
    const size_t sz = strlen(head) + strlen(header) +1;
    char headline[sz];
    for (int i = 0; i < sizeof(headline); i++) {
        headline[i] = HEADLINE_C;
    }
    headline[sizeof(headline) -1] = '\0';

    printf("%s%s\n%s\n\n", head, header, headline);
}

void printHeader(const cstring header) {
    _printHeader(header, HEADER_HEAD);
}

void printSubHeader(const cstring subheader) {
    char subheader_[strlen(subheader) +1 +1];
    strcpy(subheader_, subheader);
    subheader_[sizeof(subheader_) -2] = ':';
    subheader_[sizeof(subheader_) -1] = '\0';

    printSubDiv();
    _printHeader(subheader_, SUBHEADER_HEAD);
}

void printComment(const cstring comment) {
    printf("%s%s\n", COMMENT_HEAD, comment);
}


/***********************************************************************************************************************
********* POINTER, VALUE, AND REFERENCE ********************************************************************************
***********************************************************************************************************************/

CharHolder* _demoPassByPtr(CharHolder* c, ptr_t* paramAddr, ptr_t* returnAddr) {
    *paramAddr = c;
    c->c = 'B';  // syntactic sugar for `(*c).c = 'B';`
    *returnAddr = c;
    return c;
}

CharHolder _demoPassByVal(CharHolder c, ptr_t* paramAddr, ptr_t* returnAddr) {
    *paramAddr = &c;
    c.c = 'b';
    *returnAddr = &c;
    return c;
}

// in C++, we'd additionally have the option to pass by reference, sorta the best of both worlds


char_arr _demoPassByValFail(char_arr arr, ptr_t* paramAddr, ptr_t* returnAddr) {
    // precondition: sz(arr) > 0
    *paramAddr = arr;
    arr[0] = 'C';
    *returnAddr = arr;
    return arr;
}


void showPassing() {
    printSubHeader("Let's examine passing by value vs pointer");

    const char _c = 'A';
    printf("\
    Original element:················································································'%c'\n",
    _c);

    printf("\n");

    printComment("When you pass an object by pointer, it can be mutated:");
    CharHolder _cp = { .c = _c, .numTimesChanged = 1 };
    CharHolder* cp = &_cp;
    printComment("Notice that all these addresses are the same!");
    //
    printf("\
    Explicit address of input object, pre-passing:···················································`%p`\n",
    cp);
    //
    printf("\
    Element from input object, pre-passing:··························································'%c'\n",
    cp->c);
    //
    ptr_t paramAddrP = NULL;
    ptr_t returnAddrP = NULL;
    CharHolder* cp_ = _demoPassByPtr(cp, &paramAddrP, &returnAddrP);
    //
    printf("\
    Explicit address of parameter object, INSIDE function:···········································`%p`\n",
    paramAddrP);
    //
    printf("\
    Explicit address of output object, INSIDE function:··············································`%p`\n",
    returnAddrP);
    //
    printf("\
    Explicit address of \"input\" object, having been passed by pointer:·······························`%p`\n",
    cp);
    //
    printf("\
    Element from \"input\" object, having been passed by pointer:······································'%c'\n",
    cp->c);
    //
    printf("\
    Explicit address of \"output\" object:·····························································`%p`\n",
    cp_);
    //
    printf("\
    Element from \"output\" object:····································································'%c'\n",
    cp_->c);

    printf("\n");

    printComment("When you pass an object by value, at space+time cost of copying, it can't be mutated:");
    CharHolder cv = { .c = _c, .numTimesChanged = 1 };
    //
    printf("\
    Implicit address of input object, pre-passing:···················································`%p`\n",
    &cv);
    //
    printf("\
    Element from input object, pre-passing:··························································'%c'\n",
    cv.c);
    //
    ptr_t paramAddrV = NULL;
    ptr_t returnAddrV = NULL;
    CharHolder cv_ = _demoPassByVal(cv, &paramAddrV, &returnAddrV);
    printComment("Notice that the arg value has been COPIED into a new param variable");
    printComment("at the top of the called function's stackframe,");
    printComment("which is as expected lower than this function's stackframe:");
    //
    printf("\
    Implicit address of parameter object, INSIDE function:···········································`%p`\n",
    paramAddrV);
    //
    printf("\
    Implicit address of output object, INSIDE function:··············································`%p`\n",
    returnAddrV);
    //
    printf("\
    Implicit address of \"input\" object, having been passed by value:·································`%p`\n",
    &cv);
    //
    printf("\
    Element from \"input\" object, having been passed by value:········································'%c'\n",
    cv.c);
    //
    printComment("Notice that the return value has been COPIED into a new local variable");
    printComment("in the middle of this function's stackframe,");
    printComment("which is as expected lower than this function's previously-allocated local variable,");
    printComment("but higher than the called function's stackframe:");
    //
    printf("\
    Implicit address of \"output\" object:·····························································`%p`\n",
    &cv_);
    //
    printf("\
    Element from \"output\" object:····································································'%c'\n",
    cv_.c);

    printf("\n");

    printComment("BUT this breaks down for arrays passed by value... because remember,");
    printComment("the \"value\" of an array IS a pointer to its head element!");
    char c[1] = {_c};
    //
    printf("\
    Explicit address of input object, pre-passing:···················································`%p`\n",
    c);
    //
    printf("\
    Element from input object, pre-passing:··························································'%c'\n",
    c[0]);
    //
    ptr_t paramAddr = NULL;
    ptr_t returnAddr = NULL;
    char_arr c_ = _demoPassByValFail(c, &paramAddr, &returnAddr);
    //
    printf("\
    Implicit address of parameter object, INSIDE function:···········································`%p`\n",
    paramAddr);
    //
    printf("\
    Implicit address of output object, INSIDE function:··············································`%p`\n",
    returnAddr);
    //
    printf("\
    Implicit address of \"input\" object, having been passed by value:·································`%p`\n",
    c);
    //
    printf("\
    Element from \"input\" object, having been passed by value:········································'%c'\n",
    c[0]);
    //
    printf("\
    Implicit address of \"output\" object:·····························································`%p`\n",
    c_);
    //
    printf("\
    Element from \"output\" object:····································································'%c'\n",
    c_[0]);
}


/***********************************************************************************************************************
********* (VIRTUAL) MEMORY LAYOUT AND OBJECT LIFETIME ******************************************************************
***********************************************************************************************************************/

/* For an x86 *NIX machine:

[------------------------------------------------------------\
0xFFFFFFFF: "High addresses"                                 |
·                                                            |
·                                                            |
·                                                            |
----------- KERNEL SPACE ------------------------------------↑
----------- USER   SPACE ------------------------------------↓
                               STACK                         |
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
                               HEAP                          |
                               -------------------------------
                               ···                           |
                               "BSS" (UNINITIALIZED GLOBALS) |
                               -------------------------------
                               ···                           |
                               "DATA" (INITIALIZED GLOBALS)  |
                               -------------------------------
                               ···                           |
                               "TEXT" (CODE)                 |
                               -------------------------------
0x00000000: "Low addresses" :  NULL                          |
[------------------------------------------------------------/

*/

void showMemLayout() {
    printSubHeader("Let's examine memory layout");

    printComment("Kernel space: Highest addresses (above user space)");
    printf("\n");

    printComment("Stack: Automatically-allocated, automatic-lifetime param and/or local variables");
    printComment("High addresses, growing downward");
    printf("\n");
    //
    char d0[1];
    char d1[1];
    char d2[1];
    printf("\
    Address of my 1st local char array:······························································`%p`\n",
    d0);
    printf("\
    Address of my 2nd local char array:······························································`%p`\n",
    d1);
    printf("\
    Address of my 3rd local char array:······························································`%p`\n",
    d2);
    // no need to free, they are automatic-lifetime!
    printf("\n");

    printComment("Heap: Dynamically-allocated, dynamic-lifetime variables");
    printComment("Mid addresses, growing upward");
    printf("\n");
    //
    char_arr c0 = (char*)calloc(1, sizeof(char));
    char_arr c1 = (char*)calloc(1, sizeof(char));
    char_arr c2 = (char*)calloc(1, sizeof(char));
    // remember, the value of an array IS the pointer to its head element!
    printf("\
    Address of my 3rd calloc'ed char array:··························································`%p`\n",
    c2);
    printf("\
    Address of my 2nd calloc'ed char array:··························································`%p`\n",
    c1);
    printf("\
    Address of my 1st calloc'ed char array:··························································`%p`\n",
    c0);
    // don't leak memory!
    free(c2);
    free(c1);
    free(c0);
    printf("\n");

    printComment("BSS: Static-lifetime, uninitialized globals");
    printComment("Low addresses");
    printf("\n");
    //
    printf("\
    Address OF an uninitialized global char:·························································`%p`\n",
    &UNINIT_GLOBAL_CHAR);
    printf("\n");
    printf("\
    Address OF an uninitialized static global char:··················································`%p`\n",
    &UNINIT_STATIC_GLOBAL_CHAR);
    printf("\n");
    printf("\
    Address OF an uninitialized global constant char:················································`%p`\n",
    &UNINIT_GLOBAL_CONST_CHAR);
    printf("\n");
    printf("\
    Address OF an uninitialized static global constant char:·········································`%p`\n",
    &UNINIT_STATIC_GLOBAL_CONST_CHAR);
    printf("\n");

    printComment("Data: Static-lifetime, initialized globals");
    printComment("Very low addresses");
    printf("\n");
    //
    printf("\
    Address OF an initialized global char:···························································`%p`\n",
    &INIT_GLOBAL_CHAR);
    printf("\
    Value STORED IN that variable, i.e. value located at the address just above:·····················`%c`\n",
    INIT_GLOBAL_CHAR);
    printf("\n");
    //
    printf("\
    Address OF an initialized global constant char:··················································`%p`\n",
    &INIT_GLOBAL_CONST_CHAR);
    printf("\
    Value STORED IN that variable, i.e. value located at the address just above:·····················`%c`\n",
    INIT_GLOBAL_CONST_CHAR);
    printf("\n");
    //
    printf("\
    Address OF an initialized static global char:····················································`%p`\n",
    &INIT_STATIC_GLOBAL_CHAR);
    printf("\
    Value STORED IN that variable, i.e. value located at the address just above:·····················`%c`\n",
    INIT_STATIC_GLOBAL_CHAR);
    printf("\n");
    //
    printf("\
    Address OF an initialized static global constant char:···········································`%p`\n",
    &INIT_STATIC_GLOBAL_CONST_CHAR);
    printf("\
    Value STORED IN that variable, i.e. value located at the address just above:·····················`%c`\n",
    INIT_STATIC_GLOBAL_CONST_CHAR);
    printf("\n");

    printComment("Text (Code): Lowest addresses");
    printf("\n");

    printComment("\"Null\" is a name for the very lowest address: `0x0`,");
    printComment("and `NULL` (the null pointer, AKA `(void*)0`), points there.");
    printComment("A pointer that wants to be literally nothing must settle for being `NULL` (all 0's).");
    printComment("Following the null pointer (dereferencing `NULL`) invokes undefined behavior.");
    printComment("Null is like the black hole at the center of the Milky Way:");
    printComment("You don't know what's in there, and it could be nasal demons.");
    printf("\
    Value of `NULL`:·················································································`%p`\n",
    NULL);
}


/***********************************************************************************************************************
********* SMART POINTERS ***********************************************************************************************
***********************************************************************************************************************/

// TODO(sparshsah)


/***********************************************************************************************************************
********* POINTER ALIGNMENT AND STRUCT PADDING *************************************************************************
***********************************************************************************************************************/

void _showPtrAlign() {
    printComment("Because it's easier to load a single word at a time,");
    printComment("the OS dislikes an object that spans multiple words.");
    printComment("Therefore, in order to make reading/writing the value easier,");
    printComment("the OS will allocate an address to it that is a neat multiple of its size.");
    printComment("That way, it can minimize instance where it must load multiple words");
    printComment("simply to read or write a single value");
}

void _showStructPad() {
    size_t sz = sizeof(S);
    size_t compactSz = sizeof(CompactS);

    printComment("Here's an example of a wasteful struct `S`:");
    printComment("{ int (4 bytes), size_t (8 bytes), int (4 bytes) },");
    printComment("which will be laid out in memory as");
    printComment("········ iiii____ uuuuuuuu iiii____ ········,");
    printComment("requiring 4 bytes of padding in the middle and at the end,");
    printComment("ending up spanning 3 full words.");
    printf("\
    To wit, its size:················································································`%lu`\n",
    sz);

    printf("\n");

    printComment("Here's an example of a more mindfule struct `CompactS`:");
    printComment("{ int (4 bytes), int (4 bytes), size_t (8 bytes) },");
    printComment("which will be laid out in memory as");
    printComment("········ iiiiiiii uuuuuuuu ········,");
    printComment("requiring no padding,");
    printComment("ending up spanning only 2 fully-used words.");
    printf("\
    To wit, its size:················································································`%lu`\n",
    compactSz);

    printf("\n");

    // this is not the order the struct members were defined, but that's OK!
    CompactS convenient = { .i1 = 42, .sz = 43, .i2 = 44 };
    // silence unused variable warning
    (void) convenient;
    printComment("And don't worry: For convenience, you can initialize struct members in any order;");
    printComment("So, it's still perfectly fine to initialize a `CompactS` as");
    printComment("`{ .i1 = 42, .sz = 43, .i2 = 44 }` if that's a logical order for you.");
}

void showPtrAlign() {
    printSubHeader("Let's examine pointer alignment");
    _showPtrAlign();
    printf("\n");
    _showStructPad();
}


/***********************************************************************************************************************
********* POINTER ARITHMETIC *******************************************************************************************
***********************************************************************************************************************/

void showPtrArith() {
    printSubHeader("Let's examine pointer arithmetic");

    int arr[2] = {42, 43};
    int* p0 = arr;
    int* p1 = p0 +1;
    unsigned long p0AsNumIncr = (unsigned long)p0 +1;

    printf("\
    We have an array at address `p = %p`, which in decimal is····························`%lu`\n",
    arr, (unsigned long)arr);
    printf("\
    Accessed by index, the array is··································································`{%i, %i}`\n",
    arr[0], arr[1]);

    printf("\n");

    printf("\
    The ptr to the head elt is of course again `p0 = %p`, which in decimal is again······`%lu`\n",
    p0, (unsigned long)p0);
    printf("\
    And following that pointer yields as expected····················································`%i`\n",
    *p0);

    printf("\n");

    printf("\
    The ptr to the succeeding elt can be gotten as `p0 +1`, which in decimal is······················`%lu`\n",
    (unsigned long)p1);
    printf("\
    And following that pointer yields as expected····················································`%i`\n",
    *p1);

    printf("\n");

    printComment("How slick was that?");
    printf("\
    You might expect `p0 +1` to be equivalent to `(lu)p0 +1`, i.e.···································`%lu`\n",
    p0AsNumIncr);
    printComment("But the C compiler knows that if you're incrementing a T*,");
    printComment("then the T* is probably a pointer to a T array, therefore it servicefully");
    printComment("increments the numerical value of the pointer by `sizeof(T)`.");
}


/***********************************************************************************************************************
********* SIZING *******************************************************************************************************
***********************************************************************************************************************/
/*
size_t _getSzElt(int elt) {
    return sizeof(elt);
}

void _showSzElt() {
    printComment("For a primitive type, sizeof is the same whether you're here or passed:");

    int elt = 42;
    printf("Element: %i\n", elt);

    size_t szEltHere = sizeof(elt);
    size_t szEltPassed = _getSzElt(elt);
    printf("Size of element, here: %u\n" + szEltHere);
    printf("Size of element, passed: %u\n" + szEltPassed);
}


size_t _getSzArr(int arrPassedAsArr[], ptr_t* paramAddr) {
    *paramAddr = arrPassedAsArr;
    return sizeof(arrPassedAsArr);
}

void _showSzArr() {
    print(">>> For an array, sizeof needs to be handled very mindfully!");

    int headElt = 314;
    size_t szElt = sizeof(headElt);
    print("Head element: " + std::to_string(headElt));
    print("Size of each element: " + std::to_string(szElt));

    // could also let compiler infer sizeof(arr) with `int arr[] = ...`
    const size_t n = 3;
    int arrAsArr[n] = {headElt, 272, 162};
    print(">>> Array as array, here: ");
    print(arrAsArr);

    size_t szArrAsArrHere = sizeof(arrAsArr);
    float lenArr = szArrAsArrHere *1./ szElt;
    print("Size of array as array, here: " + std::to_string(szArrAsArrHere));
    print("Hence, length of array (as a float so you know we're not rounding): " + std::to_string(lenArr));

    print(">>> BUT... this stops working as soon as you either");
    print(">>> (a) Cast the array to what it truly is, i.e. a pointer to the head element;");
    print(">>> or, equivalently,");
    print(">>> (b) pass the array into a function.");
    print(">>> We simply get the length of the pointer itself!");
    print(">>> (On a 64bit machine: 64 bits / (8 bits per byte) = 8 bytes.)");
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
    print(">>> Hence, functions that accept arrays usually also demand to know the LENGTH of the array.");
}
*/

void showSz() {
    printSubHeader("Let's examine object sizing");
}

/***********************************************************************************************************************
********* CONCURRENCY, THREADS, AND SYNCHRONIZATION ********************************************************************
***********************************************************************************************************************/

// TODO(sparshsah)


/***********************************************************************************************************************
********* MAIN *********************************************************************************************************
***********************************************************************************************************************/

int main() {
    printDiv(true, false);
    printHeader("Hello world!");
    //
    showPassing();
    showMemLayout();
    showPtrAlign();
    showPtrArith();
    //
    printSubDiv();
    printf("\n----------------------------\n//# Good luck out there now!\n");
    printDiv(false, true);
    return 0;
}

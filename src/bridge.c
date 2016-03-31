#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

// assume this is a opaque struct
typedef struct _UnknownStruct {
    int unknown1;
    int unknown2;
    int theNumber;
} UnknownStruct;

typedef struct _MyStruct MyStruct;

typedef int (*NumberFunc) (MyStruct *myStruct, int a, void *callback_data);
struct _MyStruct {
    UnknownStruct unknown; // define this struct if this was known
    
    NumberFunc callback;
    void *callback_data;
};

// original function
MyStruct *mystruct_new() {
    g_print("mystruct_new\n");
    return malloc(sizeof(MyStruct));
}

void mystruct_free(MyStruct *mystruct) {
    g_print("mystruct_free\n");
    free(mystruct);
}

void mystruct_set_number(MyStruct *mystruct, int a) {
    mystruct->unknown.theNumber = a;
}

void mystruct_hello(MyStruct *mystruct) {
    int a = (mystruct->callback)(mystruct, 
       mystruct->unknown.theNumber,
       mystruct->callback_data);
    g_print("Hello Result: %d\n", a);
}

// additional function
void mystruct_set_callback(MyStruct *mystruct, NumberFunc callback, void *callback_data) {
    mystruct->callback = callback;
    mystruct->callback_data = callback_data;
}


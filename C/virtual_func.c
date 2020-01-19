#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include "toolkit.h"

typedef struct
{
    // 释放接口
    void (*dispose)(void *user_ptr);

} object_vtable_t;

typedef struct
{
    // 释放接口
    object_vtable_t *vtable_ptr;

} object_t;

int main()
{
    object_t obj;

    return 0;
}
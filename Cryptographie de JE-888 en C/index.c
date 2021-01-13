#include <stdio.h>
#include <stdlib.h>
#include "source.h"

int main(void)
{
    struct Keyset key = {};
    key = create_key("lol");
    char *ptr = NULL;
    ptr = uncrypt("output.txt", key, 0);
    free(ptr);
    return 0;
}
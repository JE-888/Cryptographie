#include <stdio.h>
#include <stdlib.h>
#include "source.h"

int main(void)
{
    struct Keyset key = create_key("clef");
    char *ptr = NULL;
    printf("Enter the security level you want (1-1000) ->");
    char answer[4];
    fgets(answer, 4, stdin);
    key.sinnb = atoi(answer);
    printf("\n");
    ptr = crypt("file.txt", key);
    printf("%s\n", ptr);

    ptr = uncrypt("output.txt", key);
    printf("%s\n", ptr);
    free(ptr);
    return 0;
}
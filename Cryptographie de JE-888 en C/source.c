#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float sinc(int x, float amplitude, float frequency, float start);
char* read_file(char fileName[]);
char* convert_text(char text[]); // Don't forget to free the memory !
char* crypt(char file_name[], float sinkey[3], float singet, char baskey[10]); // Don't forget to free the memory !

int main(void)
{
    return 0;
}

float sinc(int x, float amplitude, float frequency, float start)
{
    return amplitude * sin( (frequency*x) / 57.2957795 ) + start; // We convert radians to degrees by dividing by 57.2957795
}

char* read_file(char fileName[])
{
    FILE* f = NULL;
    char str[100] = "";
    static char file_content[1000] = "";

    f = fopen(fileName, "rb");
    if (f == NULL)
    {
        printf("Can't open this file.");
        exit(0);
    }

    while (fgets(str, 100, f) != NULL)
    {
        strcat(file_content, str);
    }

    fclose(f);

    return file_content;
}

char* convert_text(char text[])
{
    char chars[3];
    int value = 0;
    static char *result = NULL;
    result = calloc(strlen(text)*3, 3*sizeof(char));

    if (result == NULL){
        printf("Allocation failed.");
        exit(0);
    }

    for (int i = 0 ; i < strlen(text) ; i++){
        sprintf(chars, "%d", (int) text[i]);
        char zero[3] = "0";
        if (strlen(chars) < 3){
            strcat(zero, (const char *) chars);
            strcpy(chars, (const char *) zero);
        }
        result[i*3+0] = chars[0];
        result[i*3+1] = chars[1];
        result[i*3+2] = chars[2];
    }

    return result;
}

char* crypt(char file_name[], float sinkey[3], float singet, char baskey[10])
{
    char *file_content = NULL;
    file_content = read_file(file_name);
    char *ptr = NULL;
    ptr = convert_text(file_content);
    printf("WARNING : Memory is not free yet.\n");

    return ptr;
}
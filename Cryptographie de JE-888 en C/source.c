#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "source.h"

float sinc(int x, float amplitude, float frequency, float start);
void write_file(char file_name[], char text[]);
struct Keyset create_key(char key[]); // WORK IN PROGRESS
char* read_file(char fileName[]); // Don't forget to free the memory !
char* convert_text(char text[]); // Don't forget to free the memory !
char* convert_numbers(char numbers[]); // Don't forget to free the memory !
char* crypt(char file_name[], struct Keyset key, short singet); // Don't forget to free the memory !
char* uncrypt(char file_name[], struct Keyset key, short singet); // Don't forget to free the memory !

float sinc(int x, float amplitude, float frequency, float start)
{
    return amplitude * sin( (frequency*x) / 57.2957795 ) + start; // We convert radians to degrees by dividing by 57.2957795
}

struct Keyset create_key(char key[])
{
    static struct Keyset dest = {0.0, 0.0, 0.0, "0123456789"};
    char *num_key = NULL;
    num_key = convert_text(key);
    printf("%s\n", num_key);
    dest.amplitude = (float) (num_key[2]+num_key[1]+num_key[0]);
    dest.frequency = dest.amplitude * num_key[1] + 30.0;
    dest.start = (float) num_key[3];
    free(num_key);
    return dest;
}

char* read_file(char fileName[])
{
    FILE *f = NULL;
    char str[100] = "";
    short chr_nb = 0;

    f = fopen(fileName, "r");
    if (f == NULL)
    {
        printf("Can't open this file.");
        exit(0);
    }

    while (fgetc(f) != EOF)
    {
        chr_nb += 1;
    }

    char *file_content = NULL;
    file_content = calloc(chr_nb, sizeof(char));
    if (file_content == NULL){
        printf("Allocation failed.");
        exit(0);
    }

    rewind(f);

    while (fgets(str, 100, f) != NULL)
    {
        strcat(file_content, str);
    }

    fclose(f);

    return file_content;
}

void write_file(char file_name[], char text[])
{
    FILE *f = NULL;
    f = fopen(file_name, "w");

    fputs(text, f);

    fclose(f);
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

char* convert_numbers(char numbers[])
{
    char *result = NULL;
    result = calloc(strlen(numbers) / 3, sizeof(char));
    char chars[3] = "";
    short value;
    short j = 1;

    for (int i = 0 ; i < strlen(numbers) ; i++)
    {
        chars[j-1] = numbers[i];
        if (j >= 3)
        {
            value = atoi((const char *) chars);
            result[i/3] = (char) value;
            strcpy(chars, "");
            j = 0;
        }
        j++;
    }
    return result;
}

char* crypt(char file_name[], struct Keyset key, short singet)
{
    char *file_content = NULL;
    file_content = read_file(file_name);
    char *ptr = NULL;
    ptr = convert_text(file_content);
    printf("\nOLD STRING : %s\n\n", ptr);
    short x = 0;
    short index = 0;
    short absolute_index = 0;
    for (short i = 0 ; i < strlen(ptr) ; i++)
    {
        index = sinc(x, key.amplitude, key.frequency, key.start) - (short) ptr[i] + absolute_index;
        x += singet;
        while (index >= 10)
        {
            index -= 10;
        }
        while (index < 0)
        {
            index += 10;
        }
        ptr[i] = key.base[index];
    }
    printf("WARNING : Memory is not free yet.\n");
    printf("\nNEW STRING : %s\n\n", ptr);
    free(file_content);
    write_file("output.txt", ptr);
    return ptr;
}

char* uncrypt(char file_name[], struct Keyset key, short singet)
{
    int x = 0;
    char *file_content = NULL;
    file_content = read_file(file_name);
    printf("File content found : \"%s\"\n", file_content);
    short index = 0;
    short absolute_index = 0;

    for (short i = 0 ; i < strlen(file_content) ; i++)
    {
        index = sinc(x, key.amplitude, key.frequency, key.start) - (short) file_content[i] + absolute_index;
        x += singet;
        while (index >= 10)
        {
            index -= 10;
        }
        while (index < 0)
        {
            index += 10;
        }
        file_content[i] = key.base[index];
    }
    file_content = convert_numbers(file_content);
    printf("New file content : \"%s\".\n", file_content);
    write_file("output.txt", file_content);

    return file_content;
}
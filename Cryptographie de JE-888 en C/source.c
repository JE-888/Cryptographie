#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float sinc(int x, float amplitude, float frequency, float start);
void write_file(char file_name[], char text[]);
char* read_file(char fileName[]); // Don't forget to free the memory !
char* convert_text(char text[]); // Don't forget to free the memory !
char* convert_numbers(char numbers[]); // Don't forget to free the memory !
char* crypt(char file_name[], float sinkey[3], short singet, char baskey[10]); // Don't forget to free the memory !
char* uncrypt(char file_name[], float sinkey[3], short singet, char baskey[10]); // Don't forget to free the memory !

int main(void)
{
    char *ptr = NULL;
    float ar[3] = {8.0, 3.5, 5.1};
    ptr = uncrypt("file.txt", ar, 3, "0123456789");
    //ptr = crypt("file.txt", ar, 3, "0123456789");
    free(ptr);
    printf("Memory is now free. :)\n");
    return 0;
}

float sinc(int x, float amplitude, float frequency, float start)
{
    return amplitude * sin( (frequency*x) / 57.2957795 ) + start; // We convert radians to degrees by dividing by 57.2957795
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
    printf("Hello\n");
    static char *result = NULL;
    result = calloc(strlen(numbers)/3, sizeof(char));
    char three_numbers[3];
    for (int i = 0 ; i < strlen(numbers) ; i++)
    {
        printf("Three numbers : %s\n", three_numbers);
        if (sizeof(i % 3) == sizeof(int))
        {
            result[i/3] = ((char) ((int) three_numbers));
            printf("Added : %c\n", result[i/3]);
            strcpy(three_numbers, "");
        }
    }
    return result;
}

char* crypt(char file_name[], float sinkey[3], short singet, char baskey[10])
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
        index = sinc(x, sinkey[0], sinkey[1], sinkey[2]) - (short) ptr[i] + absolute_index;
        x += singet;
        while (index >= 10)
        {
            index -= 10;
        }
        while (index < 0)
        {
            index += 10;
        }
        ptr[i] = baskey[index];
    }
    printf("WARNING : Memory is not free yet.\n");
    printf("\nNEW STRING : %s\n\n", ptr);
    free(file_content);
    write_file("output.txt", ptr);
    return ptr;
}

char* uncrypt(char file_name[], float sinkey[3], short singet, char baskey[10])
{
    int x = 0;
    char *file_content = NULL;
    file_content = read_file(file_name);
    printf("File content found : \"%s\"\n", file_content);
    short index = 0;
    short absolute_index = 0;

    for (short i = 0 ; i < strlen(file_content) ; i++)
    {
        index = sinc(x, sinkey[0], sinkey[1], sinkey[2]) - (short) file_content[i] + absolute_index;
        x += singet;
        while (index >= 10)
        {
            index -= 10;
        }
        while (index < 0)
        {
            index += 10;
        }
        file_content[i] = baskey[index];
    }
    printf("New file content : \"%s\".\n", file_content);
    write_file("output.txt", file_content);

    return file_content;
}

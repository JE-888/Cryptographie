#ifndef SOURCE_H
#define SOURCE_H

struct Keyset
{
    float amplitude;
    float frequency;
    float start;
    char base[10];
};

float sinc(int x, float amplitude, float frequency, float start);
void write_file(char file_name[], char text[]);
struct Keyset create_key(char key[]); // WORK IN PROGRESS
char* read_file(char fileName[]); // Don't forget to free the memory !
char* convert_text(char text[]); // Don't forget to free the memory !
char* convert_numbers(char numbers[]); // Don't forget to free the memory !
char* crypt(char file_name[], struct Keyset key, short singet); // Don't forget to free the memory !
char* uncrypt(char file_name[], struct Keyset key, short singet); // Don't forget to free the memory !

#endif
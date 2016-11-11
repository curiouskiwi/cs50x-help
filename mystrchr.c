/*
  mystrchr.c
  Brenda Anderson
  Oct 2016
**/

#include <stdio.h>
#include <string.h>
#include <cs50.h>

char* mystrchr(char* s, char c);

int main(void)
{
    printf("String: ");
    char* str = get_string();
    printf("Character: ");
    char c = get_char();
    printf("Looking for substring...\n");
    char* result = mystrchr(str,c);
    if (result == NULL)
    {
        printf("Couldn't find %c.\n", c);
    }
    else
    {
        printf("Substring: %s is part of %s\n", result, str);
    }
}
   
/*
 finds the character in the string
 */
char* mystrchr(char* s, char c)
{
    while (*s)
    {
        if (*s == c)
        {
            return s;
        }
        s++;
    }
    return NULL; 
}
    

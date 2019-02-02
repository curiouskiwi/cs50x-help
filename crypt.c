/**
 *   crypt a password given a salt
 *   usage: ./crypt password salt where salt is a 2-char string
 *    used for creating hashed passwords for testing ./crack (pset2)
 *   brenda anderson 
 *   14 april 2017
 *
**/
#define _XOPEN_SOURCE  
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("usage ./crypt password salt\n");
        return -1;
    }
    if (argv[2][1] == 0)
    {
        printf("Salt must be at least 2 chars long. (extra will be ignored)\n");
        return -2;
    }
    
    printf("%s\n", crypt(argv[1],argv[2]));
    return 0;
}

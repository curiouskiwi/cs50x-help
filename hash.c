// Hash function illustration
// Brenda Anderson 2018

#include <stdio.h>
#include <stdint.h>

// prototype
int hash(const char *s);

int main(int argc, char *argv[])
{
    // get word from the command line
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s word\n", argv[0]);
        return 1;
    }
    char *word = argv[1];
    printf("%s has a hash of %i\n", word, hash(word));
}

// calculates a hash sized to fit a hashtable of 65536 elements
// case-sensitive (case-insensitive option in comment)
int hash(const char *s)
{
    uint32_t hash = 0;
    while (*s)
    {
        hash = (hash << 2) ^ *s; //(*s | 0x20);
        s++;
    }

    // return a value between 0 and 65535
    return (int)((hash >> 16) ^ (hash & 0xffff));
}
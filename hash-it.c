// Hash function illustration
// Brenda Anderson 2018

#include <stdio.h>
#include <stdint.h>

// prototype
int hash(const char *s, uint32_t *fullhash);

int main(int argc, char *argv[])
{
    // get word from the command line
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s word\n", argv[0]);
        return 1;
    }
    char *word = argv[1];

    // variable to hold the full hash which is set in the hash function
    uint32_t fullhash;
    int index = hash(word, &fullhash);
    printf("%s has a full hash of %u and a bucket-sized hash of %i\n", word, fullhash, index);
}

// calculates a 32 bit hash and hash sized
// to fit a hashtable of 65536 elements
int hash(const char *s, uint32_t *fullhash)
{
    uint32_t hash = 0;
    while (*s)
    {
        hash = (hash << 2) ^ *s; //(*s | 0x20);
        s++;
    }
    *fullhash = hash;
    return (int)((hash >> 16) ^ (hash & 0xffff));
}
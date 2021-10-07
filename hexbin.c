// When given a hex string at command line
// Print out the binary representation

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void hexbin(char c);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: hexbin HEX\n");
        return 1;
    }

    char *hexstring = argv[1];
    printf("hex: %s\nbin: ", hexstring);

    // Validate the string as containing only hex digits (A-F, 0-9)
    for (int i = 0, n = strlen(hexstring); i < n; i++)
    {
        if (isxdigit(hexstring[i]))
        {
            hexbin(hexstring[i]);
        }
        else
        {
            printf("\033[0;31m !'%c' is not a hex digit\n", hexstring[i]);
            return 1;
        }
    }
    printf("\n");
}


// Print a hex digit in binary representation
void hexbin (char c)
{
    c |= 0x20;
    c = (c >= 'a' && c <= 'f') ? c -'a' + 10 : c - '0';
    for (int bit = 8; bit; bit >>= 1)
    {
        printf("%c", c & bit ? '1' : '0');
    }
}

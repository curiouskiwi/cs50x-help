// DNA in C
// Made some assumptions that weren't necessary for the python assignment
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Assumptions about the csv file
#define MAXSTRS 10
#define MAXLINELENGTH 100
#define MAXLINES 25

char *get_seq(const char *txt);
int lmatch(char *seq, char *sub);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("usage: ./dna db txt\n");
        return 1;
    }

    // open the CSV file
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("could not open csv file\n");
        return 2;
    }

    // read in the sequences text
    char *s = get_seq(argv[2]);
    if (s == NULL)
    {
        printf("could not open sequence file\n");
        return 3;
    }
 
    char *strs[MAXSTRS];
    char buff[MAXLINELENGTH];
    // read in the first line to get the STR names
    fscanf(f, "%s", buff);

    // parsing the STR names
    // we don't need the word 'name'
    strtok(buff, ",");
    int strcount = 0;
    for (strcount = 0; strcount < MAXSTRS; strcount++)
    {
        strs[strcount] = strtok(NULL, ",");
        if (!strs[strcount])
            break;
    }

    // array to hold the longest consecutive counts for each STR
    int results[strcount];

    // get the counts for each STR
    for (int i = 0; i < strcount; i++)
        results[i] = lmatch(s, strs[i]);

    // done with the sequence string
    free(s);

    char line[MAXLINELENGTH];
    bool found = false;

    // read each line of the csv file and check for match
    while (fscanf(f, "%s", line) != EOF && !found)
    {
        // get the person's name
        char *name = strtok(line, ",");
        int count = 0;
        for (count = 0; count < strcount; count++)
        {
            char *test = strtok(NULL, ",");
            // if the value for the STR doesn't match, break out and move to next line
            if (atoi(test) != results[count])
                break;
        }
        if (count == strcount)
        {
            printf("%s\n", name);
            found = true;
        }
    }
    if (!found)
        printf("No match\n");
    fclose(f);
    return 0;
}


// opens the sequences text file and returns it as a string, returns NULL on failure
char *get_seq(const char *txt)
{
    FILE *f = fopen(txt, "r");
    if (f == NULL)
        return NULL;
    // we need to know the size of the file first
    fseek(f, 0, SEEK_END);
    int len = ftell(f);
    rewind(f);
    // remember to free it in main!
    char *s = malloc(len+1);
    fscanf(f, "%s", s);
    fclose(f);
    return s;
}


// what's bigger?
int max(int n, int m)
{
    return (n >= m ? n : m);
}


// calculates the longest consecutive match in the string
int lmatch(char *seq, char *sub)
{
    int best = 0;
    int len = strlen(sub);
    int n = strlen(seq);

    for (char *start = seq; start < seq + n; start++)
    {
        char *found = strstr(start, sub);
        if (!found)
            break;
        int count = 1;
        while (strncmp(found + count * len, sub, len) == 0)
            count++;
        best = max(best, count);
        start = found + count * len;
    }
    return best;
}

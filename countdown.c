/**
 * countdown.c
 * find the longest word using the 9 letters given
 * uses cs50's pset5 large dictionary
 * 
 * Brenda Anderson
 * 23 Sep 2016
 * */
 

#include <stdio.h>
#include <string.h>
#include <cs50.h>

#define DICTIONARY "CS50x/pset5/large"
#define LONGESTWORD 46

int main (void)
{
    // get 9 chars from user. store in a null-terminated array (string)
    char letters[10];
    for (int i = 0; i < 9; i++)
        letters[i] = get_char();
    letters[9] = '\0';
    
    // open the dictionary
    FILE* fp = fopen(DICTIONARY, "r");
    if (fp == NULL)
    {
        printf("couldn't open dictionary!\n");
        return 404;
    }
    
    // word to hold dictionary word
    char word[LONGESTWORD+1];
    
    // word to hold the best match so far
    char match[10] = "No match!";

    // length of longest word matched
    int maxlength = 0;
    
    // debug
    // int _count = 0, _tested = 0;
    
    // get each word from dictionary to see if it can be made from the 9 letters
    while (fgets(word, sizeof(word), fp) != NULL)
    {
        // debug
        // _count++;
        
        // get the word length since only words with 9 letters or fewer can be matches
        int wordlen = strlen(word);
        
        // fgets includes the newline so remove that from the word
        word[--wordlen] = 0;
        
        // if word longer than 9, eliminate, plus only check words longer than max found so far
        if (wordlen < 10 && wordlen > maxlength)
        {
            // copy of letters so I can eliminate matched ones from the array
            char test[10];
            strcpy(test, letters);
            
            // for debug 
            //  _tested++;
            
            // loop over the word. i at end of the loop equals the number of matched letters
            int i;
            for (i = 0; i < wordlen; i++)
            {
                char* matched = strchr(test,word[i]);
                
                // change matched letter to '+' which will never be in a dictionary word
                if (matched)
                {
                    *matched = '+';
                }
                // if letter not matched, word is eliminated 
                else
                    break;
            }

            // if all letters in word matched, it's a contender
            if (i == wordlen)
            {
                //printf("%s\n", word); 
                strcpy(match, word);
                maxlength = wordlen;
            }
        }    
    }
    // printf("tested %i of %i\n", _tested, _count);

    // print the longest match
    printf("%s\n", match);
}

/* scoreC.c
*   compute edit distance between two texts
*   (assumes plain ascii text)
*   implemented with 2 arrays (one for optimal score and
*   the other for the operation taken)
*
*   brenda anderson
*   2017-10-23
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DELETED 1
#define INSERTED 2
#define SUBSTITUTED 3

typedef uint8_t  BYTE;

// Prototypes
void init_matrix(short *score, BYTE *op, int rows, int cols);
void fill_matrix(short *score, BYTE *op, int rows, int col, char *f1, char *f2 );
void print_matrix(short *score, BYTE *op, int rows, int cols);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("usage: ./scoreC FILE1 FILE2");
    }

    // Verify the two files can be opened
    FILE *file1 = fopen(argv[1], "r");
    if (file1 == NULL)
    {
        printf("could not open file1\n");
        return -1;
    }
    FILE *file2 = fopen(argv[2], "r");
    if (file2 == NULL)
    {
        if (file1)
        {
            fclose(file1);
        }
        printf("could not open file2\n");
        return -1;
    }

    // Get file lengths to dynamically allocate the memory needed to store as strings
    fseek(file1, 0, SEEK_END);
    int len1 = ftell(file1);
    fseek(file1, 0, SEEK_SET);

    fseek(file2, 0, SEEK_END);
    int len2 = ftell(file2) ;
    fseek(file2, 0, SEEK_SET);

    int rows = len1 + 1;
    int cols = len2 + 1;
    printf("rows: %i\ncols: %i\n", rows, cols);

    // Get memory for each string
    char *f1 = malloc(rows);
    if (f1 == NULL)
    {
        printf("couldn't create string\n");
        return -1;
    }
    char *f2 = malloc(cols);
    if (f2 == NULL)
    {
        printf("couldn't create string\n");
        return -1;
    }

    // Read files into string
    fread(f1, 1, len1, file1);
    f1[len1] = '\0';
    fread(f2, 1, len2, file2);
    f2[len2] = '\0';


    // Initialize the matrix
    short *score = calloc(1, rows * cols * sizeof(short));
    BYTE *op = calloc(1, rows * cols * sizeof(BYTE));
    init_matrix(score, op, rows, cols);

    // Fill the matrix
    fill_matrix(score, op, rows, cols, f1, f2);

    // DEBUG printing
    // printf("Text1:\n %s\n", f1);
    // printf("Text2:\n %s\n", f2);
    // print_matrix(score, op, rows, cols);

    // Final score
    printf("%i\n", score[len1*cols + len2]);

    // Tidy up
    free(score);
    free(op);
    free(f1);
    free(f2);
    fclose(file1);
    fclose(file2);

    // All done
    return 0;
}

/*
* Sets the first row and column based on text lengths
*/
void init_matrix(short *score, BYTE *op, int rows, int cols)
{

    score[0] = 0;
    op[0] = 0;

    // Initialize all columns in Row 0
    // Blank string to any char(s) is an Insert
    for (int col = 1; col < cols; col++)
    {
        score[col] = score[col-1] + 1;
        op[col] = INSERTED;
    }

    // Initialize all rows in Column 0
    // Any char(s) to blank string is a Delete
    for (int row = 1; row < rows; row++)
    {
        score[row*cols] = score[(row-1)*cols] + 1;
        op[row*cols] = DELETED;
    }

}
/*
* Calculates the scores for each cell based on the chars in the text
*/
void fill_matrix(short *score, BYTE *op, int rows, int cols, char *f1, char *f2 )
{
    int lowest_score = 0, lowest_op = 0, s = 0, d = 0, i = 0;

    for (int row = 1; row < rows; row++)
    {
        for (int col = 1; col < cols; col++)
        {
           // Substitution first as that is potential lowest cost

           // If the chars are the same, then no cost
           if (f1[row-1] == f2[col-1])
            {
                s = score[(row-1)*cols + col-1];
            }
            // Else the cost is 1
            else
            {
                s = score[(row-1)*cols + col-1] + 1;
            }
            lowest_score = s;
            lowest_op = SUBSTITUTED;

           // Deleting a char has cost of 1
            d = score[(row-1)*cols + col] + 1;
            if (d < lowest_score)
            {
                lowest_score = d;
                lowest_op = DELETED;
            }

           // Inserting a char has cost of 1
            i = score[row*cols + col-1] + 1;
            if (i < lowest_score)
            {
                lowest_score = i;
                lowest_op = INSERTED;
            }

            // Now fill the cell with the optimal path values
            score[row*cols + col] = lowest_score;
            op[row*cols + col] = lowest_op;
        }
    }
}

/*
* Prints the matrix for debugging purposes
*/
void print_matrix(short *score, BYTE *op, int rows, int cols)
{
       for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            printf(" %2i:%i", score[r*cols + c], op[r*cols + c]);
        }
        printf("\n");
    }
}

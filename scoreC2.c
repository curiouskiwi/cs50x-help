/* scoreC2.c
*   compute edit distance between two texts
*   (assumes plain ascii text)
*
*   struct version
*   brenda anderson
*   2017-10-23
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DELETED 1
#define INSERTED 2
#define SUBSTITUTED 3

typedef struct
{
    short score;
    uint8_t op;
}
cell;

// Prototypes
void init_matrix(cell *matrix, int rows, int cols);
void fill_matrix(cell *matrix, int rows, int col, char *f1, char *f2 );
void print_matrix(cell *matrix, int rows, int cols);


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
        if (file1) fclose(file1);
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
    if (f1 == NULL) return -1;
    char *f2 = malloc(cols);
    if (f2 == NULL) return -1;

    // Read files into string
    fread(f1, 1, len1, file1);
    f1[len1] = '\0';
    fread(f2, 1, len2, file2);
    f2[len2] = '\0';

    cell *matrix = calloc(1, rows*cols*sizeof(cell));

    // Initialize the matrix
    init_matrix(matrix, rows, cols);

    // Fill the matrix
    fill_matrix(matrix, rows, cols, f1, f2);

    // DEBUG printing
    // printf("Text1:\n %s\n", f1);
    // printf("Text2:\n %s\n", f2);
    // print_matrix(matrix, rows, cols);

   // Final score
    printf("%i\n", matrix[len1*cols+len2].score);

   // Tidy up
   free(matrix);
   free(f1);
   free(f2);
   fclose(file1);
   fclose(file2);

   return 0;
}


/*
* Sets the first row and column based on text lengths
*/
void init_matrix(cell* matrix, int rows, int cols)
{

    matrix[0].score= 0;
    matrix[0].op = 0;

    for (int col = 1; col < cols; col++)
    {
        matrix[col].score = matrix[col-1].score + 1;
        matrix[col].op = INSERTED;
    }

    for (int row = 1; row < rows; row++)
    {
        matrix[row*cols].score = matrix[(row-1)*cols].score + 1;
        matrix[row*cols].op = DELETED;
    }
}


/*
* Calculates the scores for each cell based on the chars in the text
*/
void fill_matrix(cell *matrix, int rows, int cols, char *f1, char *f2 )
{
    int lowest_score = 0, lowest_op = 0, s = 0, d = 0, i = 0;

    for (int row = 1; row < rows; row++)
    {
        for (int col = 1; col < cols; col++)
        {
           // Substitution first as that is potential lowest cost
            if (f1[row-1] == f2[col-1])
            {
                s = matrix[(row-1)*cols + col-1].score;
            }
            else
            {
               s = matrix[(row-1)*cols + col-1].score + 1;
            }

            lowest_score = s;
            lowest_op = SUBSTITUTED;

           // Deletion
            d = matrix[(row-1)*cols + col].score + 1;

            if (d < lowest_score)
            {
                lowest_score = d;
                lowest_op = DELETED;
            }

           // Insertion
            i = matrix[row*cols + col-1].score + 1;

            if (i < lowest_score)
            {
                lowest_score = i;
                lowest_op = INSERTED;
            }

            // Now fill the cell with the optimal path values
            matrix[row*cols + col].score = lowest_score;
            matrix[row*cols + col].op = lowest_op;
        }
    }
}


/*
* Prints the matrix for debugging purposes
*/
void print_matrix(cell *matrix, int rows, int cols)
{
       for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
           printf(" %2i:%i", matrix[r*cols + c].score, matrix[r*cols + c].op);

        printf("\n");
    }
}

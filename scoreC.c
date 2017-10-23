/* scoreC.c
*   compute edit distance between two texts
*   (assumes plain ascii text)
*
*   brenda anderson
*   2017-10-23
*/

#include <stdio.h>
#include <stdlib.h>

#define DELETED 1
#define INSERTED 2
#define SUBSTITUTED 3


// Prototypes
void init(int* score, int* op, int rows, int cols);
void fill_matrix(int *score, int *op, int rows, int col, char *f1, char *f2 );
void print_matrix(int *score, int *op, int rows, int cols);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("usage: ./scoreC FILE1 FILE2");
    }

    // verify the two files can be opened
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

    // get file lengths to dynamically allocate the memory needed to store as strings
    fseek(file1, 0, SEEK_END);
    int len1 = ftell(file1);
    fseek(file1, 0, SEEK_SET);

    fseek(file2, 0, SEEK_END);
    int len2 = ftell(file2) ;
    fseek(file2, 0, SEEK_SET);

    int rows = len1 + 1;
    int cols = len2 + 1;
    printf("rows: %i\ncols: %i\n", rows, cols);

    // get memory for each string
    char *f1 = malloc(rows);
    if (f1 == NULL) return -1;
    char *f2 = malloc(cols);
    if (f2 == NULL) return -1;

    // read files into string
    fread(f1, 1, len1, file1);
    f1[len1] = '\0';
    fread(f2, 1, len2, file2);
    f2[len2] = '\0';

    int *score = calloc(1,rows*cols*sizeof(int));
    int *op = calloc(1,rows*cols*sizeof(int));

    // initialize the matrix
    init(score, op, rows, cols);

    // fill the matrix
    fill_matrix(score, op, rows, cols, f1, f2);

    // print matrix for debugging
   // print_matrix(score, op, rows, cols);

    //printf("Text1:\n %s\n", f1);
    //printf("Text2:\n %s\n", f2);


   printf("%i\n", score[len1*cols + len2]);

   // tidy up
   free(score);
   free(op);
   free(f1);
   free(f2);
   fclose(file1);
   fclose(file2);

   return 0;
}


void init(int* score, int* op, int rows, int cols)
{

    score[0] = 0;
    op[0] = 0;

    for (int col = 1; col < cols; col++)
    {
        score[col] = score[col-1]+1;
        op[col] = INSERTED;
    }
    for (int row = 1; row < rows; row++)
    {
        score[row*cols] = score[(row-1)*cols]+1;
        op[row*cols] = DELETED;
    }

}

void fill_matrix(int *score, int *op, int rows, int cols, char *f1, char *f2 )
{
    int lowest_score = 0, lowest_op = 0, s = 0, d = 0, i = 0;

    for (int row = 1; row < rows; row++)
    {
        for (int col = 1; col < cols; col++)
        {
           //substitution first as that is potential lowest cost
           if (f1[row-1] == f2[col-1])
            {
                s = score[(row-1)*cols + col-1];
            }
            else
            {
                s = score[(row-1)*cols + col-1] + 1;
            }
            lowest_score = s;
            lowest_op = SUBSTITUTED;

           // deletion
            d = score[(row-1)*cols + col] + 1;
            if (d < lowest_score)
            {
                lowest_score = d;
                lowest_op = DELETED;
            }

           // insertion
            i = score[row*cols + col-1] + 1;
            if (i < lowest_score)
            {
                lowest_score = i;
                lowest_op = INSERTED;
            }
            score[row*cols + col] = lowest_score;
            op[row*cols + col] = lowest_op;
        }
    }

}

void print_matrix(int *score, int* op, int rows, int cols)
{
       for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
            printf(" %2i:%i", score[r*cols + c],op[r*cols + c]);

        printf("\n");
    }
}

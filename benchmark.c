/*
 * Benchmarks speller program against the staff's implementation
 * with all the texts available in the pset5/texts folder
 *
 * - Azaan (azaan@outlook.com) 2012
 *   
 *. Thanks Azaan!! 
 *.
 *. @curiouskiwi 
 *. updated 1 Apr 2020 for new directories
 *. also removed directories from the list of files
 */

#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CS50_TEXTS "/home/ubuntu/pset5/speller/texts/"
#define CS50_SPELLER "/home/cs50/2019/fall/pset5/speller"

// max number of files that can be benchmarked
#define MAX_FILES 100

// output constants
#define C_CLEAR "\033[2J\033[1;1H"
#define C_RESET "\e[m"
#define C_GREEN "\e[32m"
#define C_YELLOW "\e[33m"
#define C_CYAN "\e[36m"
#define C_BLUE "\e[34m"
#define C_RED "\e[31m"
#define C_WHITE "\e[37m"
#define C_BOLD "\e[1m"
#define C_BWHITE "\e[47m"

#define C_CS50 C_CYAN
#define C_YOURS C_WHITE

typedef struct
{
    char* filename;
    char* path;
    bool success;

    int misspelled, cs50_misspelled;
    int dictionary, cs50_dictionary;
    int text, cs50_text;

    float load, cs50_load;
    float check, cs50_check;
    float size, cs50_size;
    float unload, cs50_unload;
    float total, cs50_total;
}
record;

char* compare_format(float num1, float num2);
void print_row(record* mrecord, int prec);
void error_m(char* error, int errno);
void dump_record(record* mrecord);
void set_path(record* mrecord);
record* create_record();
void delete_record(record* mrecord);

// benchmarks given file
void run_benchmark(record* mrecord);

bool includeStaff = false;




int main(int argc, char* argv[])
{
    if ((argc > 1) && strcmp(argv[1],"t") == 0) includeStaff = true;

    // make sure speller program exists
    FILE* fp = fopen("speller", "r");
    if (!fp)
        error_m("speller binary does not exist, please compile it and place it in \
                the current director\n", 1);

    fclose(fp);

    //
    // setup records to benchmark
    //

    record* records[MAX_FILES];
    int num_records;

    DIR* dirp = opendir(CS50_TEXTS);
    if (!dirp)
        error_m("Could not read " CS50_TEXTS "\n", 1);

    struct dirent* dir;
    int f = 0;
    while ((dir = readdir(dirp)) != NULL)
    {
        records[f] = create_record();
        records[f]->filename = strdup(dir->d_name);

        char* temp_path = malloc(sizeof(char) * 150);

        strcpy(temp_path, CS50_TEXTS);
        strcat(temp_path, dir->d_name);
        
        if (dir->d_name[0] == '.') continue;
        records[f]->path = temp_path;

        f++;
    }

    closedir(dirp);
    num_records = f;

    // clear screen
    printf(C_CLEAR);

    // print header
    printf("\t" C_CS50 "Cyan " C_RESET "- CS50's implementation\n");
    printf("\t" C_YOURS "White " C_RESET "- your implementation\n");
    printf("\t" C_BOLD "Bold " C_RESET "- lesser time\n");

    printf("\n");
    printf("Filename\t");
    printf("Status\t");
    printf("Load\t\t");
    printf("Check\t\t");
    printf("Size\t\t");
    printf("Unload\t\t");
    printf("Total\t\t");
    printf("\n");

    float ytload = 0, ytcheck = 0, ytsize = 0, ytunload = 0, yttotal = 0;
    float ctload = 0, ctcheck = 0, ctsize = 0, ctunload = 0, cttotal = 0;

    // benchmark the files and output records
    for (int i = 0; i < num_records; i++)
    {
        // print filename and flush buffer
        printf("%15.15s\t", records[i]->filename);
        fflush(stdout);

        // run benchmark
        run_benchmark(records[i]);

        // print status
        if (records[i]->success)
            printf(C_GREEN "OK\t");
        else
            printf(C_RED "ERROR\t");
        printf(C_RESET);

        // print data
        print_row(records[i], 3);

        // keep track of totals
        ctload += records[i]->cs50_load;
        ytload += records[i]->load;

        ctcheck += records[i]->cs50_check;
        ytcheck += records[i]->check;

        ctsize += records[i]->cs50_size;
        ytsize += records[i]->size;

        ctunload += records[i]->cs50_unload;
        ytunload += records[i]->unload;

        cttotal += records[i]->cs50_total;
        yttotal += records[i]->total;
    }

    // display averages
    printf("\n");
    printf("Average : \t\t");

    // print averages using the function which prints a row, takes a record struct
    record rec;
 /*   rec.load        = ytload;
    rec.cs50_load   = ctload;
    rec.check       = ytcheck;
    rec.cs50_check  = ctcheck;
    rec.size        = ytsize;
    rec.cs50_size   = ctsize;
    rec.unload      = ytunload;
    rec.cs50_unload = ctunload;
    rec.total       = yttotal;
    rec.cs50_total  = cttotal;
*/
    rec.load        = ytload / num_records;
    rec.cs50_load   = ctload / num_records;
    rec.check       = ytcheck / num_records;
    rec.cs50_check  = ctcheck / num_records;
    rec.size        = ytsize / num_records;
    rec.cs50_size   = ctsize / num_records;
    rec.unload      = ytunload / num_records;
    rec.cs50_unload = ctunload / num_records;
    rec.total       = yttotal / num_records;
    rec.cs50_total  = cttotal / num_records;


    print_row(&rec, 3);

    printf("\t\t\t");
    printf("Load\t\t");
    printf("Check\t\t");
    printf("Size\t\t");
    printf("Unload\t\t");
    printf("Total\t\t");
    printf("\n\n");

    // clean up
    for (int i = 0; i < num_records; i++)
        delete_record(records[i]);

    return 0;
}


/*
 * benchmarks the file and returns the structure with
 * values filled in
 */
void run_benchmark(record* mrecord)
{
    char user_command[250];
    char cs50_command[250];

    sprintf(user_command, "./speller %s", mrecord->path);
    sprintf(cs50_command, "%s %s", CS50_SPELLER, mrecord->path);

    FILE* fpipe;
    char buffer[200];

    // execute and parse user results
    fpipe = popen(user_command, "r");
    if (!fpipe)
    {
        mrecord->success = false;
        return;
    }

    // consume till stats
    while (fgets(buffer, sizeof(buffer), fpipe))
        if (strstr(buffer, "WORDS MISSPELLED") != NULL)
            break;

    sscanf(buffer, "WORDS MISSPELLED: %d\n", &mrecord->misspelled);

    // parse output
    fscanf(fpipe,   "WORDS IN DICTIONARY:  %d\n"
                    "WORDS IN TEXT:        %d\n"
                    "TIME IN load:         %f\n"
                    "TIME IN check:        %f\n"
                    "TIME IN size:         %f\n"
                    "TIME IN unload:       %f\n"
                    "TIME IN TOTAL:        %f\n"

            , &mrecord->dictionary, &mrecord->text
            , &mrecord->load, &mrecord->check, &mrecord->size, &mrecord->unload
            , &mrecord->total);

    pclose(fpipe);

 if (includeStaff)
 {
    // execute and parse cs50 results
    fpipe = (FILE*) popen(cs50_command, "r");
    if (!fpipe)
    {
        mrecord->success = false;
        return;
    }

    // consume till stats
    while (fgets(buffer, sizeof(buffer), fpipe))
        if (strstr(buffer, "WORDS MISSPELLED") != NULL)
            break;

    sscanf(buffer, "WORDS MISSPELLED: %d\n", &mrecord->cs50_misspelled);

    // parse output
    fscanf(fpipe,   "WORDS IN DICTIONARY:  %d\n"
                    "WORDS IN TEXT:        %d\n"
                    "TIME IN load:         %f\n"
                    "TIME IN check:        %f\n"
                    "TIME IN size:         %f\n"
                    "TIME IN unload:       %f\n"
                    "TIME IN TOTAL:        %f\n"

            , &mrecord->cs50_dictionary, &mrecord->cs50_text
            , &mrecord->cs50_load, &mrecord->cs50_check, &mrecord->cs50_size, &mrecord->cs50_unload
            , &mrecord->cs50_total);

    pclose(fpipe);
}
    // thats all
    mrecord->success = true;
}


/*
 * displays the error, and exists with the errno
 */
void error_m(char* error, int errno)
{
    printf("Error: %s", error);
    exit(errno);
}

/*
 * prints the row
 */
void print_row(record* rec, int prec)
{
    printf("%s", compare_format(rec->cs50_load, rec->load));
    printf(C_CS50 "%.*f\t" C_RESET, prec, rec->cs50_load);
    printf("%s", compare_format(rec->load, rec->cs50_load));
    printf(C_YOURS "%.*f\t" C_RESET, prec, rec->load);
    printf(C_RESET);

    printf("%s", compare_format(rec->cs50_check, rec->check));
    printf(C_CS50 "%.*f\t" C_RESET, prec, rec->cs50_check);
    printf("%s", compare_format(rec->check, rec->cs50_check));
    printf(C_YOURS "%.*f\t" C_RESET, prec, rec->check);
    printf(C_RESET);

    printf("%s", compare_format(rec->cs50_size, rec->size));
    printf(C_CS50 "%.*f\t" C_RESET, prec, rec->cs50_size);
    printf("%s", compare_format(rec->size, rec->cs50_size));
    printf(C_YOURS "%.*f\t" C_RESET, prec, rec->size);
    printf(C_RESET);

    printf("%s", compare_format(rec->cs50_unload, rec->unload));
    printf(C_CS50 "%.*f\t" C_RESET, prec, rec->cs50_unload);
    printf("%s", compare_format(rec->unload, rec->cs50_unload));
    printf(C_YOURS "%.*f\t" C_RESET, prec, rec->unload);
    printf(C_RESET);

    printf("%s", compare_format(rec->cs50_total, rec->total));
    printf(C_CS50 "%.*f\t" C_RESET, prec, rec->cs50_total);
    printf("%s", compare_format(rec->total, rec->cs50_total));
    printf(C_YOURS "%.*f\t" C_RESET, prec, rec->total);

    printf(C_RESET "\n");
}

/*
 * returns the format specifier based on comparision
 */
char* compare_format(float num1, float num2)
{
    float epsilon = 0.0001;

    // equal
    if (fabs(num1-num2) <= epsilon)
        return C_BOLD;

    // num1 greater
    if (num1 < num2)
        return C_BOLD;

    // num2 greater
    return "";
}

record* create_record()
{
    record* r = malloc(sizeof(record));
    return r;
}

void delete_record(record* mrecord)
{
    free(mrecord->path);
    free(mrecord->filename);
    free(mrecord);
}

void dump_record(record* mrecord)
{
    printf("\nUser Details :\n");
    printf("WORDS MISSPELLED:     %d\n"
           "WORDS IN DICTIONARY:  %d\n"
           "WORDS IN TEXT:        %d\n"
           "TIME IN load:         %.2f\n"
           "TIME IN check:        %.2f\n"
           "TIME IN size:         %.2f\n"
           "TIME IN unload:       %.2f\n"
           "TIME IN TOTAL:        %.2f\n"

           , mrecord->misspelled, mrecord->dictionary, mrecord->text
           , mrecord->load, mrecord->check, mrecord->size, mrecord->unload
           , mrecord->total);

    printf("\nCS50 Details :\n");
    printf("WORDS MISSPELLED:     %d\n"
           "WORDS IN DICTIONARY:  %d\n"
           "WORDS IN TEXT:        %d\n"
           "TIME IN load:         %.2f\n"
           "TIME IN check:        %.2f\n"
           "TIME IN size:         %.2f\n"
           "TIME IN unload:       %.2f\n"
           "TIME IN TOTAL:        %.2f\n"

           , mrecord->cs50_misspelled, mrecord->cs50_dictionary, mrecord->cs50_text
           , mrecord->cs50_load, mrecord->cs50_check, mrecord->cs50_size, mrecord->cs50_unload
           , mrecord->cs50_total);
}

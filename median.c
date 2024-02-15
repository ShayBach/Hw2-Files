#include <stdio.h> //printf,scanf
#include <string.h> //strlen,strcat,etc 
#include <stdlib.h> //malloc, free
#define MAX_ARRAY_SIZE 10000
#define MAX_SCORE 100
#define MIN_SCORE 0
/**
 * @brief This fuction compares two integers for qsort 
 * @param a is the first integer
 * @param b is the first integer
 * @return 1 - if  a>b; -1 if a<b; 0 if they are equals
*/
int compare_values(const void *a, const void *b);

/**
 * @brief This fuction calculates from a given grades file it's median
 * @param *fp is the pointer to the grades file
 * @return 1 if the file has more than 1 argument in a line or the file
 * contains unreal grades (more than 100 or less than 0)
 * @note the function also prints the median out of the grades 
*/
int calc_median(FILE *fp);

int main (int argc, char *argv[]){
    FILE *fp;
    int exit_status;
    //ARGV[0] - name of our program

    //1 - there is only argv[0]- there is no path at all
    //2 - the path is "-"
    //3 - file can't end with "/" in linux
   if ((argc == 1) || (!strcmp(argv[1],"-")) || 
    (argv[1][strlen(argv[1])-1] == '/')) {
        fp = stdin;
    }
    else {
        fp = fopen(argv[1], "r");
    }
    //Must check if file is not found:
    if (!fp) {
        fprintf(stderr, "File was not found: \"%s\"\n", argv[1]);
        return 1;
    }
    exit_status = calc_median(fp);
    fclose(fp);
    return exit_status;
}

int calc_median (FILE *fp) {
    int grade;
    int grades_arr[MAX_ARRAY_SIZE] = {0};
    int retval;
    int line_num;
    int median_mun;
    int exit_status;
    line_num = 0;
    median_mun = 0;
    exit_status = 0;
    while (1) {
        retval = fscanf(fp, "%d", &grade);
        /* no more grades left */
        if (retval == EOF) {
            break;
        }
        /* We got more than 1 argumnt at the pointer's current point */
        else if ((retval != 1)) {
            fprintf (stderr, "Error at line %d: should contain 1 grade\n"
            ,line_num+1);
            exit(1);
        }
        /* The grade we recieved is an unreal grade */
        else if ((grade > MAX_SCORE) || (grade < MIN_SCORE)) {
            fprintf (stderr, "Error at line %d: grade %d invalid\n"
            ,line_num+1,grade);
            exit_status = 1;
        }
        else {
            grades_arr[line_num] = grade;
            line_num++;
        }
    }
    /* if we recieved some real grades we sort them */
    if (line_num > 0) {
        qsort(grades_arr,line_num,sizeof(int),compare_values);
        median_mun = (line_num + 1) / 2; 
    }
    /* print the median */
    printf("%d\n", grades_arr[median_mun - 1]); 
    return exit_status;
}
int compare_values(const void *a, const void *b) {
    /** (int*)a: This casts the pointer a to a pointer of type int. 
     * It tells the compiler to treat the memory location pointed 
     * to by a as if it contains an integer.
    */
    /**
     * *((int*)a): This dereferences the pointer resulting from the cast.
     *It means "get the value at the memory location pointed to by the pointer"
    */
    /* Convert the void pointers to pointers to integers */
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    if (int_a < int_b) {
        return -1;
    } else if (int_a > int_b) {
        return 1;
    } else {
        return 0;
    }
}
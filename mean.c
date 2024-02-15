#include <stdio.h> //printf,scanf
#include <string.h> //strlen,strcat,etc 
#include <stdlib.h> //malloc, free
#define MAX_SCORE 100
#define MIN_SCORE 0
/**
 * @brief This fuction calculates from a given grades file it's mean(average)
 * @param *fp is the pointer to the grades file
 * @return 1 if the file has more than 1 argument in a line or the file
 * contains unreal grades (more than 100 or less than 0)
 * @note the function also prints the average out of the grades 
*/
int calc_mean(FILE *fp);

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
    exit_status = calc_mean(fp);
    fclose(fp);
    return exit_status;
}

int calc_mean (FILE *fp) {
    int grade;
    double avg;
    int retval;
    int line_num;
    int exit_status;
    avg = 0;
    line_num = 0;
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
            avg += grade;
            line_num++;
        }
    }
    /* if we recieved some real grades we will calculate the average and 
    print it, to avoid dividing to zero */
    if (line_num > 0) {
        printf("%0.2lf\n", avg / line_num);
    }
    /* otherwise we print 0 (avg initaite) */
    else {
        printf("%0.2lf\n", avg);
    }
    return exit_status;
}
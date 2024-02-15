#include <stdio.h> //printf,scanf
#include <string.h> //strlen,strcat,etc 
#include <stdlib.h> //malloc, free
#include <unistd.h>
#define MAX_SCORE 100
#define MIN_SCORE 0
#define DEFAULT_NUM_BINS 10
enum {ASCII_ZERO = 48, ASCII_NINE = 57};

/**
 * @brief This fuction calculates from a given grades file it's histogram
 * @param *fp is the pointer to the grades file
 * @param nbins is the number of bins given to the function, if no argument
 * for nbins given or the number is unreal the deafult is 10
 * @return 1 if the file has more than 1 argument in a line or the file
 * contains unreal grades (more than 100 or less than 0)
 * @note the function also prints the histogram out of the grades according
 * to the nubmer of bins given 
*/
int calc_hist(FILE *fp, int nbins);

/**
 * @brief This fuction checks the validation of the next argument of 
 * "-nbins" arg
 * @param argv[] is a string that contain the next argument after "-nbins" arg
 * @return atoi(argv[]) (atoi - argument to int) if the string given indeed
 * an ascii representation of an int between 1 and 100 oterwise returns 10 
*/
int check_nbins(char argv[]);

int main (int argc, char *argv[]){
    FILE *fp;
    int nbins;
    int exit_status;
    int closing_file;
    /* enum {ASCII_ZERO = 48, ASCII_NINE = 57}; */
    //ARGV[0] - name of our program

    //1 - there is only argv[0]- there is no path at all
    //2 - the path is "-"
    //3 - file can't end with "/" in linux
    
    /* in case there is no input from user */
    nbins = DEFAULT_NUM_BINS;
    fp = stdin;
    closing_file = 0;
    for (int i = 1; i < argc; ++i) {
        /* printf("Argument %d:%s\n", i, argv[i]); */
        if (!strcmp(argv[i],"-")/*  || (argv[i][strlen(argv[i])-1] == '/') */) {
           /*  printf("if 1 Arg num is %d\n", i); */
            fp = stdin;
        }
        else if (!strcmp(argv[i],"-nbins")) {
            /* meaning there is another argument after */
            /* printf("if 2 Arg num is %d\n", i); */
            if (i < argc-1) {
                nbins = check_nbins(argv[i+1]); 
            }
            i++;
        }
        /* else if ((strlen(argv[i])) > 4 && */
        /* (argv[i][strlen(argv[i])-1] == 't') && */
        /* (argv[i][strlen(argv[i])-2] == 'x') && */
        /* (argv[i][strlen(argv[i])-3] == 't')) { */
            /* printf("if 3 Arg num is %d\n", i); */
        else if (access(argv[i], F_OK) == 0) {
            fp = fopen(argv[i], "r");
            closing_file = 1;
            if (!fp) {
                fprintf(stderr, "File was not found: \"%s\"\n", argv[i]);
                return 1;
            }
        }
    }
    //Must check if file is not found:
    exit_status = calc_hist(fp, nbins);
    if (closing_file){
        fclose(fp);
    }
    return exit_status;
}

int check_nbins (char argv[]) {
    for (int i=0; i<strlen(argv); i++) {
        if (((int)argv[i] < ASCII_ZERO) || 
        ((int)argv[i] > ASCII_NINE)) {
            return DEFAULT_NUM_BINS;
        }
    }
    /* if ((atoi(argv) <= MIN_SCORE) ||  (atoi(argv) > MAX_SCORE)){ */
    /*     return DEFAULT_NUM_BINS; */
    /* } */
    return atoi(argv);
}

int calc_hist (FILE *fp, int nbins) {
    int grade;
    /* maximum 100 */
    int hist_arr[MAX_SCORE+1] = {0};
    int retval;
    int line_num;
    int exit_status;
    double bin_size;
    int grade_place;
    line_num = 0;
    exit_status = 0;
    /* to calc grade's location in hist_arr */
    bin_size = (double)MAX_SCORE / nbins;
    grade_place = 0;
    while (1) {
        retval = fscanf(fp, "%d", &grade);
        line_num++;
        /* no more grades left */
        if (retval == EOF) {
            line_num--;
            break;
        }
        /* We got more than 1 argumnt at the pointer's current point */
        else if ((retval != 1)) {
            fprintf (stderr, "Error at line %d: should contain 1 grade\n"
            ,line_num);
            line_num--;
            exit(1);
        }
        /* The grade we recieved is an unreal grade */
        else if ((grade > MAX_SCORE) || (grade < MIN_SCORE)) {
            fprintf (stderr, "Error at line %d: grade %d invalid\n"
            ,line_num,grade);
            line_num--;
            exit_status = 1;
        }
        else {
            grade_place = (int)grade/bin_size;
            hist_arr[grade_place]++;
        }
    }
    for (int i = 0; i < nbins; i++){
        printf("%.0lf-%.0lf\t%d\n", i*bin_size,
        (i < nbins - 1) ? ((i+1) * bin_size-1) : MAX_SCORE,
        (i < nbins - 1) ? hist_arr[i] : hist_arr[i] + hist_arr[nbins]);
    }
    return exit_status;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <getopt.h>
#include "vibinld.h"
#include "vibdiag.h"

int main(int argc, char **argv)
{
    double f_rotate, line_in_spectr;
    int width_spectr, n, opt;
    char numbear[lenbear], filename[lenfile];
    n = scanf("%lf %d %lf", &f_rotate, &width_spectr, &line_in_spectr);  
    if(!n) {
	printf("type correct data\n");
	exit(1);
    }
    int f_r = init_f_r(f_rotate, width_spectr, line_in_spectr);
    scanf ("%31s", numbear);
    double *x_spectr;
    double *y_spectr;
    x_spectr = malloc((line_in_spectr)*sizeof(double));
    y_spectr = malloc((line_in_spectr)*sizeof(double));
    if (argc == 1) {
	puts("type parameters\n");
	exit(1);
    }
    while((opt = getopt(argc, argv, "ifp")) != -1) {
        switch(opt) {
        case 'i':
	    srand(time(NULL));
	    init_x_spectr(width_spectr, line_in_spectr, x_spectr);
	    init_y_spectr(f_r, y_spectr);
	    init_y_spectr_bear(f_r, y_spectr, numbear);
	    print_spectr(line_in_spectr, x_spectr, y_spectr);
            break;
        case 'f':
	    if(!argv[2]) {
	    printf("type filename\n");
	    exit(2);
	    }
	    strcpy(filename, argv[2]);
	    load_spectr(line_in_spectr, x_spectr, y_spectr, filename);
            break;
        case 'p':
	    plot(line_in_spectr, x_spectr, y_spectr);
	    break;
        default:
            printf("Incorrect option\n");
            exit(EXIT_FAILURE);
    	}
    }
    skz(line_in_spectr, y_spectr);
    diagnostics(f_r, x_spectr, y_spectr);
    diagnostics_bear(f_r, x_spectr, y_spectr, numbear);
    free(x_spectr);
    free(y_spectr);
    return 0;
}

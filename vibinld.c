#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "vibinld.h"
#include "vibdiag.h"

int init_f_r(double f_rotate, int width_spectr, double line_in_spectr)
{
    return (line_in_spectr/width_spectr)*f_rotate;
}

void init_x_spectr(double width_spectr, double line_in_spectr, double *x_spectr)
{
    int i;
    double j;
    for (i=0, j=0; i <= line_in_spectr; i++, j=j+(width_spectr/line_in_spectr))
	x_spectr[i] = j;
}

void init_y_spectr(int f_r, double *y_spectr)
{
    int f_r_g, n, m;
    n = two;
    m = f_r * n;
    f_r_g = f_r;
    for(; f_r <= m; f_r += f_r_g) {
	y_spectr[f_r] = 0 + ((double)rand()/(double)(RAND_MAX) * (MAXVIB - 0));
    }
}

void init_y_spectr_bear(int f_r, double *y_spectr, char *numbear)
{
    FILE *f;
    char nbear[lenbear];
    int Din, Dout, Nrol;
    double Drol;
    int f_s, f_out, f_in;
    int b=0;
    int s=0;
    f = fopen("bearing.txt", "r");
    if (f == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }
    while(fscanf(f, "%32s %d %d %lf %d", nbear, &Din, &Dout, &Drol, &Nrol) != EOF) {
        if (strncmp(nbear, numbear, 32)==0 && (Din>0 && Dout>0 && Nrol>0 && Drol>0)) {
	    b++;
	    s++;
	    f_s = 0.4*f_r;
	    f_out = 0.4*Nrol*f_r;
	    f_in = 0.6*Nrol*f_r;
	    y_spectr[f_s] = 0 + ((double)rand()/(double)(RAND_MAX) * (MAXVIB - 0));
	    y_spectr[f_out] = 0 + ((double)rand()/(double)(RAND_MAX) * (MAXVIB - 0));
	    y_spectr[f_in] = 0 + ((double)rand()/(double)(RAND_MAX) * (MAXVIB - 0));
	}
    }
    fclose(f);
}

void print_spectr(double line_in_spectr, double *x_spectr, double *y_spectr)
{
    char filename[lenfile];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(filename, sizeof(filename), "%Y%m%d%H%M%S.csv", tm);
    FILE *f = fopen (filename, "w");
    for (int i = 0; i <= line_in_spectr; i++) {
	fprintf(f, "%.2f %.2f\n", x_spectr[i], y_spectr[i]);
    }
    fclose(f);
}

void load_spectr(double line_in_spectr, double *x_spectr, double *y_spectr, char *filename)
{
    double n, m;
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
       	printf("Can't open file for reading.\n");
       	exit(1);
    }
    for (int i = 0; i <= line_in_spectr; i++) {
	fscanf(f, "%lf %lf", &n, &m);
	x_spectr[i] = n;
	y_spectr[i] = m;
    }
    fclose(f);
}

void plot (double line_in_spectr, double *x_spectr, double *y_spectr)
{
    FILE *gnuplot = popen ("gnuplot -persist", "w");
    fprintf(gnuplot, "set title 'spectr'\n");
    fprintf(gnuplot, "plot '-' with lines\n");
    for (int i = 0; i <= line_in_spectr; i++) {
	fprintf(gnuplot, "%.2f %.2f\n", x_spectr[i], y_spectr[i]);
    }
    fprintf(gnuplot, "e\n");
    pclose(gnuplot);
}

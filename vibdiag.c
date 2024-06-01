#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "vibdiag.h"
#include "vibinld.h"

void skz(double line_in_spectr, double *y_spectr)
{
    double sk_z = 0;
    for (int i = 0; i <= line_in_spectr; i++) {
	sk_z += y_spectr[i]*y_spectr[i];
    }
    sk_z = sqrt(sk_z);
    printf("RMS: %.2f\n", sk_z);
}

void diagnostics(int f_r, double *x_spectr, double *y_spectr)
{
    double onedivtwo = y_spectr[f_r] / y_spectr[two*f_r];
    double twodivone = y_spectr[two*f_r] / y_spectr[f_r];
    if(onedivtwo > 2 && y_spectr[f_r] > 0.3 * MAXVIB)
	printf("disbalance: '%.2f - %.2f Hz'\n", y_spectr[f_r], x_spectr[f_r]);
    if(twodivone > 2 && y_spectr[2*f_r] > 0.3 * MAXVIB)
	printf("misalignment: '%.2f - %.2f Hz'\n", y_spectr[two*f_r], x_spectr[two*f_r]);
    if(onedivtwo > 1 && onedivtwo <= 2 && y_spectr[f_r] > 0.3 * MAXVIB)
	printf("mechanical slack: '%.2f - %.2f Hz', '%.2f - %.2f Hz'\n", 
    	    y_spectr[f_r], x_spectr[f_r], y_spectr[2*f_r], x_spectr[2*f_r]);
    if(twodivone >= 1 && twodivone < 2 && y_spectr[2*f_r] > 0.3 * MAXVIB)
	printf("warning: clearances: '%.2f - %.2f Hz', '%.2f - %.2f Hz'\n", 
    	    y_spectr[f_r], x_spectr[f_r], y_spectr[2*f_r], x_spectr[2*f_r]);
}

void diagnostics_bear(int f_r, double *x_spectr, double *y_spectr, char *numbear)
{
    int b=0; int s=0;
    char nbear[lenbear];
    int Din, Dout, Nrol;
    int f_cage, f_out, f_in;
    double Drol;
    FILE *f = fopen("bearing.txt", "r");
    if (f == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }
    while(fscanf(f, "%32s %d %d %lf %d", nbear, &Din, &Dout, &Drol, &Nrol) != EOF) {
        if (strncmp(nbear, numbear, 32)==0 && (Din>0 && Dout>0 && Nrol>0 && Drol>0)) {
	    b++;
	    s++;
	f_cage = 0.4 * f_r;		
	if(y_spectr[f_cage] > 0.3 * MAXVIB)
	    printf("defect bearing: '%.2f - FTF %.2f Hz'\n", y_spectr [f_cage], x_spectr[f_cage]);
	f_out = 0.4*Nrol*f_r;
	if(y_spectr[f_out] > 0.3 * MAXVIB)
	    printf("defect bearing: '%.2f - BPFO %.2f Hz'\n", y_spectr [f_out], x_spectr[f_out]);
	f_in = 0.6*Nrol*f_r;
	if(y_spectr[f_in] > 0.3 * MAXVIB)
	    printf("defect bearing: '%.2f - BPFI %.2f Hz'\n", y_spectr [f_in], x_spectr[f_in]);
		}
	}
	if (s==0) 
	    printf("Type bear '%s' with correct data in file 'bearing.txt'\n", numbear);
	if (b>1)
	    printf("Found %d copeis of bear '%s'. Choose one copy and delete rest in file 'bearing.txt'", b, numbear); 
	fclose(f);
}

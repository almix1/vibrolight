#ifndef VIBINLD_H_SENTRY
#define VIBINLD_H_SENTRY

#define MAXVIB 4.5

enum garmony {one = 1, two = 2, three = 3, four = 4, five = 5,
	six = 6, seven = 7, eight = 8, nine = 9, ten = 10};

enum {lenbear = 32, lenfile = 64};

int init_f_r(double f_rotate, int width_spectr, double line_in_spectr);
void init_x_spectr(double width_spectr, double line_in_spectr, double *x_spectr);
void init_y_spectr(int f_r, double *y_spectr);
void init_y_spectr_bear(int f_r, double *y_spectr, char *numbear);
void print_spectr(double line_in_spectr, double *x_spectr, double *y_spectr);
void load_spectr(double line_in_spectr, double *x_spectr, double *y_spectr, char *filename);
void plot (double line_in_spectr, double *x_spectr, double *y_spectr);

#endif

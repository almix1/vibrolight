vib: vib.c vibinld.c vibinld.h vibdiag.c vibdiag.h
	gcc -Wall -g vib.c vibinld.c vibdiag.c -lm -o vib

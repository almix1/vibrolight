The Vibrolite program is an attempt at automated vibration spectrum diagnostics. 
With a certain degree of probability, the program identifies defects such as: 
disbalance, misalignment, and rolling bearing defects 
(if bearing characteristics are present in the file 'bearing.txt'). 
Vibrolite is a test program and should be verified when analyzing 
real spectrum data exported to a file containing two columns, 
the first with frequencies, the second with values at these frequencies. 
Spectrum displayed using the gnuplot program.

After starting the program, you need to sequentially enter the rotational frequency, 
spectrum width, and the number of lines in the spectrum. 
The accuracy of the analysis will depend on how closely the entered 
data matches that in the connected file. As an example, 
the program can generate a file with data for diagnostics and conduct a diagnostics itself.
To do this, you need to run it with the -i parameter:
./vib -i or ./vib -ip to display the spectrum in the gnuplot program. 
You can connect a file for analysis using:
./vib -f or ./vib -fp to display the spectrum in the gnuplot program.

The program uses the file 'bearing.txt', which contains the characteristics 
of rolling bearings necessary for calculating possible rolling bearing defects. 
The file contains a few number of bearings, if necessary, 
you can add the necessary bearings and their characteristics to file 'bearing.txt'.

Example_1 of starting the program with spectrum generation: ./vib -i
25 1000 2000 /* type parameters */
205 /* type number of bearing */
/* Result: */
RMS: 6.05
disbalance: '4.45 - 25.00 Hz'
defect bearing: '3.75 - BPFO 90.00 Hz'
defect bearing: '1.56 - BPFI 135.00 Hz'
The program creates a file with a name that includes the date, time, and csv extension.

Example_1 of starting the program with data from a file and displaying the spectrum 
in the gnuplot program:
./vib -fp 20240601121644.csv
25 1000 2000 /* type the same parameters */
205 /*type the same number of bearing */
/* Result: */
RMS: 6.05
disbalance: '4.45 - 25.00 Hz'
defect bearing: '3.75 - BPFO 90.00 Hz'
defect bearing: '1.56 - BPFI 135.00 Hz'

Example_2 of starting the program with spectrum generation: ./vib -i
10 100 200 /* type parameters */
205 /* type number of bearing */
/* Result: */
RMS: 5.75
disbalance: '4.04 - 10.00 Hz'
defect bearing: '3.12 - BPFO 36.00 Hz'
defect bearing: '2.55 - BPFI 53.50 Hz'
The program creates a file with a name that includes the date, time, and csv extension.

Example_2 of starting the program with data from a file and displaying the spectrum 
in the gnuplot program:
./vib -fp 20240601141354.csv
10 100 200 /* type the same parameters */
205 /*type the same number of bearing */
/* Result: */
RMS: 5.75
disbalance: '4.04 - 10.00 Hz'
defect bearing: '3.12 - BPFO 36.00 Hz'
defect bearing: '2.55 - BPFI 53.50 Hz'

Accordingly:
25 or 10 - this is the rotational frequency, 1000 or 100 - the spectrum width, 
2000 or 200 - the number of lines in the spectrum.
205 - bearing number.

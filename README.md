# HiCKey

This is the software package for detecting TAD boundaries in HiC data. The package is written in C++. It contains 1 header file: HiCKey.h; 2 source files: HiCKey.cpp and main.cpp. The compiled application is HiCKey.exe. We will soon add an R package for those not familiar with C++.

# Usage:

It's easy to use. We have a sample HiC data in fold "examples".

"BrownianP.txt" is the simulated tail distribution of our test statistic, which is essential for every analysis.

"nijchr16.txt" is a Human ES Cell Normalized Matrix downloaded from Ren Lab http://chromosome.sdsc.edu/mouse/hi-c/download.html

"nijchr16_list.txt" is the list form HiC data of above matrix, Tad separated, containing only nonzero reads with their row and column indices. Our package can read both list form data file and the above matrix form file.

After you download HiCKey.exe (or you download all 3 code files and compile yourself), for windows users you can open Command Prompt, change drive to the path containing HiCKey.exe and input following command line arguments (as an example):

HiCKey C:/Users/Yingru/Source/Repos/HiCKey/examples/nijchr16.txt C:/Users/Yingru/Source/Repos/HiCKey/examples/BrownianP.txt 5 0.05 0.0005

First argument is the name of the application, second is the path of you HiC data, third is the path of "BrownianP.txt", fourth is the lower bound of TAD size, fifth is the significance level alpha0 for testing a TAD boundary, sixth is the significance level alpha1 for assigning hierarchical levels (according to our paper). If you omit the sixth argument then HiCKey will not assign hierarchical orders.

The output file would be named as "nijchr16_output.txt" in the same fold as your data file. In the output file there would be three columns: first the indices for change-points, second their hierarchical orders and third local p-values of each change-point.

# A side note:

sometimes list form HiC data files are indexed by their resolution like the folowing 50k resolution data:

0	0	16.0

0	50000	4.0

50000	50000	133.0

100000	100000	75.0

50000	150000	1.0

100000	150000	7.0

150000	150000	20.0

0	200000	2.0

50000	200000	9.0

100000	200000	28.0

150000	200000	10.0

200000	200000	244.0

100000	250000	10.0

200000	250000	32.0

250000	250000	23.0

you shold divide the row and column indices by their resolution first making it like:

0	0	16

0	1	4

1	1	133

2	2	75

1	3	1

2	3	7

3	3	20

0	4	2

1	4	9

2	4	28

3	4	10

4	4	244

2	5	10

4	5	32

5	5	23

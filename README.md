# HiCKey

This is the software HiCKey for detecting TAD boundaries and their hierarchical strucutre in HiC data. For the detail of our methodology please refer to "Decipher hierarchical organization of topologically associated domains through change-point testing". This software package is written in C++. It contains 1 header file: HiCKey.h; 2 source files: HiCKey.cpp and main.cpp. The compiled application is HiCKey.exe. We will also incorporate the C++ code into an R package.

# Usage:

We have two sample HiC datasets in the folder "examples".

The folder "examples" contains three files:

"BrownianP.txt" is the simulated distribution of our test statistic, which is essential for every analysis.

"nijchr16.txt" is a Human ES Cell Normalized Hi-C Matrix downloaded from Ren Lab http://chromosome.sdsc.edu/mouse/hi-c/download.html

"nijchr16_list.txt" is the list form of the matrix, Tab separated, containing only nonzero reads with their row and column indices(0 based).

Our software can read both the matrix and list form data files.

After you download HiCKey.exe (or you download all 3 code files and compile yourself), for windows users you can open Command Prompt, change drive to the path containing HiCKey.exe and input following command line arguments (as an example):

HiCKey C:/XXXX/nijchr16.txt C:/XXXX/BrownianP.txt 5 0.05 0.0005

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

you shold divide the row and column indices by their resolution first making it like the following, Tab separated.

0	0	16.0

0	1	4.0

1	1	133.0

2	2	75.0

1	3	1.0

2	3	7.0

3	3	20.0

0	4	2.0

1	4	9.0

2	4	28.0

3	4	10.0

4	4	244.0

2	5	10.0

4	5	32.0

5	5	23.0

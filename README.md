# HiCKey

This is the software HiCKey for detecting TAD boundaries and their hierarchical strucutre in HiC data. For the detail of our methodology please refer to "Decipher hierarchical organization of topologically associated domains through change-point testing". This software package is written in C++. It contains 1 header file: HiCKey.h; 2 source files: HiCKey.cpp and main.cpp. The compiled application is HiCKey.exe. We will also incorporate the C++ code into an R package.

# Examples:

We have two sample HiC datasets in the folder "examples".

The folder "examples" contains three files:

"BrownianP.txt" is the simulated distribution of our test statistic, which is essential for every analysis.

"nijchr16.txt" is a Human ES Cell Normalized Hi-C Matrix downloaded from Ren Lab http://chromosome.sdsc.edu/mouse/hi-c/download.html

"nijchr16_list.txt" is the list form of the matrix, Tab separated, containing only nonzero reads with their row and column indices(0 based).

Our software can read both the matrix and list form data files.

# Usage:

To run the program, you need 5 arguments as follows.

1. fileName: path and name of you Hi-C dataset (either matrix or list form, our program can read both).

2. fileNameP: path and name of the "BrownianP.txt".

3. cv: lower bound of TAD size (as explained in our paper).

4. sv: significance level alpha0 for testing TAD boundaries (as explained in our paper).

5. hv: hierarchical p-value cutoff alpha1 for identifying nested TADs (as explained in our paper). This argument is optional. If it's ommited, then HiCKey will not assign hierarchical order of the TAD boundaries.

After you download HiCKey.exe (or download all 3 code files and compile), windows users can open Command Prompt, change drive and path to the folder containing HiCKey.exe then input command line arguments:

HiCKey fileName fileNameP cv sv hv

or

HiCKey fileName fileNameP cv sv

For example on author's computer running the "nijchr16.txt" is like the following pic shows.

![Untitled](https://user-images.githubusercontent.com/60941766/84854383-7caebf80-b02f-11ea-852a-c1c88afb6153.png)

# Output

For the above example the output file would have name "nijchr16_output.txt" located in the same folder as the dataset file "nijchr16.txt". The output file has three columns:

First column is the indices for change-points (TAD boundaries).

Second column is their hierarchical orders. 1 means top layer, it goes to bottom layer as the order increases (as explained in our paper). If the "hv" argument was ommited when you run the program, then all the orders would be 1.

Third column is the p-values of the boundaries.

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

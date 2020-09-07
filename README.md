# HiCKey

This is the software HiCKey for detecting TAD boundaries and their hierarchical strucutre in HiC data. For the detail of our methodology please refer to "Decipher hierarchical organization of topologically associated domains through change-point testing". This software package was compiled by Visual C++ and GNU C++14. It contains 1 header file: "HiCKey.h"; 2 source files: "HiCKey.cpp" and "main.cpp". The compiled application are "HiCKey.exe" for Windows and "hickey_linux.exe" for Linux.

# Examples:

We have two sample HiC datasets in the folder "examples".

The folder "examples" contains three files:

"BrownianP.txt" is the simulated distribution of our test statistic, which is essential for every analysis.

"nijchr16.txt" is a Human ES Cell Normalized Hi-C Matrix downloaded from Ren Lab http://chromosome.sdsc.edu/mouse/hi-c/download.html

"nijchr16_list.txt" is the list form of the matrix, Tab separated, containing only nonzero reads with their row and column indices(0 based).

Our software can read both the matrix and list form data files.

# Normalization:

HiCKey requres normalized Hi-C matrices, that the effect of power law decay removed. Usually the observed over expected precedure is preferred, as many Hi-C data are released in this form. Otherwise we suggest a simple normalization method. Let Y = y_{ij} be raw reads, apply x_{ij} = y_{ij}/(|i-j|^a) to do the transform. the parameter a should be estimated from data close to main diagonal where most of the power law effect pronounced.

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

"hickey_linux.exe" is used for linux system in exactly the same way. Except the first argument should be "~/hickey_linux" instead of "HiCKey".

If the terminal shows "bash: ~/hickey_linux: Permission denied", try input "chmod u+x ~/hickey_linux" first. Then execute the programe.

# Output

For the above example the output file would have name "nijchr16_output.txt" located in the same folder as the dataset file "nijchr16.txt". The output file has three columns:

First column is the indices for change-points (TAD boundaries).

Second column is their hierarchical orders. 1 means top layer, it goes to bottom layer as the order increases (as explained in our paper). If the "hv" argument was ommited when you run the program, then all the orders would be 1.

Third column is the p-values of the boundaries.

# Format of list form datasets

Sometimes list form Hi-C dataset files are indexed by their resolution like the folowing 50k resolution data. The first column is row indices, second column is column indices and third column is count reads.

0 0 16.0

0 50000 4.0

50000 150000  5.0

User should first divide the row and column indices by their resolution, making it looks like the following tab separated file.

0	0	16.0

0	1	4.0

1	3	5.0

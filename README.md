# HiCKey

This is the software HiCKey for detecting TAD boundaries and their hierarchical strucutre in HiC data. For the details of our methodology, please refer to "Decipher hierarchical organization of topologically associated domains through change-point testing". This software package was compiled by Visual C++ and GNU C++14. It contains 1 header file: "HiCKey.h"; 2 source files: "HiCKey.cpp" and "main.cpp". The compiled application are "HiCKey.exe" for Windows and "hickey" for Linux.

# Examples:

There are four sample HiC datasets in the folder "examples".

"nijchr16.txt" is a Human ES Cell Normalized Hi-C Matrix downloaded from Ren Lab (http://chromosome.sdsc.edu/mouse/hi-c/download.html).

"nijchr16_list.txt" is the list form of the matrix, Tab separated, containing only nonzero reads with their row and column indices (0 based).

"chr21_50kb.RAWobserved" is one of the unnormalized HiC matrices produced by Rao (2015) and downloaded from the Gene Expression Omnibus (GEO) database (http://www.ncbi.nlm.nih.gov/geo/).

"samp2n.txt" is the hierarchical TADs example demonstrated in our paper, it was produced by Forcato (2017) and normalized.

# Normalization:

HiCKey requires normalized Hi-C matrix, that the effect of power law decay removed. Usually the observed over expected precedure is preferred, as many Hi-C datasets are released in this form. Otherwise we suggest a simple normalization method. Let Y = y_{ij} be raw reads, apply x_{ij} = y_{ij}/(|i-j|^a) to do the transform. the parameter 'a' should be estimated from elements close to the main diagonal where most of the power law effect pronounced.

# Usage:

"BrownianP.txt" is the simulated distribution of our test statistic, "arguments.txt" contains the parameter settings. They are essential for every analysis.

To run the program, you need to specify 6 arguments in the file "arguments.txt":

1st line is Hi-C matrix path and name \nijchr16.txt

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

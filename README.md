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

# Arguments setting:

"BrownianP.txt" is the simulated distribution of our test statistic, "arguments.txt" is arguments setting. They are essential for every analysis.

You need to specify 6 arguments in the file "arguments.txt"

1st line is the path and name of Hi-C matrix: ~/xxxx

2nd line is the path and name of "BrownianP": ~/BrownianP.txt

3rd line is Hi-C matrix form and resolution. If it is matrix form then input 'm', if it is list form then input resolution.

4st line is the lower bound of TAD size.

5st line is alpha0 to test if a change-point is significant.

6st line is alpha1 for identifying nested TADs. If it is 0, then HiCKey will not output hierarchical orders.

For example, "nijchr16.txt" can be:

C:/Users/Yingru/Source/Repos/HiCKey/examples/nijchr16.txt \
C:/Users/Yingru/Source/Repos/HiCKey/examples/BrownianP.txt \
m \
5 \
0.05 \
0.00005

"nijchr16_list.txt" can be:

# Usage
After you download HiCKey.exe or hickey (or download all 3 code files and compile), windows users can open Command Prompt, change drive to the folder of HiCKey.exe then type in:

HiCKey ~/arguments.txt

Linux users can type in:

~/hickey ~/arguments.txt

If the terminal shows "bash: ~/hickey: Permission denied", try input "chmod u+x ~/hickey" first and then execute the programe.

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

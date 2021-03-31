# HiCKey

This is the software HiCKey for detecting TAD boundaries and their hierarchical strucutre in HiC data. For the details of our methodology, please refer to "Decipher hierarchical organization of topologically associated domains through change-point testing". This software package was compiled by Visual C++ and GNU C++14. It contains 1 header file: "HiCKey.h"; 2 source files: "HiCKey.cpp" and "main.cpp". The compiled application are "HiCKey.exe" for Windows and "hickey" for Linux.

# Examples

There are four sample HiC datasets in the folder "examples".

"nijchr16.txt" is a Human ES Cell Normalized Hi-C Matrix downloaded from Ren Lab (http://chromosome.sdsc.edu/mouse/hi-c/download.html).

"nijchr16_list.txt" is the list form of the matrix, Tab separated, containing only nonzero reads with their row and column indices (0 based).

"chr21_50kb.RAWobserved" is one of the unnormalized HiC matrices produced by Rao (2015) and downloaded from the Gene Expression Omnibus (GEO) database (http://www.ncbi.nlm.nih.gov/geo/).

"samp_nested.txt" is the Figure 4 case b in our paper, it was produced by Forcato (2017). We normalized its upper triangular part (see the following section).

# Normalization

HiCKey requires normalized Hi-C matrix, that the effect of power law decay removed. Usually the observed over expected precedure is preferred, as many Hi-C datasets are released in this form. Otherwise we suggest a simple normalization method. Let Y = y_{ij} be raw reads, apply x_{ij} = y_{ij}/(|i-j|^a) to do the transform. the parameter 'a' should be estimated from elements close to the main diagonal where most of the power law effect pronounced.

# Arguments setting

"BrownianP.txt" is the simulated distribution of our test statistic, which is always needed.

You need to specify 6 arguments in the file "arguments_HiCKey.txt" or "arguments_hickey".

1st line is the path and name of Hi-C matrix: ~/xxxx \
2nd line is the path and name of "BrownianP": ~/BrownianP.txt \
3rd line is Hi-C matrix form and resolution. If it is matrix form then input 'm', if it is list form then input resolution. \
4st line is the lower bound of TAD size. \
5st line is alpha0 to test if a change-point is significant. \
6st line is alpha1 for identifying nested TADs. If it is 0, then HiCKey will not output hierarchical orders.

For example, "nijchr16.txt" can be:

C:/Users/Yingru/Source/Repos/HiCKey/examples/nijchr16.txt \
C:/Users/Yingru/Source/Repos/HiCKey/examples/BrownianP.txt \
m \
5 \
0.05 \
0.00005

"nijchr16_list.txt" can be:

C:/Users/Yingru/Source/Repos/HiCKey/examples/nijchr16_list.txt \
C:/Users/Yingru/Source/Repos/HiCKey/examples/BrownianP.txt \
1 \
5 \
0.05 \
0.00005

"chr21_50kb.RAWobserved" can be:

C:/Users/Yingru/Source/Repos/HiCKey/examples/chr21_50kb.RAWobserved \
C:/Users/Yingru/Source/Repos/HiCKey/examples/BrownianP.txt \
50000 \
5 \
0.05 \
0.00005

# Usage
After you download HiCKey.exe or hickey (or download all 3 code files and compile), windows users can open Command Prompt, change drive to the folder of HiCKey.exe then type in:

HiCKey ~/arguments_HiCKey.txt

Linux users can type in:

~/hickey ~/arguments_hickey

If the terminal shows "bash: ~/hickey: Permission denied", try input "chmod u+x ~/hickey" first and then execute the programe.

# Output

For Hi-C matrix with name "xxxx" the output file would have name "xxxx_output" in the same folder. The output file has three columns:

The first column is the locations of change-points (start point of a TAD).

The second column is their hierarchical orders. '1' means top layer, it goes to bottom layer as the order increases (as explained in our paper). If the 6th line in "arguments.txt" is '0', then all orders would be '1'.

The third column is the p-values of the change-points.

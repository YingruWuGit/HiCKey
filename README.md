# HiCKey

This is the software HiCKey for detecting TAD boundaries and their hierarchical strucutre in HiC data. For the details of our methodology, please refer to ```Xing, H., Wu, Y., Zhang, M.Q. et al. Deciphering hierarchical organization of topologically associated domains through change-point testing. BMC Bioinformatics 22, 183 (2021)``` (https://rdcu.be/clEFG). It was compiled by Visual C++ and GNU C++14. It contains 1 header file "HiCKey.h"; 2 source files "HiCKey.cpp" and "main.cpp". The compiled applications are "HiCKey.exe" for Windows and "hickey" for Linux.

# R package

In another repository "HiCKeyR" (https://github.com/YingruWuGit/HiCKeyR) we have the R package of HiCKey. The R package was constructed by Rcpp with the same C++ code here. There is a new function in the R package that returns a submatrix of the HiC matrix, so user can draw a heatmap to show the segmentation result.

# Examples

There are four sample HiC datasets in the folder "examples".

"nijchr16.txt" is a Human ES Cell Normalized Hi-C Matrix downloaded from Ren Lab (http://chromosome.sdsc.edu/mouse/hi-c/download.html).

"nijchr16_list.txt" is the list form of the matrix, Tab separated, containing only nonzero reads with their indices (0 based). The first column is row index, the second column is column index and the thrid column is count read.

"chr21_50kb.RAWobserved" is one of the unnormalized HiC matrices produced by Rao (2015) and downloaded from the Gene Expression Omnibus (GEO) database (http://www.ncbi.nlm.nih.gov/geo/). It is in list form similar with "nijchr16_list.txt", just its indices are multiplied by resolution.

"samp_nested.txt" is the Figure 4 case b in our paper, it was produced by Forcato (2017). We normalized its upper triangular part (see the following section).

# Normalization

HiCKey requires normalized HiC matrix, that the effect of power law decay removed. Usually the observed over expected precedure is preferred, as many HiC datasets are released in that form. Otherwise we suggest a simple normalization method. Let <img src="https://render.githubusercontent.com/render/math?math=y_{ij}"> be raw reads, apply <img src="https://render.githubusercontent.com/render/math?math=x_{ij}=y_{ij}/(|i-j|^a)"> to do the transform. the parameter <img src="https://render.githubusercontent.com/render/math?math=a"> should be estimated from elements close to the main diagonal where most of the power law effect pronounce.

# Arguments setting

"BrownianP.txt" is the simulated distribution of our test statistic, which is needed in each run.

User needs to specify 6 arguments in the file "arguments_HiCKey.txt" or "arguments_hickey".

1st line is the path and name of HiC matrix: ~/xxxx \
2nd line is the path and name of "BrownianP": ~/BrownianP.txt \
3rd line is HiC matrix form and resolution. If it is matrix form then input 'm', if it is list form then input resolution. \
4th line is the lower bound of TAD size. \
5th line is alpha0 to test if a change-point is significant. \
6th line is alpha1 for identifying nested TADs. If it is 0, then HiCKey will not output hierarchical orders.

For example, if HiC data is "nijchr16.txt", then the "arguments_HiCKey.txt" can be:
```
C:/Users/Yingru/Source/Repos/HiCKey/examples/nijchr16.txt
C:/Users/Yingru/Source/Repos/HiCKey/examples/BrownianP.txt
m
5
0.05
0.00005
```
If HiC data is "nijchr16_list.txt", then the "arguments_HiCKey.txt" can be:
```
C:/Users/Yingru/Source/Repos/HiCKey/examples/nijchr16_list.txt
C:/Users/Yingru/Source/Repos/HiCKey/examples/BrownianP.txt
1
5
0.05
0.00005
```
If HiC data is "chr21_50kb.RAWobserved", then the "arguments_HiCKey.txt" can be:
```
C:/Users/Yingru/Source/Repos/HiCKey/examples/chr21_50kb.RAWobserved
C:/Users/Yingru/Source/Repos/HiCKey/examples/BrownianP.txt
50000
5
0.05
0.00005
```

# Usage

Download HiCKey.exe (or hickey for Linux), arguments_HiCKey.txt (arguments_hickey), BrownianP.txt and prepare your HiC data file.

Modify the arguments in arguments_HiCKey.txt (arguments_hickey).

For Windows user, open Command Prompt, change directory to the folder containing HiCKey.exe and arguments_HiCKey.txt, then input:
```
HiCKey arguments_HiCKey.txt
```
For Linux user open Terminal, change directory and input:
```
./hickey ./arguments_hickey
```
If it shows ```bash: ./hickey: Permission denied```, try input ```chmod u+x ./hickey``` first and then execute the program.

# Output

For HiC data file with name "xxxx" the output file would be named as "xxxx_output" in the same directory. The output file has three columns:

The first column is the locations of change-points (start of a TAD).

The second column is their hierarchical orders. '1' means top layer, it goes to bottom layer as the order increases (as explained in our paper). If the 6th line in the "arguments_HiCKey.txt" is 0, then all orders would be '1'.

The third column is the p-values of the change-points.

# HiCKey

This is HiCKey for detecting TAD boundaries and their hierarchical structure in HiC data. For the details of our methodology, please refer to `Deciphering hierarchical organization of topologically associated domains through change-point testing. BMC Bioinformatics (2021)` (https://rdcu.be/clEFG). One of the advantages of HiCKey is that it outputs p-values of the detected boundaries.

- "HiCKey.h", "HiCKey.cpp" and "main.cpp" are the source files
- "HiCKey.exe" is the application for Windows compiled by Visual C++ under C++14 standard
- "hickey" is the application for Linux compiled by GNU under C++14 standard

# R package

In another repository "HiCKeyR" (https://github.com/YingruWuGit/HiCKeyR) we have the R package of HiCKey. The R package was constructed by Rcpp with the same source code. There is one more function in the R package that returns a sub-matrix of segmented HiC data, so user can draw a heatmap to show the results. The R package works in Windows and MacOS.

# Examples

There are four sample HiC datasets in the folder "examples".

- "nijchr16.txt" is a Human ES Cell Normalized Hi-C Matrix downloaded from Ren Lab (http://chromosome.sdsc.edu/mouse/hi-c/download.html).
- "nijchr16_list.txt" is the list form of the above matrix, Tab separated, containing only nonzero reads with their indices (0 based). The first column is row indices, the second column is column indices and the thrid column is count reads.
- "chr21_50kb.RAWobserved" is one of the unnormalized HiC matrices with resolution 50k produced by Rao (2015) and downloaded from the Gene Expression Omnibus (GEO) database (http://www.ncbi.nlm.nih.gov/geo/). It is in list form similar with "nijchr16_list.txt", just its indices are multiplied by resolution.
- "samp_nested.txt" is the Figure 4 case b in our paper, it was produced by Forcato (2017). We normalized its upper triangular part (see the following section).

# Normalization

HiCKey requires normalized HiC data, that the effect of power law decay removed. Usually the observed over expected precedure is preferred, as many HiC datasets are released in that form. Otherwise, we suggest a simple normalization method. Let <img src="https://render.githubusercontent.com/render/math?math=y_{ij}"> be raw reads, apply <img src="https://render.githubusercontent.com/render/math?math=x_{ij}=y_{ij}/(|i-j|^a)"> to do the transform. the parameter <img src="https://render.githubusercontent.com/render/math?math=a"> can be estimated from reads close to the main diagonal of the HiC matrix where most of the power law effect pronounce. Specifically, collect non-zero <img src="https://render.githubusercontent.com/render/math?math=y_{ij}"> and use simple linear regression <img src="https://render.githubusercontent.com/render/math?math=a-a">, in which <img src="https://render.githubusercontent.com/render/math?math=x_{ij}"> treated as unknown error, to estimate <img src="https://render.githubusercontent.com/render/math?math=a">.

# Arguments setting

"BrownianP.txt" is the simulated distribution of our test statistic, which is needed in each analysis.

User needs to specify 6 arguments in the file "arguments_HiCKey.txt" (for Windows) or "arguments_hickey" (for Linux).

- 1st line is the path and name of HiC data
- 2nd line is the path and name of "BrownianP.txt"
- 3rd line is HiC data form or resolution. If it is in matrix form then input 'm', if it is in list form then input the resolution
- 4th line is the lower bound of TAD size
- 5th line is threshold alpha0 to test if a boundary (change-point) is significant
- 6th line is threshold alpha1 for identifying nested TADs. If it is 0, then HiCKey will ignore hierarchical orders

For example, if HiC data is "nijchr16.txt", the "arguments_HiCKey.txt" can be:
```
C:/Users/Andrew/Documents/GitHub/HiCKey/examples/nijchr16.txt
C:/Users/Andrew/Documents/GitHub/HiCKey/BrownianP.txt
m
5
0.05
0.00005
```
If HiC data is "nijchr16_list.txt", the "arguments_HiCKey.txt" can be:
```
C:/Users/Andrew/Documents/GitHub/HiCKey/examples/nijchr16_list.txt
C:/Users/Andrew/Documents/GitHub/HiCKey/BrownianP.txt
1
5
0.05
0.00005
```
Note: the resolution should be 1 if the list form HiC data was derived form matrix form.

If HiC data is "chr21_50kb.RAWobserved", the "arguments_HiCKey.txt" can be:
```
C:/Users/Andrew/Documents/GitHub/HiCKey/examples/chr21_50kb.RAWobserved
C:/Users/Andrew/Documents/GitHub/HiCKey/BrownianP.txt
50000
5
0.05
0.00005
```

# Usage

Download HiCKey.exe (hickey, or compile the source code), arguments_HiCKey.txt (arguments_hickey), BrownianP.txt and prepare your HiC data file.

Modify the arguments in arguments_HiCKey.txt (arguments_hickey).

For Windows user, open Command Prompt, change directory to the folder containing HiCKey.exe and arguments_HiCKey.txt, then input:
```
HiCKey arguments_HiCKey.txt
```
For Linux user, open Terminal, change directory to the folder containing hickey and arguments_hickey, then input:
```
./hickey ./arguments_hickey
```
If it shows `bash: ./hickey: Permission denied`, try `chmod u+x ./hickey` first and then execute the program.

# Output

For HiC data file with name "xxxx", the output file would be named as "xxxx_output.txt" in the same directory. The output file has three columns:

- The first column is the locations of boundaries (start of TADs).
- The second column is hierarchical orders. '1' indicates top (outer) layer, it goes to bottom layer as the order increases, as explained in our paper. If the 6th line in the "arguments_HiCKey.txt" is 0, then all orders would be '1'.
- The third column is the p-values of the boundaries.

HiCKey also generates a BED file named as "xxxx_TADs.bed" in the same directory. It also has three columns:

- The first column is the start of TADs
- The second column is the end of TADs
- The third column is the hierarchical order of TADs (defined as the highest hierarchical order of its start and end boundaries)

The rows in the BED file are arranged in this way. Suppose that the highest order of all boundaries is 3, HiCKey records all TADs with order <= 3 in the first batch, then all TADs with order <= 2 in the second batch, and all TADs with order <=1 in the last batch.

# References

Rao SSP, Huntley MH, Durand N, Stamenova EK, Bochkov I, Robinson JT, et al. A 3D map of the human genome at kilobase resolution reveals principles of chromatin looping. Cell. 2015;159(7):1665–80.

Forcato M, Nicoletti C, Pal K, Livi C, Ferrari F, Bicciato S. Comparison of computational methods for Hi-C data analysis. Nat Methods. 2017;14:679–85.

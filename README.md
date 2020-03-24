# HiCKey

This is the software package for detecting TAD boundaries in HiC data. The package is written in C++. It contains 1 header file: HiCKey.h; 2 source files: HiCKey.cpp and main.cpp. The compiled application is HiCKey.exe. We will soon add an R package for those not familiar with C++.

It's easy to use. We have a sample HiC data in fold "examples".

"BrownianP.txt" is the simulated tail distribution of our test statistic, which is essential for every analysis.

"nijchr16.txt" is a Human ES Cell Normalized Matrix downloaded from Ren Lab http://chromosome.sdsc.edu/mouse/hi-c/download.html
"nijchr16_list.txt" is the list form HiC data of above matrix, containing only nonzero reads with their row and column indices. Our package can read both this list form data file and the above matrix for file.

After you download HiCKey.exe (or you download all 3 code files and compile yourself), for windows users you can open Command Prompt, change drive to the fold containing HiCKey.exe and input following command line arguments:



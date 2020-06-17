#include "HiCKey.h"
//command line: HiCKey C:/Users/Yingru/Source/Repos/HiCKey/examples/nijchr16.txt C:/Users/Yingru/Source/Repos/HiCKey/examples/BrownianP.txt 5 0.05 0.0005

int main(int argc, char* argv[]) {
	int cv = std::atoi(argv[3]);
	double sv = std::atof(argv[4]);
	double hv = 0.0;
	if (argc > 5)
		hv = std::atof(argv[5]);

	Hic sample(argv[1], argv[2], cv, sv, hv);
	sample.topDown();
	sample.pruning();
	sample.bottomUp();
	sample.outPut();
	return 0;
}

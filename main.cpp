#include "HiCKey.h"
//HiCKey C:/Users/Yingru/Source/Repos/hic/nijchr16_matrix.txt C:/Users/Yingru/Source/Repos/hic/BrownianP.txt 5 0.05 0.005

int main(int argc, char* argv[]) {
	int _cv = std::atoi(argv[3]);
	double _sv = std::atof(argv[4]);
	double _hv = 0.0;
	if (argc > 5)
		_hv = std::atof(argv[5]);

	Hic sample(argv[1], argv[2], _cv, _sv, _hv);
	sample.topDown();
	sample.pruning();
	sample.bottomUp();
	sample.outPut();
	return 0;
}

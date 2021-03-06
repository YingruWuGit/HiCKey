#include "HiCKey.h"

int main(int argc, char* argv[]) {
	std::ifstream fin(argv[1]);
	std::string arg1, arg2, arg3, arg4, arg5, arg6;
	std::getline(fin, arg1);
	std::getline(fin, arg2);
	std::getline(fin, arg3);
	std::getline(fin, arg4);
	std::getline(fin, arg5);
	std::getline(fin, arg6);
	fin.close();
	Hic sample(arg1, arg2, ((arg3 == "m") ? 0 : std::stoi(arg3)), std::stoi(arg4), std::stof(arg5), std::stof(arg6));
	sample.topDown();
	sample.pruning();
	sample.bottomUp();
	sample.outPut();
	return 0;
}

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <deque>
#include <map>
#include <utility>
#include <cstdlib>
#include <numeric>
#include <algorithm>


//declaration of Hic class
class Hic {
	const std::string fileName;
	const std::string fileNameP;
	const int cv;
	double sv;
	double hv;
	std::vector<std::vector<std::pair<int, double>>> countMatrix;
	std::vector<double> brownianP;
public:
	std::vector<int> cpI;
	std::vector<int> cpS;
	std::vector<double> pValue;

	Hic(const char* _fileName, const char* _fileNameP, const int _cv, const double _sv, const double _hv = 0.0);
	void topDown();
	void topDown(int cpt0, int cpt1);
	void testCp(int cp, int store);
	void pruning();
	void bottomUp();
	void outPut();
	std::vector<std::vector<double>> subMatrix(int s, int e);
};

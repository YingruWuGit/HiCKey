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
	const std::string _fileName;
	const std::string _fileNameP;
	const int _cv;
	double _sv;
	double _hv;
	std::vector<std::vector<std::pair<int, double>>> _countMatrix;
	std::vector<double> _brownianP;
public:
	std::vector<int> _cpI;
	std::vector<int> _cpS;
	std::vector<double> _pValue;

	Hic(const char* fileName, const char* fileNameP, const int cv, const double sv, const double hv = 0.0);
	void topDown();
	void topDown(int cpt0, int cpt1);
	void testCp(int cp, int store);
	void pruning();
	void bottomUp();
	void outPut();
	std::vector<std::vector<double>> subMatrix(int s, int e);
};

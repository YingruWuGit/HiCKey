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


class Hic {
	const std::string _fileName; //HiC data file
	const std::string _fileNameP; //distribution file
	const int _in_form; //input HiC data form
	const int _cv; //xi
	double _sv; //alpha0
	double _hv; //alpha1
	std::vector<std::vector<std::pair<int, double>>> _countMatrix; //stored HiC data
	std::vector<double> _brownianP; //stored distribution data
public:
	std::vector<int> _cpI; //index of CP orders: -1 not a CP; 0 start and end(+1); 1+ CPs
	std::vector<int> _cpS; //all CP locations
	std::vector<double> _pValue; //p-values 1 not a CP; <1 for CPs

	Hic(std::string fileName, std::string fileNameP, int in_form, int cv, double sv, double hv = 0.0);
	void topDown();
	void topDown(int cpt0, int cpt1);
	void testCp(int cp, int store);
	void pruning();
	void bottomUp();
	void outPut();
	std::vector<std::vector<double>> subMatrix(int s, int e);
};

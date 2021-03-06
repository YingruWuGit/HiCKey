#include "HiCKey.h"

Hic::Hic(std::string fileName, std::string fileNameP, int in_form, int cv, double sv, double hv) : _fileName{ fileName }, _fileNameP{ fileNameP }, _in_form{ in_form }, _cv{ cv }, _sv{ sv }, _hv{ hv }, _countMatrix{}, _brownianP{}, _cpI{}, _cpS{}, _pValue{} {
	std::ifstream fin(_fileName);
	std::string newLine = "";
	double newElement = 0.0;
	//read input as list
	if (_in_form) {
		int r = 0; //how many rows does _countMatrix have
		while (std::getline(fin, newLine)) {
			std::istringstream sin1(newLine);
			int rn = 0;
			sin1 >> rn; //new row from data
			rn /= _in_form;
			while (rn >= r) {
				_countMatrix.emplace_back();
				++r;
			}
			int cn = 0;
			sin1 >> cn >> newElement;
			cn /= _in_form;
			if (cn >= rn) {
				_countMatrix[rn].emplace_back(cn, newElement);
			}
		}
	}
	//read input as matrix
	else {
		int r = -1; //row to write
		while (std::getline(fin, newLine)) {
			++r;
			std::istringstream sin0(newLine);
			_countMatrix.emplace_back();
			int c = 0;
			for (; c < r; ++c) {
				sin0 >> newElement; //drop this part of data
			}
			while (sin0 >> newElement) {
				if (newElement != 0.0) {
					_countMatrix[r].emplace_back(c, newElement);
				}
				++c;
			}
		}
	}
	fin.close();
	//initialize cpI and pValue, add a dummy element at the end
	for (int z = 0; z < _countMatrix.size() + 1; ++z) {
		_cpI.emplace_back(-1);
		_pValue.emplace_back(1);
	}

	//read BrownainP
	_brownianP.reserve(1000000);
	fin.open(_fileNameP, std::ifstream::in);
	std::getline(fin, newLine);
	std::istringstream sin2(newLine);
	while (sin2 >> newElement) {
		_brownianP.emplace_back(newElement);
	}
	_sv = _brownianP[static_cast<int>(_sv * _brownianP.size()) - 1]; //sv is compared to lambda, hv to p-value
	fin.close();
}

void Hic::topDown() {
	int cm = _countMatrix.size();
	std::deque<int> cpT{}; //cpT is a temporary CP vector(all starting points)
	for (int z = 0; z < cm; ++z) { //eliminate start zeros
		if (_countMatrix[z].size() != 0) {
			_cpI[z] = 0;
			cpT.emplace_back(z);
			break;
		}
	}
	for (int z = cm - 1; z != -1; --z) { //eliminate ending zeros
		if (_countMatrix[z].size() != 0) {
			_cpI[z + 1] = 0; //last start CP, maybe at dummy
			cpT.emplace_back(z + 1);
			break;
		}
	}
	while (cpT.size() > 1) {
		if (cpT[1] - cpT[0] < 2 * _cv) {
			cpT.pop_front();
			continue;
		}
		int lcs = cpT[0], lce = cpT[1];
		std::vector<double> rowSum(lce - lcs, 0.0);
		std::vector<double> colSum(lce - lcs, 0.0);
		for (int z = lcs; z < lce; ++z) {
			for (const std::pair<int, double>& p : _countMatrix[z]) {
				if (p.first >= lce) {
					break;
				}
				rowSum[z - lcs] += p.second;
				colSum[p.first - lcs] += p.second;
			}
		}
		std::pair<int, double> logLR(lcs, INFINITY);
		int sizA = (lce - lcs + 1) * (lce - lcs) / 2;
		double subA = std::accumulate(rowSum.begin(), rowSum.end(), 0.0);
		double subA1 = std::accumulate(colSum.begin(), std::next(colSum.begin(), _cv - 1), 0.0);
		double subA2 = std::accumulate(std::next(rowSum.begin(), _cv - 1), rowSum.end(), 0.0);
		double subA3 = subA - subA1 - subA2;
		if (subA2 == 0.0) {//most zeros in subA, put no change point
			cpT.pop_front();
			continue;
		}
		for (int x = _cv; x <= lce - lcs - _cv; x++) {//put a change point at location x(start of a block)
			int y = x - 1;
			subA1 += colSum[y];
			subA2 -= rowSum[y];
			subA3 += rowSum[y] - colSum[y];
			if ((subA1 == 0.0) && (rowSum[x] == 0.0)) {
				continue;
			}
			int sizA1 = (x + 1) * x / 2;
			int sizA2 = (lce - lcs - x + 1) * (lce - lcs - x) / 2;
			int sizA3 = sizA - sizA1 - sizA2;
			double l = subA * subA / sizA;
			double l1 = ((subA1 == 0.0) ? INFINITY : subA1 * subA1 / sizA1);
			double l2 = ((subA2 == 0.0) ? INFINITY : subA2 * subA2 / sizA2);
			double l3 = ((subA3 == 0.0) ? INFINITY : subA3 * subA3 / sizA3);
			double lambda = l - l1 - l2 - l3;

			if (lambda < logLR.second) {
				logLR.second = lambda;
				logLR.first = x + lcs;
			}
		}
		if (logLR.first == lcs) {
			cpT.pop_front();
			continue;
		}
		_cpI[logLR.first] = ((_cpI[lcs] >= _cpI[lce]) ? _cpI[lcs] : _cpI[lce]) + 1; //adjust cpI for new change point founded
		cpT.emplace_back(logLR.first);
		std::sort(cpT.begin(), cpT.end());
	}
	return;
}

void Hic::topDown(int cpt0, int cpt1) {
	std::deque<int> cpT = { cpt0, cpt1 }; //cpT is a temporary CP vector(all starting points)
	while (cpT.size() > 1) {
		int lcs = cpT[0], lce = cpT[1];
		std::vector<double> rowSum(lce - lcs, 0.0);
		std::vector<double> colSum(lce - lcs, 0.0);
		for (int z = lcs; z < lce; ++z) {
			for (const std::pair<int, double>& p : _countMatrix[z]) {
				if (p.first >= lce) {
					break;
				}
				rowSum[z - lcs] += p.second;
				colSum[p.first - lcs] += p.second;
			}
		}
		std::pair<int, double> logLR(lcs, INFINITY);
		int sizA = (lce - lcs + 1) * (lce - lcs) / 2;
		double subA = std::accumulate(rowSum.begin(), rowSum.end(), 0.0);
		double subA1 = 0.0;
		double subA2 = subA;
		double subA3 = 0.0;
		for (int x = 1; x < lce - lcs; ++x) {
			int y = x - 1;
			subA1 += colSum[y];
			subA2 -= rowSum[y];
			subA3 += rowSum[y] - colSum[y];
			if (_cpI[x + lcs] == -1) {
				continue;
			}
			int sizA1 = (x + 1) * x / 2;
			int sizA2 = (lce - lcs - x + 1) * (lce - lcs - x) / 2;
			int sizA3 = sizA - sizA1 - sizA2;
			double l = subA * subA / sizA;
			double l1 = ((subA1 == 0.0) ? INFINITY : subA1 * subA1 / sizA1);
			double l2 = ((subA2 == 0.0) ? INFINITY : subA2 * subA2 / sizA2);
			double l3 = ((subA3 == 0.0) ? INFINITY : subA3 * subA3 / sizA3);
			double lambda = l - l1 - l2 - l3;

			if (lambda < logLR.second) {
				logLR.second = lambda;
				logLR.first = x + lcs;
			}
		}
		if (logLR.first == lcs) {
			cpT.pop_front();
			continue;
		}
		_cpI[logLR.first] = ((_cpI[lcs] >= _cpI[lce]) ? _cpI[lcs] : _cpI[lce]) + 1; //adjust cpI for new change point founded
		cpT.emplace_back(logLR.first);
		std::sort(cpT.begin(), cpT.end());
	}
	return;
}

void Hic::testCp(int cp, int store) {
	int lcs = cp - 1, lce = cp + 1;
	while (_cpI[lcs] == -1) {
		--lcs;
	}
	while (_cpI[lce] == -1) {
		++lce;
	}
	double subA = 0.0;
	double subA1 = 0.0;
	double subA2 = 0.0;
	double subA3 = 0.0;
	double sigmaS = 0.0;
	for (int z = lcs; z < lce; ++z) {
		for (const std::pair<int, double>& p : _countMatrix[z]) {
			if (p.first >= lce) {
				break;
			}
			subA += p.second;
			sigmaS += p.second * p.second;
			if (z < cp && p.first < cp) {
				subA1 += p.second;
			}
			else if (z < cp && p.first >= cp) {
				subA3 += p.second;
			}
			else {
				subA2 += p.second;
			}
		}
	}
	int sizA = (lce - lcs + 1) * (lce - lcs) / 2;
	int sizA1 = (cp - lcs + 1) * (cp - lcs) / 2;
	int sizA2 = (lce - cp + 1) * (lce - cp) / 2;
	int sizA3 = sizA - sizA1 - sizA2;
	sigmaS = sigmaS / sizA - (subA / sizA) * (subA / sizA);
	double l = subA * subA / (sigmaS * sizA);
	double l1 = ((subA1 == 0.0) ? INFINITY : subA1 * subA1 / (sigmaS * sizA1));
	double l2 = ((subA2 == 0.0) ? INFINITY : subA2 * subA2 / (sigmaS * sizA2));
	double l3 = ((subA3 == 0.0) ? INFINITY : subA3 * subA3 / (sigmaS * sizA3));
	double lambda = l - l1 - l2 - l3;
	if (lambda > _sv) {
		_cpI[cp] = -1;
	}
	if (store && (_cpI[cp] > 0)) {
		_cpI[cp] = 1; //reset change point order
		_pValue[cp] = (std::upper_bound(_brownianP.begin(), _brownianP.end(), lambda) - _brownianP.begin()) / static_cast<double>(_brownianP.size()); //record p-values
		_cpS.emplace_back(cp);
	}
	return;
}

void Hic::pruning() {
	//first pruning
	std::map<int, std::vector<int>> cpsMap{};
	for (int z = 0; z < _cpI.size(); ++z) {
		if ((_cpI[z] > 0) && (cpsMap.find(_cpI[z]) == cpsMap.end())) {
			cpsMap[_cpI[z]] = { z };
		}
		else if (_cpI[z] > 0) {
			cpsMap[_cpI[z]].emplace_back(z);
		}
	}
	for (auto ritr = cpsMap.rbegin(); ritr != cpsMap.rend(); std::advance(ritr, 1)) {
		for (int cp : (*ritr).second) {
			testCp(cp, 0);
		}
	}
	//second pruning and record p-values
	std::map<int, std::vector<int>> cpsMap1{};
	for (int z = 0; z < _cpI.size(); ++z) {
		if ((_cpI[z] > 0) && (cpsMap1.find(_cpI[z]) == cpsMap1.end())) {
			cpsMap1[_cpI[z]] = { z };
		}
		else if (_cpI[z] > 0) {
			cpsMap1[_cpI[z]].emplace_back(z);
		}
	}
	for (auto ritr = cpsMap1.rbegin(); ritr != cpsMap1.rend(); std::advance(ritr, 1)) {
		for (int cp : (*ritr).second) {
			testCp(cp, 1);
		}
	}
	std::sort(_cpS.begin(), _cpS.end());
	return;
}

void Hic::bottomUp() {
	if (_hv == 0.0) {
		return;
	}
	int fst = 0, lst = _cpI.size() - 1;
	while (_cpI[fst] != 0) {
		++fst;
	}
	while (_cpI[lst] != 0) {
		--lst;
	}
	std::vector<int> idh = { fst };
	for (int z : _cpS) {
		if (_pValue[z] <= _hv) {
			if (idh.size() > 2) {
				topDown(idh[0], z);
			}
			idh.clear();
			idh.emplace_back(z);
		}
		else {
			_cpI[z] = 2;
			if (z < _cpS.back()) {
				idh.emplace_back(z);
			}
			else if (idh.size() > 1) {
				topDown(idh[0], lst);
			}
		}
	}
	return;
}

void Hic::outPut() {
	std::string fileName3(_fileName);
	std::string::iterator itr = std::prev(fileName3.end());
	while (*itr != '.') {
		std::advance(itr, -1);
	}
	fileName3.erase(itr, fileName3.end());
	fileName3 += "_output.txt";
	std::ofstream fout(fileName3);
	if (_in_form) {
		for (int c : _cpS) {
			fout << c * _in_form << '\t' << _cpI[c] << '\t' << _pValue[c] << '\n';
		}
	}
	else {
		for (int c : _cpS) {
			fout << c << '\t' << _cpI[c] << '\t' << _pValue[c] << '\n';
		}
	}
	fout.close();
	return;
}

//here s is the start point with 0 index; e is not included
std::vector<std::vector<double>> Hic::subMatrix(int s, int e) {
	s /= _in_form;
	e /= _in_form;
	double lEle = 0.0; //fill in lower triangular part
	std::vector<std::vector<double>> half(e - s, std::vector<double>(e - s, 0.0));
	for (int z = s; z < e; ++z) {
		for (const std::pair<int, double>& p : _countMatrix[z]) {
			if (p.first >= e) {
				break;
			}
			half[z - s][p.first - s] = p.second;
			lEle += ((p.first < 2 * _cv + z) ? p.second : 0.0);
		}
	}
	std::vector<int> cpi(_cpI.begin() + s, _cpI.begin() + e);
	int O = *std::max_element(cpi.begin(), cpi.end());
	lEle /= 2 * static_cast<double>(_cv)* (static_cast<double>(e) - static_cast<double>(s))* O;
	for (int o = 1; o <= O; ++o) {
		int lcs = 0;
		for (int i = 1; i < e - s; ++i) {
			if (cpi[i] != -1 && cpi[i] <= o) {
				lcs = i;
				continue;
			}
			for (int j = i - 1; j >= lcs; --j) {
				half[i][j] += lEle;
			}
		}
	}
	return half;
}

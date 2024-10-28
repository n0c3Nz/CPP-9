#include "PmergeMe.hpp"

Pmergeme::Pmergeme(){ }

Pmergeme::Pmergeme(std::string nbrs){
	if (nbrs.find_first_not_of("0123456789 ") != std::string::npos){
		std::cout << "Invalid input, please provide a string with only digits and spaces." << std::endl;
		return;
	}
	std::vector<int> v;
	std::string::size_type sz;
	while (nbrs.size() > 0){
		v.push_back(std::stoi(nbrs, &sz));
		nbrs = nbrs.substr(sz);
	}
	_nbrs = v;
}

Pmergeme::Pmergeme(const Pmergeme &copy) {
	_nbrs = copy._nbrs;
}

Pmergeme &Pmergeme::operator=(const Pmergeme &copy) {
	_nbrs = copy._nbrs;
	return *this;
}

Pmergeme::~Pmergeme() { }

void Pmergeme::fordJohnsonSort(std::vector<int>& arr, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		if (!_r) {
			_ls = m;
			_rs = r - m + 1;
			_r = true;
		}

		fordJohnsonSort(arr, l, m);
		_lend = std::clock();
		_lelapsed = double(_lend - _lstart) / CLOCKS_PER_SEC;
		
		fordJohnsonSort(arr, m + 1, r);
		_rend = std::clock();
		_relapsed = double(_rend - _rstart) / CLOCKS_PER_SEC;

		std::list<int> left(arr.begin() + l, arr.begin() + m + 1);
		std::vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
		mergeListVector(left, right, arr, l);
	}
}

void Pmergeme::mergeListVector(std::list<int>& left, std::vector<int>& right, std::vector<int>& arr, int l) {
	std::list<int>::iterator itLeft = left.begin();
	int itRight = 0;
	int k = l;

	while (itLeft != left.end() && itRight < right.size()) {
		if (*itLeft <= right[itRight]) {
			arr[k] = *itLeft;
			++itLeft;
		} else {
			arr[k] = right[itRight];
			++itRight;
		}
		++k;
	}

	while (itLeft != left.end()) {
		arr[k] = *itLeft;
		++itLeft;
		++k;
	}

	while (itRight < right.size()) {
		arr[k] = right[itRight];
		++itRight;
		++k;
	}
}

void Pmergeme::sort() {
	_r = false;
	if (_nbrs.empty()) {
		std::cout << "Empty vector, please provide one." << std::endl;
		return;
	}
	std::cout << "Before: ";
	for (int i = 0; i < _nbrs.size(); i++)
		std::cout << _nbrs[i] << " ";
	std::cout << std::endl;

	_rstart = std::clock();
	_lstart = std::clock();

	fordJohnsonSort(_nbrs, 0, _nbrs.size() - 1);

	std::cout << "After:  ";
	for (int i = 0; i < _nbrs.size(); i++)
		std::cout << _nbrs[i] << " ";
	std::cout << std::endl;

	std::cout << "Time to process left range of " << _ls << " elements with fordJohnsonSort: " << _lelapsed * 1e6 << " us" << std::endl;
	std::cout << "Time to process right range of " << _rs << " elements with fordJohnsonSort: " << _relapsed * 1e6 << " us" << std::endl;
}

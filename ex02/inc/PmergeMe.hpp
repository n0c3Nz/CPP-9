#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>


class Pmergeme {
	private:
		std::vector<int> _nbrs;
		std::list<int> _left;
		std::vector<int> _right;
		std::chrono::high_resolution_clock::time_point _rstart;
		std::chrono::high_resolution_clock::time_point _rend;
		std::chrono::duration<double> _relapsed;
		std::chrono::high_resolution_clock::time_point _lstart;
		std::chrono::high_resolution_clock::time_point _lend;
		std::chrono::duration<double> _lelapsed;
		int _ls;
		int _rs;
		bool _r;

		void mergeListVector(std::list<int>& left, std::vector<int>& right, std::vector<int>& arr, int l);
		void fordJohnsonSort(std::vector<int>& arr, int l, int r);
	public:
		Pmergeme();
		Pmergeme(std::string nbrs);//parametros
		Pmergeme(const Pmergeme &copy);
		Pmergeme &operator=(const Pmergeme &copy);
		~Pmergeme();
		void sort();
};



#endif
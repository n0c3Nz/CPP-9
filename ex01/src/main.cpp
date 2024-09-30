#ifndef RPN_HPP
#define RPN_HPP

#include <vector>
#include <iostream>
#include <algorithm>


class Rpn {
	private:
		std::vector<int> _operand;
		std::vector<char> _operator;
	public:
		Rpn(void);//Default Constructor
		Rpn(std::vector<int> _operand, std::vector<char>operator);//Parameter Constructor
		Rpn

};


#endif
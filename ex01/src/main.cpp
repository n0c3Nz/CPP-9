#include "RPN.hpp"


int main(int argc, char **argv){
	if (argc != 2)
	{
		std::cerr << "Invalid number of arguments" << std::endl;
		return 1;
	}

	Rpn::calculate(argv[1]);
	return 0;
}
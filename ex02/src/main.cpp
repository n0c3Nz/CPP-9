#include "PmergeMe.hpp"


int main(int argc, char **argv)
{
	if (argc > 2)
	{
		//take all args and do a string with them
		std::string nbrs;
		for (int i = 1; i < argc; i++)
		{
			nbrs += argv[i];
			if (i < argc - 1)
				nbrs += " ";
		}
		Pmergeme p(nbrs);
		p.sort();
	}
	else if (argc == 2){
		std::string nbrs = argv[1];
		Pmergeme p(nbrs);
		p.sort();
	}
	else {
		std::cout << "Usage: " << argv[0] << " \"10 6 29 2 42\"" << std::endl;
	}

	return 0;
}
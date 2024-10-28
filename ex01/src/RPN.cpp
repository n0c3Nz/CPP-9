#include "RPN.hpp"


Rpn::Rpn(void) {
	std::cout << "Default Constructor" << std::endl;
}

Rpn::Rpn(char *operation) {
	std::cout << "Parametric Constructor" << std::endl;
}

Rpn::Rpn(const Rpn &copy) {
	std::cout << "Copy Constructor" << std::endl;
	*this = copy;
}

Rpn &Rpn::operator=(const Rpn &copy) {
	std::cout << "Assignation Operator" << std::endl;
	return *this;
}

Rpn::~Rpn() {
	std::cout << "Destructor" << std::endl;
}

int strlen(char *operation){
	int i = 0;
	while (operation[i] != '\0'){
		i++;
	}
	return i;
}

int Rpn::isAOperation(char *operation){
	bool space = true;
	int numbers = 0;
	for (int i = 0; i < strlen(operation); ++i)
	{
		if (std::isalpha(operation[i])){
			throw InvalidArgument();
			return 1;
		}
		else if (std::isspace(operation[i])){
			space = true;
		}
		if (isdigit(operation[i]) && space == true){
			numbers++;
			space = false;
		}
		
	}
	if (numbers < 2 || numbers > 10){
		throw InvalidArgument();
		return 1;
	}
	return 0;
}

const char	*Rpn::InvalidArgument::what() const throw()
{
	return ("Invalid Arguments");
}

const char	*Rpn::InvalidOperation::what() const throw()
{
	return ("Invalid Operation");
}


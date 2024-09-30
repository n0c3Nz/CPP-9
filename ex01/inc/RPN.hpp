#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <algorithm>
#include <string>


class Rpn {
	private:
		Rpn(void);//Default Constructor
		Rpn(char *operation);//Parametric Constructor
		Rpn(const Rpn &copy);
		Rpn &operator=(const Rpn &copy);
		static int isAOperation(char *operation);
	public:
		class InvalidArgument : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		~Rpn();
		static int calculate(char *operation){
			try {
				isAOperation(operation);
				std::string str(operation);
				std::string::iterator it = str.begin();
				std::string::iterator ite = str.end();
				std::stack<int> stack;
				
				while(it != ite){
					if (std::isdigit(*it)){
						std::string number;
						// Leer el número completo
						while (it != ite && std::isdigit(*it)){
							number += *it;
							++it;
						}
						stack.push(std::stoi(number));
						continue; // Para evitar incrementar 'it' dos veces.
					}
					else if (*it == '+'){
						if (stack.size() < 2)
							throw InvalidArgument();
						int a = stack.top();
						stack.pop();
						int b = stack.top();
						stack.pop();
						stack.push(a + b);
					}
					else if (*it == '-'){
						if (stack.size() < 2)
							throw InvalidArgument();
						int a = stack.top();
						stack.pop();
						int b = stack.top();
						stack.pop();
						stack.push(b - a);
					}
					else if (*it == '*'){
						if (stack.size() < 2)
							throw InvalidArgument();
						int a = stack.top();
						stack.pop();
						int b = stack.top();
						stack.pop();
						stack.push(a * b);
					}
					else if (*it == '/'){
						if (stack.size() < 2)
							throw InvalidArgument();
						int a = stack.top();
						stack.pop();
						int b = stack.top();
						stack.pop();
						stack.push(b / a);
					}
					else if (*it != ' '){
						throw InvalidArgument();
					}
					++it;
				}
				if (stack.size() != 1)
					throw InvalidArgument();
				std::cout << stack.top() << std::endl;
				return stack.top();
			}
			catch (std::exception &e){
				std::cerr << e.what() << std::endl;
				return -1;
			}
		}

		

};

/*
12 * 3 - 5 * ( 5 + 7) = -24
12 3 * 5 5 7 + * -

(42 * 2) / 4 - 2 + 3 = 19
42 * 2 = 84 / 4 = 21 | 3 + 2 = 5 | 21 - 5 = 16
*/

#endif
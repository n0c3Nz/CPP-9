#include "PmergeMe.hpp"


Pmergeme::Pmergeme(){
	//std::cout << "Default constructor called" << std::endl;
}

Pmergeme::Pmergeme(std::string nbrs){
	//std::cout << "Parametric constructor called" << std::endl;
	//Chequear si todos los caracteres son digitos o espacios
	if (nbrs.find_first_not_of("0123456789 ") != std::string::npos){
		std::cout << "Invalid input, please provide a string with only digits and spaces." << std::endl;
		return;
	}
	// Convert string to vector of positive integers
	std::vector<int> v;
	std::string::size_type sz;
	while (nbrs.size() > 0){
		v.push_back(std::stoi(nbrs, &sz));
		nbrs = nbrs.substr(sz);
	}
	_nbrs = v;
}

Pmergeme::Pmergeme(const Pmergeme &copy){
	//std::cout << "Copy constructor called" << std::endl;
	_nbrs = copy._nbrs;
}

Pmergeme &Pmergeme::operator=(const Pmergeme &copy){
	//std::cout << "Assignation operator called" << std::endl;
	_nbrs = copy._nbrs;
	return *this;
}

Pmergeme::~Pmergeme(){
	//std::cout << "Destructor called" << std::endl;
}

// Asumiendo que ya tienes el resto de tu clase definida
void Pmergeme::fordJohnsonSort(std::vector<int>& arr, int l, int r)
{
	if (l < r) {
        int m = l + (r - l) / 2;  // Calculamos el punto medio
		if (!_r)
		{
			_ls = m;
			_rs = r - m + 1;
			_r = true;
		}

        // Llamamos recursivamente a fordJohnsonSort en ambas mitades
        fordJohnsonSort(arr, l, m);    // Ordenamos la mitad izquierda
		_lend = std::chrono::high_resolution_clock::now();
   		// Separar los '>>' en C++98
    	_lelapsed = std::chrono::duration_cast<std::chrono::duration<double> >(_lend - _lstart);
		fordJohnsonSort(arr, m + 1, r);  // Ordenamos la mitad derecha
		_rend = std::chrono::high_resolution_clock::now();
   		// Separar los '>>' en C++98
		_relapsed = std::chrono::duration_cast<std::chrono::duration<double> >(_rend - _rstart);
        // Dividimos la mitad izquierda en una std::list y la mitad derecha en std::vector
        std::list<int> left(arr.begin() + l, arr.begin() + m + 1);  // Izquierda como lista
        std::vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);  // Derecha como vector

        // Fusionamos las dos mitades usando lista para la izquierda y vector para la derecha
        mergeListVector(left, right, arr, l);
        // Imprimir el vector después de cada fusión
        /*std::cout << "Array after merge: ";
        for (int i = 0; i < arr.size(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;*/
    }
}

void Pmergeme::mergeListVector(std::list<int>& left, std::vector<int>& right, std::vector<int>& arr, int l)
{
    std::list<int>::iterator itLeft = left.begin();  // Iterador para la lista (mitad izquierda)
    int itRight = 0;                                  // Índice para el vector (mitad derecha)
    int k = l;                                        // Índice para el arreglo original

    // Combinamos ambas mitades (lista y vector) en el arreglo original
    while (itLeft != left.end() && itRight < right.size()) {
        if (*itLeft <= right[itRight]) {
            arr[k] = *itLeft;  // Copiamos desde la lista si el elemento es menor o igual
            ++itLeft;          // Avanzamos en la lista
        } else {
            arr[k] = right[itRight];  // Copiamos desde el vector si el elemento es menor
            ++itRight;                // Avanzamos en el vector
        }
        ++k;  // Avanzamos en el arreglo original
    }

    // Copiamos los elementos restantes de la lista (si los hay)
    while (itLeft != left.end()) {
        arr[k] = *itLeft;
        ++itLeft;
        ++k;
    }

    // Copiamos los elementos restantes del vector (si los hay)
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
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;

    // Declaramos el tipo explícitamente para medir el tiempo
    _rstart = std::chrono::high_resolution_clock::now();
    _lstart = std::chrono::high_resolution_clock::now();

    fordJohnsonSort(_nbrs, 0, _nbrs.size() - 1);

    std::cout << "After:  ";
    for (int i = 0; i < _nbrs.size(); i++)
        std::cout << _nbrs[i] << " ";
    std::cout << std::endl;
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;

    // Mostrar el tiempo en microsegundos
	std::cout << "Time to process left range of " << _ls << " elements with fordJohnsonSort: " << _lelapsed.count() * 1e6 << " us" << std::endl;
	std::cout << "Time to process right range of " << _rs << " elements with fordJohnsonSort: " << _relapsed.count() * 1e6 << " us" << std::endl;
}
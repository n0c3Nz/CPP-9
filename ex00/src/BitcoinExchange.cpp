#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

BitcoinExchange::BitcoinExchange(void) {
	getDB();
}

BitcoinExchange::BitcoinExchange(std::string filename) {
	getDB();
	getUserPrices(filename);
}


BitcoinExchange::~BitcoinExchange(void) {
}


void BitcoinExchange::getDB(void){
    std::ifstream file("db/data.csv");
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file ../db/data.csv");
    }
    std::string line;

    // Ignorar la primera línea si contiene encabezados
    std::getline(file, line);

    while (std::getline(file, line)) {
        // Asegurarse de que la línea tiene al menos una coma
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            continue; // Saltar líneas sin coma
        }

        std::string date = line.substr(0, commaPos);
        std::string price = line.substr(commaPos + 1);

        // Verificar si el valor de precio es válido antes de intentar convertirlo
        try {
            PriceData data;
            data._date = date;

            // Asegurarse de que la cadena price no esté vacía y tenga formato adecuado
            if (!price.empty()) {
                data._price = std::stof(price);
            } else {
                std::cerr << "Invalid price format at line: " << line << std::endl;
				std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
                continue;
            }

            _btc.push_back(data);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid argument in stof at line: " << line << std::endl;
			std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
            continue;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Value out of range in stof at line: " << line << std::endl;
			std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
            continue;
        }
    }
}

void BitcoinExchange::getUserPrices(std::string filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file " + filename);
	}
	std::string line;
	// Ignorar la primera línea si contiene encabezados
    std::getline(file, line);
	while (std::getline(file, line)) {
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos) {
			continue;
		}
		std::string date = line.substr(0, pipePos - 1);
		// Check if the date has the correct format (YYYY-MM-DD)
		if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
			std::cerr << "Invalid date format at line: " << line << std::endl;
			std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
			continue;
		}
		// Check if the date is valid
		if (std::stoi(date.substr(5, 2)) > 12 || std::stoi(date.substr(8, 2)) > 31) {
			std::cerr << "Invalid date at line: " << line << std::endl;
			std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
			continue;
		}
		std::string price = line.substr(pipePos + 2);
		try {
			PriceData data;
			data._date = date;
			if (!price.empty()) {
				// Check if the price is a valid positive int or float
				bool isValidPrice = true;
				for (size_t i = 0; i < price.length(); ++i) {
					char c = price[i];
					if (!isdigit(c) && c != '.' && c != '-') {
						isValidPrice = false;
						break;
					}
				}
				if (!isValidPrice || std::stof(price) < 0 || std::stof(price) > 1000) {
					std::cerr << "Invalid price value at line: " << line << " (price: " << price << ")" << std::endl;
					std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
					continue;
				}

				data._price = std::stof(price);
			} else {
				std::cerr << "Invalid price format at line: " << line << std::endl;
				std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
				continue;
			}
			_userPrices.push_back(data);
		} catch (const std::invalid_argument& e) {
			std::cerr << "Error: Invalid argument in stof at line: " << line << std::endl;
			std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
			continue;
		} catch (const std::out_of_range& e) {
			std::cerr << "Error: Value out of range in stof at line: " << line << std::endl;
			std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
			continue;
		}
	}
}

bool comparePriceData(const PriceData& data, const std::string& date) {
    return data._date < date;
}

void BitcoinExchange::userPurchases(void) {
    for (int i = 0; i < _userPrices.size(); ++i) {
        // Obtener el iterador al precio de btc en la fecha más cercana desde abajo a la fecha de compra
        std::vector<PriceData>::iterator it = std::lower_bound(_btc.begin(), _btc.end(), _userPrices[i]._date, comparePriceData);

        // Si no se encuentra la fecha porque es demasiado actual, se toma el precio más actual
        if (it == _btc.end()) {
            it = _btc.end() - 1;
        }
        else {
            --it;  // Esto es para coger el precio de la fecha más cercana desde abajo
        }

        // Calcular el valor de la compra en la fecha correspondiente
        double result = it->_price * _userPrices[i]._price;

        // Imprimir la fecha
        std::cout << _userPrices[i]._date << " => ";

        // Comprobar si el precio del usuario es un número entero
        if (_userPrices[i]._price == static_cast<int>(_userPrices[i]._price)) {
            // Si es entero, imprimirlo como tal
            std::cout << static_cast<int>(_userPrices[i]._price);
        } else {
            // Si tiene decimales, imprimirlo con precisión fija
            std::cout << std::fixed << std::setprecision(2) << _userPrices[i]._price;
        }

        std::cout << " = ";

        // Comprobar si el resultado es efectivamente un número entero
        if (result == static_cast<int>(result)) {
            // Si es entero, imprimirlo como tal
            std::cout << static_cast<int>(result) << std::endl;
        } else {
            // Si tiene decimales, imprimirlo con precisión fija
            std::cout << std::fixed << std::setprecision(2) << result << std::endl;
        }
    }
}

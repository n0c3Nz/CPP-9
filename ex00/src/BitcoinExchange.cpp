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

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) {
    *this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy) {
    if (this != &copy) {
        _btc = copy._btc;
        _userPurchases = copy._userPurchases;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange(void) {
    _btc.clear();
    _userPurchases.clear();
    std::cout << "Destructor called" << std::endl;
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
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            continue; // Saltar líneas sin coma
        }

        std::string date = line.substr(0, commaPos);
        std::string price = line.substr(commaPos + 1);

        try {
            if (!price.empty()) {
                _btc[date] = std::stof(price); // Usamos std::map aquí
            } else {
                std::cerr << "Invalid price format at line: " << line << std::endl;
				std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
                continue;
            }
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
            std::cerr << "Invalid separator format at line: " << line << std::endl;
			std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
			continue;
		}
		std::string date = line.substr(0, pipePos - 1);
		std::string price = line.substr(pipePos + 2);
		try {
			if (!price.empty()) {
				bool isValidPrice = true;
				for (size_t i = 0; i < price.length(); ++i) {
					char c = price[i];
					if (!isdigit(c) && c != '.' && c != '-') {
						isValidPrice = false;
						break;
					}
				}
				if (!isValidPrice || std::stof(price) < 0 || std::stof(price) > 1000) {
					std::cerr << "Invalid price value at line: " << line << std::endl;
					std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
					continue;
				}

				_userPurchases[date] = std::stof(price); // Usamos std::map aquí
			} else {
				std::cerr << "Invalid price format at line: " << line << std::endl;
				std::cerr << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
				continue;
			}
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

void BitcoinExchange::userPurchases(void) {
    std::map<std::string, float>::iterator it;
    std::map<std::string, float>::iterator purchase_it;

    for (purchase_it = _userPurchases.begin(); purchase_it != _userPurchases.end(); ++purchase_it) {
        it = _btc.lower_bound(purchase_it->first);
        
        if (it == _btc.end()) {
            it = --_btc.end();
        } else if (it != _btc.begin()) {
            --it; // Para tomar la fecha más cercana desde abajo
        }

        double result = it->second * purchase_it->second;

        // Imprimir la fecha
        std::cout << purchase_it->first << " => ";

        // Comprobar si el precio del usuario es un número entero
        if (purchase_it->second == static_cast<int>(purchase_it->second)) {
            std::cout << static_cast<int>(purchase_it->second);
        } else {
            std::cout << std::fixed << std::setprecision(2) << purchase_it->second;
        }

        std::cout << " = ";

        // Comprobar si el resultado es un número entero
        if (result == static_cast<int>(result)) {
            std::cout << static_cast<int>(result) << std::endl;
        } else {
            std::cout << std::fixed << std::setprecision(2) << result << std::endl;
        }
    }
}

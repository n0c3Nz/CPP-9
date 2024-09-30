#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

class BitcoinExchange {
	private:
		std::map<std::string, float> _btc;
		std::map<std::string, float> _userPurchases;
		void getDB(void);
		void getUserPrices(std::string filename);
	public:
		BitcoinExchange(void);
		BitcoinExchange(std::string filename);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);
		~BitcoinExchange(void);
		void userPurchases(void);
};

#endif

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

struct PriceData {
    float _price;
    std::string _date;
};

class BitcoinExchange {
	private:
		std::vector<PriceData> _btc;
		std::vector<PriceData> _userPrices;
		void getDB(void);
		void getUserPrices(std::string filename);
	public:
		BitcoinExchange(void);
		BitcoinExchange(std::string filename);
		~BitcoinExchange(void);
		void userPurchases(void);


};

#endif
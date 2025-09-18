#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <cstdlib>

class BitcoinExchange
{
    public: 
        BitcoinExchange();
        BitcoinExchange& operator=(const BitcoinExchange& other);
        BitcoinExchange(const BitcoinExchange& copy);
        ~BitcoinExchange();
        void giveBitcoin (char *input);
        void getData(std::map <std::string,float> &_map);
    private:
        std::map <std::string, float> _map;
};

#endif
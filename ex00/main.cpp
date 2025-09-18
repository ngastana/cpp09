#include "BitcoinExchange.hpp"


int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 0;
    }
    
    class BitcoinExchange bitcoin;
    bitcoin.giveBitcoin(argv[1]);
    return 0;
}
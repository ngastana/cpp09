#include "BitcoinExchange.hpp"

bool leapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validateDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (size_t i = 0; i < date.size(); i++) {
        if (i == 4 || i == 7) 
            continue;
        if (!std::isdigit(date[i])) 
            return false;
    }

    int year = atoi(date.substr(0, 4).c_str());
    int month  = atoi(date.substr(5, 2).c_str());
    int day  = atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12) return false;

    int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && leapYear(year)) {
        daysPerMonth[1] = 29;
    }

    if (day < 1 || day > daysPerMonth[month - 1]) return false;

    return true;
}

bool validateValue(const float value){
    if (value <= 0 || value >= 1000)
        return false;
    return true;
}

void getData(std::map <std::string,float>* _db)
{
    std::ifstream  data("data.csv");
    if (!data.is_open()){
        std::cout << "I can not open the file." << std::endl;
        return;
    }
    std::string line;

    std::getline(data, line);
    while (getline(data, line)){
        std::string date = line.substr(0, line.find(','));
        std::string amount = line.substr(line.find(',')+1, line.length());
        _db->operator[](date) = atof(amount.c_str());
    }
    data.close();
}

bool toFloat(const std::string &s, float &result) {
    std::istringstream iss(s);
    iss >> result;
    return !iss.fail() && iss.eof();
}

float obtainValue(std::string date, std::map <std::string,float> _db)
{
    if (_db.empty()){
        return -1;
    }
    std::map<std::string, float>::const_iterator it = _db.lower_bound(date);//upper no me da justo la fecha

    if (it != _db.end() && it->first == date){
        return it->second;
    }
    else if (it == _db.begin())
        return -1;
    else {
        --it;
        return it->second;
    }
}

void BitcoinExchange(char *input)
{
    std::ifstream file(input);
    if (!file.is_open()){
        std::cout << "I can not open the file." << std::endl;
        return;
    }
    std::map <std::string,float> _idb;
    std::map <std::string,float> _db;
    getData(&_db);
    std::string line;
    if (!getline(file, line) || line.compare("date | value"))
    {
        std::cerr << "Example file: date | value"<< std::endl;
        //throw std::runtime_error("File structure badly done.");
        return;
    }
    while (getline(file, line)){
//      std::cout << "ESTO ES EL TEXTO " << line << std::endl;
        size_t pos = line.find('|');
        if (pos != std::string::npos){
            std::string date = line.substr(0, pos);
            std::string value = line.substr(pos+1);
            while (!date.empty() && date[date.size() -1] == ' ')
                date.erase(date.size()-1);
            if (!validateDate(date)){
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }
            while (!value.empty() && value[0] == ' ') 
                value.erase(0,1);
            float value_float;
            if (!toFloat(value, value_float)) {
                std::cerr << "Error: invalid number: " << value <<  std::endl;
                continue;
            }                
            if (!validateValue(value_float)){
                if (value_float < 0)
                    std::cerr << "Error: not a positive number." << std::endl;
                if (value_float > 1000)
                    std::cerr << "Error: too large a number." << std::endl;
                continue;
            }
            _idb[date] = value_float;
            float   bitcoinValue = obtainValue(date,_db);
            if (bitcoinValue == -1){
                std::cerr << "Error: not bitcoin value in date " << date << std::endl;
                continue;
            }
            std::cout << date << " => " << _idb[date] << " = " << bitcoinValue * _idb[date] << std::endl;
        }
        else {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
    file.close();
    return;
}

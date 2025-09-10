#include "BitcoinExchange.hpp"

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
    getline(file, line);
    while (getline(file, line)){
        size_t pos = line.find('|');
        if (pos != std::string::npos){
            std::string date = line.substr(0, pos);
            std::string value = line.substr(pos+1);
            while (!date.empty() && date[date.size() -1] == ' ') date.erase(date.size()-1);
            while (!value.empty() && value[0] == ' ') value.erase(0,1);
            float value_float = static_cast<float>(atof(value.c_str())); //c_str convierte de string a char*, atof convierte este ultimo a un double
            _idb[date] = value_float;
        }
        else {
            std::cerr << "Line badly formed" << std::endl;
        }
    }
    file.close();
    int i = 0;
    for (std::map<std::string,float>::iterator it = _idb.begin(); it != _idb.end(); ++it)
    {
        for (std::map<std::string,float>::iterator dit = _db.begin(); dit != _db.end(); ++dit)
        {
            if (it->first == )
            it->first << "=>" << it->second << std::endl;
        }
    }
    for (std::map<std::string,float>::iterator it = _idb.begin(); it != _idb.end(); ++it)
    {
        std::cout << it->first << "=>" << it->second << std::endl;
    }
    return;
}

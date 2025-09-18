#ifndef RPN_HPP
#define RPN_HPP
#include <stack>
#include <iostream>

class RPN
{
    public: 
        RPN();
        RPN& operator=(const RPN& other);
        RPN(const RPN& copy);
        ~RPN();
        int doMath (const std::string& input);
    private:
        std::stack <int> _st;
};

#endif
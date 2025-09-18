#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) : _st(other._st) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _st = other._st;
    }
    return *this;
}

RPN::~RPN() {}

int RPN::doMath (const std::string& input){
    for (size_t i = 0; i < input.size(); i++) {
        char c = input[i];
        if (std::isspace(c))
            continue;
        if (std::isdigit(c))
        {
            _st.push(c - '0'); 
        }
        else {
            if (_st.size() < 2) {
                std::cerr << "Error: not enough operands.\n";
                return -1;
            }
            int b = _st.top();
            _st.pop();
            int a = _st.top();
            _st.pop();
            int result = 0;
            switch (c)
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b == 0) {
                        std::cerr << "Error: division by zero.\n";
                        return -1;
                    }
                    result = a / b;
                    break; 
                default:
                    std::cerr << "Error: unknown operator " << c << "\n";
                    return -1;
            }
            _st.push(result);
        }
    }
    if (_st.size() != 1)
    {
        std::cerr << "Error: invalid RPN expression.\n";
        return -1;
    }
    return _st.top();
}

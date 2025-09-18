#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2){
        std::cout << "Input badly written: write the Reverse Polish Notation in one sentence.\n";
        return 0;
    }
    std::string myequation = argv[1];
    class RPN rpn;
    int value = rpn.doMath(myequation);
    if (value >= 0)
        std::cout << "Result: " << value << std::endl;
    return 1;
}

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv) {
    for (int i= 1; i < argc; i++)
    {
        int num = std::stoi(argv[i]);
        if (num < 0) {
            std::cerr << "Error: negative numbers not allowed.\n";
            return;
        }
        _vector.push_back(num);
        _deque.push_back(num);
    }
}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void FordJohnsonAlgorithm (int argc, const std::string &input)
{
    PmergeMe sorter(argc, input);
    std::cout << "Vector leído: ";
    for (size_t i = 0; i < _vector.size(); ++i) {
        std::cout << _vector[i] << " ";
    }
    std::cout << "\n";
}
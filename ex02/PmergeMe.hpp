#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iterator>

class PmergeMe {
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
    
    public:
        PmergeMe(int argc, char **argv);
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();
        
        const std::vector<int>& getVector() const { return _vector; }
        const std::deque<int>& getDeque() const { return _deque; }
        void sort(int argc, char** input);
};

#endif
#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>
#include <array>
#include <iostream>
#include <sstream>
#include <algorithm>


class PmergeMe {
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
    
    public:
        PmergeMe(int argc, char **argv);
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();
        
        void process(int argc, char* argv[]);
};

#endif
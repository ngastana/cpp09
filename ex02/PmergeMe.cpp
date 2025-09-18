#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv) {
    for (int i= 1; i < argc; i++)
    {
        int num = std::atoi(argv[i]);
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

std::vector<int> jacobsthalUpToVector(int n) {
    std::vector<int> J;
    J.push_back(0);
    J.push_back(1);
    while (true) {
        int next = J[J.size() - 1] + 2 * J[J.size() - 2];
        if (next >= n) break;
        J.push_back(next);
    }
    return J;
}

std::deque<int> jacobsthalUpToDeque(int n) {
    std::deque<int> J;
    J.push_back(0);
    J.push_back(1);
    while (true) {
        int next = J[J.size() - 1] + 2 * J[J.size() - 2];
        if (next >= n) break;
        J.push_back(next);
    }
    return J;
}

std::vector<int> fordJohnsonVector(std::vector<int> _vector)
{
    if (_vector.size() <= 2)
    {
        if(_vector.size() == 2 && (_vector[0] > _vector[1]))
            std::swap(_vector[0], _vector[1]);
        return _vector;
    }
    std::vector<int> winners;
    std::vector<int> losers;
    for (size_t i = 0; i + 1 < _vector.size(); i += 2){
        if (_vector[i] > _vector[i+1]){
            winners.push_back(_vector[i]);
            losers.push_back(_vector[i+1]);
        }
        else{
            winners.push_back(_vector[i+1]);
            losers.push_back(_vector[i]);
        }
    }
    int leftover = 0;
    bool hasLeftover = false;
    if (_vector.size() % 2) {
        //leftover = _vector[_vector.size() - 1];
        leftover = _vector.back();
        hasLeftover = true;
    }
    std::vector<int> sortedWinners = fordJohnsonVector(winners);
    std::vector<int> J = jacobsthalUpToVector(losers.size());
    for (size_t k = 0; k < J.size(); ++k) {
        size_t idx = J[k];
        if (idx < losers.size()) {
            std::vector<int>::iterator pos = std::lower_bound(sortedWinners.begin(), sortedWinners.end(), losers[idx]);
            sortedWinners.insert(pos, losers[idx]);
        }
    }
    for (size_t i = 0; i < losers.size(); ++i) {
        bool inJacob = false;
        for (size_t j = 0; j < J.size(); ++j) {
            if (J[j] == (int)i) {
                inJacob = true;
                break;
            }
        }
        if (!inJacob) {
            std::vector<int>::iterator pos = std::lower_bound(sortedWinners.begin(), sortedWinners.end(), losers[i]);
            sortedWinners.insert(pos, losers[i]);
        }
    }
    // for (size_t i = 0; i < losers.size(); ++i){
    //     std::vector<int>::iterator pos = std::lower_bound(sortedWinners.begin(), sortedWinners.end(), losers[i]);
    //     sortedWinners.insert(pos, losers[i]);
    // }
    if (hasLeftover){
        std::vector<int>::iterator pos = std::lower_bound(sortedWinners.begin(), sortedWinners.end(), leftover);
        sortedWinners.insert(pos, leftover);
    }
    return sortedWinners;
}

std::deque<int> fordJohnsonDeque(std::deque<int> _deque)
{
    if (_deque.size() <= 2)
    {
        if(_deque.size() == 2 && (_deque[0] > _deque[1]))
            std::swap(_deque[0], _deque[1]);
        return _deque;
    }
    std::deque<int> winners;
    std::deque<int> losers;
    for (size_t i = 0; i + 1 < _deque.size(); i += 2){
        if (_deque[i] > _deque[i+1]){
            winners.push_back(_deque[i]);
            losers.push_back(_deque[i+1]);
        }
        else{
            winners.push_back(_deque[i+1]);
            losers.push_back(_deque[i]);
        }
    }
    int leftover = 0;
    bool hasLeftover = false;
    if (_deque.size() % 2) {
        leftover = _deque[_deque.size() - 1];
        hasLeftover = true;
    }
    std::deque<int> sortedWinners = fordJohnsonDeque(winners);
    std::deque<int> J = jacobsthalUpToDeque(losers.size());
    for (size_t k = 0; k < J.size(); ++k) {
        size_t idx = J[k];
        if (idx < losers.size()) {
            std::deque<int>::iterator pos = std::lower_bound(sortedWinners.begin(), sortedWinners.end(), losers[idx]);
            sortedWinners.insert(pos, losers[idx]);
        }
    }
    for (size_t i = 0; i < losers.size(); ++i) {
        bool inJacob = false;
        for (size_t j = 0; j < J.size(); ++j) {
            if (J[j] == (int)i) {
                inJacob = true;
                break;
            }
        }
        if (!inJacob) {
            std::deque<int>::iterator pos = std::lower_bound(sortedWinners.begin(), sortedWinners.end(), losers[i]);
            sortedWinners.insert(pos, losers[i]);
        }
    }
    // for (size_t i = 0; i < losers.size(); ++i){
    //     std::deque<int>::iterator pos = std::lower_bound(sortedWinners.begin(), sortedWinners.end(), losers[i]);
    //     sortedWinners.insert(pos, losers[i]);
    // }
    if (hasLeftover){
        std::deque<int>::iterator pos = std::lower_bound(sortedWinners.begin(), sortedWinners.end(), leftover);
        sortedWinners.insert(pos, leftover);
    }
    return sortedWinners;
}

void PmergeMe::sort (int argc, char **input)
{
    for (int i= 1; i < argc; i++){
        int num = std::atoi(input[i]);
        if (num < 0) {
            std::cerr << "Error\n";
            return;
        }
    }  
    PmergeMe sorter(argc, input);
    try {
        std::cout << "Before: ";
        for (size_t i = 0; i < sorter.getVector().size(); ++i) {
            std::cout << sorter.getVector()[i] << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
        return;
    }
    std::vector<int> after = sorter.getVector();
    std::sort(after.begin(), after.end());
    std::cout << "After: ";
    for (size_t i = 0; i < after.size(); ++i) {
        std::cout << after[i] << " ";
    }
    std::cout << std::endl;
    std::clock_t start = std::clock();
    std::vector<int> sortedVector = fordJohnsonVector(_vector);
    std::clock_t end = std::clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC * 100;
    std::cout << "Time to process a range of " << sorter.getVector().size() << " elements with std::vector: " << elapsed << " us" << std::endl;
    // std::cout << "After vector: ";
    // for (size_t i = 0; i < sortedVector.size(); ++i) {
    //     std::cout << sortedVector[i] << " ";
    // }
    // std::cout << std::endl;
    start = std::clock();
    std::deque<int> sortedDeque = fordJohnsonDeque(_deque);
    end = std::clock();
    elapsed = double(end - start) / CLOCKS_PER_SEC * 100;
    std::cout << "Time to process a range of " << sorter.getVector().size() << " elements with std::deque: " << elapsed << " us" << std::endl;
    // std::cout << "After deque: ";
    // for (size_t i = 0; i < sortedDeque.size(); ++i) {
    //     std::cout << sortedDeque[i] << " ";
    // }
    // std::cout << std::endl;
}

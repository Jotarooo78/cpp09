#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <deque>
#include <cstdlib>

class PmergeMe {

    private :
        void fordJohnsonVector(std::vector<int> &vec);
        void insertBinaryVector(std::vector<int> &vec);
        void fordJohnsonDeque(std::deque<int> &dq);
        void insertBinaryDeque(std::deque<int> &dq);

    public :
        PmergeMe();
        ~PmergeMe();    
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &copy);
        void sort(int *arr, int size);
} ;

#endif
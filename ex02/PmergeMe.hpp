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

    public :
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &copy);
        void sortVec(int *arr, int size);
        void sortDeque(int *arr, int size);
} ;

#endif
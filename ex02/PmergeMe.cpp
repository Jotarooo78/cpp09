/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:56:23 by armaunito         #+#    #+#             */
/*   Updated: 2026/04/05 19:20:30 by armaunito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &copy) {
    (void)copy;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &copy) {
    if (this != &copy) {
        (void)copy;
    }
    return *this;
}

template <typename T>
void    printContainer(T &mainChain) {
    
    for (int i = 0; i < (int)mainChain.size(); i++) {
        std::cout << mainChain[i] << " ";
    }
    std::cout << "\n";
}


template <typename T>
void binarySearch(size_t value, T &mainChain, size_t limit) {

    size_t low = 0;
    size_t high = limit;
    
    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (mainChain[mid] > value)
            high = mid;
        else
            low = mid + 1;
    }
    mainChain.insert(mainChain.begin() + low, value);
}
template <typename T>
static T jacobsthalSequence(size_t n) {
    
    T jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    
    while (1) {
        size_t nxt = (jacob[jacob.size() - 1]) + 2 * (jacob[jacob.size() - 2]);
        if (nxt >= n)
            break ;
        jacob.push_back(nxt);
    }
    jacob.push_back(n);
    return jacob;
}

template <typename T>
void fordJohnson(T &container) {
    
    bool hasOdd = false;
    size_t lastValue;

    if (container.size() < 2)
        return ;
    
    T small;
    T big;

    if (container.size() % 2 != 0) {
        hasOdd = true;
        lastValue = container.back();
    }

    for (size_t i = 1; i < container.size(); i += 2) {
        if (container[i - 1] > container[i]) {
            small.push_back(container[i]);
            big.push_back(container[i - 1]);
        }
        else {
            small.push_back(container[i - 1]);
            big.push_back(container[i]);
        }
    }
    fordJohnson<T>(big);
    T mainChain = big;
    T jacob = jacobsthalSequence<T>(small.size());
    mainChain.insert(mainChain.begin(), small[0]);
    std::vector<bool> inserted(small.size(), false);
    inserted[0] = true;
    
    for (size_t i = 2; i < jacob.size(); i++) {
        size_t end = jacob[i];
        size_t start = jacob[i - 1];
        for (size_t j = end - 1; j >= start; j--) {
            if (inserted[j] == false) {
                binarySearch<T>(small[j], mainChain, mainChain.size());
                inserted[j] = true;
            }
        }
    }
    if (hasOdd) {
        binarySearch(lastValue, mainChain, mainChain.size());
    }
    container = mainChain;
}

template <typename T>
double timeToSort(T &container) {

    clock_t start = clock();
    fordJohnson<T>(container);
    clock_t end = clock();
    return static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
}

void PmergeMe::sortVec(int *arr, int size) {

    std::vector<size_t> vec(arr, arr + size);
    std::cout << "before : ";
    printContainer(vec);
    double sortTime = timeToSort(vec);
    std::cout << "Time to process a range of " << size << " elements with std::vector : " << sortTime << std::endl;    
    std::cout << "after : ";
    printContainer(vec);
    std::cout << '\n';
}

void PmergeMe::sortDeque(int *arr, int size) {

    std::vector<size_t> deq(arr, arr + size);
    std::cout << "before : ";
    printContainer(deq);
    double sortTime = timeToSort(deq);
    std::cout << "Time to process a range of " << size << " elements with std::deque : " << sortTime << std::endl;    
    std::cout << "after : ";
    printContainer(deq);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:56:23 by armaunito         #+#    #+#             */
/*   Updated: 2026/04/01 18:38:40 by armaunito        ###   ########.fr       */
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

void    printVec(std::vector<int> &mainChain) {
    
    for (int i = 0; i < (int)mainChain.size(); i++) {
        std::cout << mainChain[i] << " ";
    }
    std::cout << "\n";
}

void PmergeMe::sort(int *arr, int size) {
    
    std::vector<int> vec(arr, arr + size);
    // std::deque<int> deq(arr, arr + size);

    clock_t start = clock();
    fordJohnsonVector(vec);
    clock_t end = clock();
    std::cout << "Time to process a range of " << size << " elements with std::vector : " << static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000<< std::endl;
    printVec(vec);

    // clock_t start;
    // fordJohnsonDeque(deq);
    // clock_t end;
    // std::cout << "Time to process a range of " << size << " elements with std::deque : " << end - start << std::endl;
}


void binarySearch(int value, std::vector<int> &mainChain, int limit) {

    int low = 0;
    int high = limit;
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (mainChain[mid] > value)
            high = mid;
        else
            low = mid + 1;
    }
    mainChain.insert(mainChain.begin() + low, value);
}

static std::vector<int> jacobsthalSequence(int n) {
    
    std::vector<int> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    
    while (1) {
        int nxt = (jacob[jacob.size() - 1]) + 2 * (jacob[jacob.size() - 2]);
        if (nxt >= n)
            break ;
        jacob.push_back(nxt);
    }
    jacob.push_back(n);
    return jacob;
}

void PmergeMe::fordJohnsonVector(std::vector<int> &vec) {
    
    bool hasOdd = false;
    int lastValue;

    if (vec.size() < 2)
        return ;
    
    std::vector<int> small;
    std::vector<int> big;

    if (vec.size() % 2 != 0) {
        hasOdd = true;
        lastValue = vec.back();
    }

    for (size_t i = 1; i < vec.size(); i += 2) {
        if (vec[i - 1] > vec[i]) {
            small.push_back(vec[i]);
            big.push_back(vec[i - 1]);
        }
        else {
            small.push_back(vec[i - 1]);
            big.push_back(vec[i]);
        }
    }
    fordJohnsonVector(big);
    std::cout << "\\\\\\\\\\\\\\\\\\\\\\debug/////////////////\n";
    std::vector<int> mainChain = big;
    std::cout << "mainChain : ";
    printVec(mainChain);
    std::cout << "smallChain : ";
    printVec(small);
    std::cout << "bigChain : ";
    printVec(big);
    std::cout << "jacob : ";
    std::vector<int> jacob = jacobsthalSequence(small.size());
    printVec(jacob);
    mainChain.insert(mainChain.begin(), small[0]);
    std::vector<bool> inserted(small.size(), false);
    inserted[0] = true;
    
    std::cout << "small size : " << small.size() << "\n\n";

    for (size_t i = 2; i < jacob.size() - 1; i++) {
        size_t end = jacob[i];
        if (end < small.size())
        end = small.size();
        size_t start = jacob[i - 1];
        std::cout << "i = " << i << std::endl;
        for (size_t j = end - 1; j >= start; j--) {
            if (inserted[j] == false) {
                std::cout << "j = " << j << " | small[j] while the loop : " << small[j] << std::endl;
                binarySearch(small[j], mainChain, mainChain.size());
                inserted[j] = true;
            }
        }
    }
    if (hasOdd) {
        binarySearch(lastValue, mainChain, mainChain.size());
    }
    vec = mainChain;
}
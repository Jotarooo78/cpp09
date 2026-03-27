/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:56:23 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/27 19:18:32 by armosnie         ###   ########.fr       */
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

void PmergeMe::sort(int *arr, int size) {
    
    std::vector<int> vec(arr, arr + size);
    // std::deque<int> deq(arr, arr + size);

    clock_t start = clock();
    fordJohnsonVector(vec);
    clock_t end = clock();
    std::cout << "Time to process a range of " << size << " elements with std::vector : " << static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000<< std::endl;

    // clock_t start;
    // fordJohnsonDeque(deq);
    // clock_t end;
    // std::cout << "Time to process a range of " << size << " elements with std::deque : " << end - start << std::endl;
}


void binarySearch(int value, std::vector<int> &main, int mainSize) {

    int low = 0;
    int high = mainSize;
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (main[mid] > value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    main.insert(main.begin() + low, value);
}

static std::vector<int> jacobsthalSequence(int n) {
    
    std::vector<int> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    
    while (1) {
        int nxt = (jacob[jacob.size() - 1] - 1) + 2 * (jacob[jacob.size()] - 2);
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

    for (int i = 1; i < static_cast<int>(vec.size()); i += 2) {
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
    std::vector<int> main = big;
    main.insert(main.begin(), small[0]);

    std::vector<int> jacob = jacobsthalSequence(small.size());
    std::vector<bool> inserted(small.size(), false);
    inserted[0] = true;
    
    for (int i = 1; i < static_cast<int>(jacob.size()); i++) {
        int idx = jacob[i] - 1;
        if (idx >= static_cast<int>(small.size()))
            idx = small.size() - 1;
        for (int j = i; j > jacob[i - 1] - 1; j--) {
            if (j < static_cast<int>(small.size()) && inserted[j] == false) {
                int bound = static_cast<int>(main.size());
                binarySearch(small[j], main, bound);
                inserted[j] = true;
            }
        }
    }
    if (hasOdd)
        binarySearch(lastValue, main, main.size());
    vec = main;
}
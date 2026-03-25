/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:56:23 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/25 17:03:14 by armaunito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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
    std::deque<int> deq(arr, arr + size);

    clock_t start;
    fordJohnsonVector(vec);
    clock_t end;
    std::cout << "Time to process a range of " << size << " elements with std::vector : " << end - start << std::endl;

    clock_t start;
    fordJohnsonDeque(deq);
    clock_t end;
    std::cout << "Time to process a range of " << size << " elements with std::deque : " << end - start << std::endl;
}



void PmergeMe::fordJohnsonVector(std::vector<int> &vec) {
    
    if (vec.size() < 2)
        return ;
    
    std::vector<int> small;
    std::vector<int> big;

    for (int i = 1; i < vec.size(); i += 2) {
        if (vec[i - 1] > vec[i]) {
            small.push_back(vec[i]);
            big.push_back(vec[i - 1]);
        }
        else {
            small.push_back(vec[i - 1]);
            big.push_back(vec[i]);
        }
    }
    if (vec.size() % 2 != 0) {
        int lastValue = vec.back();
    }
    fordJohnsonVector(big);
    std::vector<int> main;
    for (int i = 0; big.size() != 0 && big[i]; i++) {
        main.push_back(small[0]);
        main.push_back(big[i]);
    }
    for (int i = 1; small.size() != 0 && small[i]; i++) {
        binaryResearch(small[i], main);
    }
    big = main;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:00:03 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/30 18:59:16 by armaunito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    int *arr = new int[argc -1];
    for (int i = 1; i < argc - 1; i++) { // ajouter un peu de parcing
        arr[i - 1] = atoi(argv[i]);
    }
    PmergeMe Pm;
    Pm.sort(arr, argc - 1);
    
    
    delete[] arr;
    return 0;
}
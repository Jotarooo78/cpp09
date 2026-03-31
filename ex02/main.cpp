/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:00:03 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/31 19:35:11 by armaunito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    int *arr = new int[argc - 1];
    for (int i = 1; i < argc; i++) { // ajouter un peu de parcing
        for (int j = 0; argv[i][j]; j++) {
            if (!isdigit(argv[i][j])) {
                delete [] arr;
                return 1;
            }
        }
        arr[i - 1] = atoi(argv[i]);
        if (arr[i - 1] <= 0) {
                delete [] arr;
                return 1;
        }
        std::cout << "arr[i] : " << arr[i - 1] << std::endl;
    }
    PmergeMe Pm;
    Pm.sort(arr, argc - 1);
    

    delete[] arr;
    return 0;
}
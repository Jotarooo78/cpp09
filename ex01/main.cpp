/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:29:47 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/24 16:27:26 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv) {
   
   if (argc != 2) {
      std::cerr << "Usage: ./RPN number" << std::endl;
      return 1;
   }
   RPN num;
   if (num.algo(argv[1]) == false) {
      std::cerr << "invalid inverted Polish mathematical expression" << std::endl;
      return 1;
   }
   return 0;
}
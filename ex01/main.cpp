/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:29:47 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/16 18:53:10 by armaunito        ###   ########.fr       */
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
      std::cerr << "invalid inverted Polish mathematical expression as argument" << std::endl;
      return 1;
   }
   return 0;
}
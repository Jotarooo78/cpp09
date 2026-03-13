/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:29:47 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/13 15:58:03 by armaunito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
   
   if (argc != 2) {
      std::cerr << "Usage: ./btc <input_file>" << std::endl;
      return 1;
   }
   BitcoinExchange btc;
   btc.parseAndDisplay(argv[1]);
   return 0;
}
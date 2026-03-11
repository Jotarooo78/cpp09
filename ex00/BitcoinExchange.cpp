/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:39:02 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/11 18:42:09 by armaunito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy) {}

bool BitcoinExchange::isValidDate(const std::string &date) {
   
   try {
      if (date.empty() || date.length() != 10)
         return false;
      for (int i = 0; i < 10; i++) {
         if (i == 4 || i == 7) {
            if (date[i] != '-')
               return false;
         }
         else if (!isdigit(date[i])) {
            return false;
         }
      }
      int year = atoi(date.substr(0, 4).c_str());
      int month = atoi(date.substr(5, 2).c_str());
      int day = atoi(date.substr(8, 2).c_str());

      if (year < 2009 || year > 2100)
         return false;
      if (month < 1 || month > 12)
         return false;
      if (day < 1 || day > 31)
         return false;
      if (month == 2) {
         if (day > 29)
            return false;
         if (day == 29) {  
            bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            if (!isLeap) 
               return false;
         }
      }
      else if (month == 4 || month == 6 || month == 9 || month == 11) {
         if (day > 30)
            return false;
      }
      return true;
   }
   catch (const std::invalid_argument& e) {
      return false; 
   }
   catch (const std::out_of_range& e) {
      return false;
   }
}

bool BitcoinExchange::isValidValue(const std::string &value) {
   
   try {
      if (value.empty())
         return false;
      size_t pos;
      double num = std::stod(value, &pos);
      if (num < 0 || num > 1000 || pos != value.length())
         return false;
      return true;
   }
   catch (const std::invalid_argument& e) {
      return false; 
   }
   catch (const std::out_of_range& e) {
      return false;
   }
}

double BitcoinExchange::findClosestRate(const std::string &date) {
   
   auto it = _database.lower_bound(date);
   
   if (it != _database.end() && it->first == date)
      return it->second;
   if (it == _database.begin())
      throw std::runtime_error("Error: date too old");
   if (it == _database.end()) {
      it--;
      return it->second;
   }
   it--;
   return it->second;
}

std::string BitcoinExchange::trim(std::string &line) {

   size_t start = line.find_first_not_of(" \t");
   if (start == std::string::npos)
      return line;
   size_t end = line.find_last_not_of(" \t");
   size_t length = end - start + 1;
   return line.substr(start, length);
}

void BitcoinExchange::parseDataBase(const std::string &filename) {

   std::ifstream file;

   file.open(filename);
   if (!file.is_open()) {
      std::cerr << "Error: could not open file " << filename << std::endl;
      return;
   }
   std::string line;
   std::string date;
   std::string valueStr;
   double value;
   
   getline(file, line);
   
   while (getline(file, line)) {
      
      if (line.empty())
         continue;
         
      line = trim(line);
      if (line.empty())
         continue;

      size_t commaPos = line.find(',');
      if (commaPos == std::string::npos) {
         std::cerr << "Error: bad input format " << line << std::endl;
         return;
      }
      date = line.substr(0, commaPos);
      date = trim(date);
      if (isValidDate(date) == false) {
         std::cerr << "Error: bad date format " << date << std::endl;
         continue ;
      }
      valueStr = line.substr(commaPos + 1);
      valueStr = trim(valueStr);
      if (isValidValue(valueStr) == false) {
         std::cerr << "Error: bad value format " << valueStr << std::endl;
         continue ;
      }
      value = std::stod(valueStr);
      _database.insert(std::make_pair(date,value));
   }
   file.close();
}

void BitcoinExchange::processInputFile(const std::string &filename) {

   std::ifstream file;

   file.open(filename);
   if (!file.is_open()) {
      std::cerr << "Error: could not open file " << filename << std::endl;
      return;
   }
   std::string line;
   std::string date;
   std::string valueStr;
   double value;
   
   getline(file, line);
   while (getline(file, line)) {
      
      if (line.empty())
         continue;
         
      line = trim(line);
      if (line.empty())
         continue;

      size_t commaPos = line.find(',');
      if (commaPos == std::string::npos) {
         std::cerr << "Error: bad input format " << line << std::endl;
         return;
      }
      date = line.substr(0, commaPos);
      date = trim(date);
      if (isValidDate(date) == false) {
         std::cerr << "Error: bad date format " << date << std::endl;
         continue ;
      }
      valueStr = line.substr(commaPos + 1);
      valueStr = trim(valueStr);
      if (isValidValue(valueStr) == false) {
         std::cerr << "Error: bad value format " << valueStr << std::endl;
         continue ;
      }
      value = std::stod(valueStr);
      _database.insert(std::make_pair(date,value));
   }
   file.close();
}

//2009-01-02,0

//2011-01-03 | 3
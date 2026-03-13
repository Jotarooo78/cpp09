/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:39:02 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/13 17:14:04 by armaunito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) {
   (void)copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy) {

   if (this != &copy) {
      (void)copy;
   }
   return *this;
}

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

bool BitcoinExchange::isValidValue(const std::string &value, double &outValue, int option) {
   
   try {
      if (value.empty())
         return false;

      char *endPtr;
      double num = std::strtod(value.c_str(), &endPtr);
      if (*endPtr != '\0') {
         std::cerr << "Error: bad line format " << value << std::endl; // ici
         return false ;
      }
      if (option == 1) {
         if (num < 0 || num > 1000) {
         std::cerr << "Error: btc > 1000 or btc < 0 : " << value << std::endl; // ici
         return false ;
         }
      }
      else  {
         if (num < 0) {
            std::cerr << "Error: btc < 0 : " << value << std::endl; // ici
            return false ;
         }
      }
      outValue = num;
      return true;
   }
   catch (const std::invalid_argument& e) {
      return false;
   }
   catch (const std::out_of_range& e) {
      return false;
   }
   return false;
}

double BitcoinExchange::findClosestRate(const std::string &date) {
   
   std::map<std::string, double>::iterator it = _database.lower_bound(date);
   
   if (it != _database.end() && it->first == date)
      return it->second;
   if (it == _database.begin()){
         std::cerr << "Error: bad line format " << std::endl;
         return false ;
   }
   if (it == _database.end()) {
      it--;
      return it->second;
   }
   it--;
   return it->second;
}

void  BitcoinExchange::trim(std::string &line) {

   size_t start = line.find_first_not_of(" \t");
   if (start == std::string::npos) {
      std::cerr << "Error: bad line format " << line << std::endl;
      return ;
   }
   size_t end = line.find_last_not_of(" \t");
   size_t length = end - start + 1;
   line = line.substr(start, length);
}

void BitcoinExchange::parseDataBase(const char *dataBase) {

   std::ifstream file(dataBase);

   if (!file.is_open()) {
      std::cerr << "Error: could not open file " << dataBase << std::endl;
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
         
      trim(line);
      if (line.empty())
         continue;
         
      size_t comaPos = line.find(',');
      if (comaPos == std::string::npos) {
         std::cerr << "Error: bad input format " << line << std::endl;
         continue ;
      }
      date = line.substr(0, comaPos);
      trim(date);
      if (isValidDate(date) == false) {
         std::cerr << "Error: bad date format " << date << std::endl;
         continue ;
      }
      valueStr = line.substr(comaPos + 1);
      trim(valueStr);
      

      if (!isValidValue(valueStr, value, 0)) {
         std::cerr << "Error: bad value format " << valueStr << std::endl;
         continue;
      }
      _database.insert(std::make_pair(date, value));
   }
   file.close();
}

void BitcoinExchange::processInputFile(const std::string &inputTxt) {

   std::ifstream file(inputTxt.c_str());

   if (!file.is_open()) {
      std::cerr << "Error: could not open file " << inputTxt << std::endl;
      return;
   }
   std::string line;
   std::string date;
   std::string valueStr;
   double value;
   bool firstLine = true;
   
   while (getline(file, line)) {
      
      if (line.empty())
         continue;
         
      trim(line);
      if (line.empty() || line =="")
         continue;
      
      if (firstLine == true) {
         firstLine = false;
         if (line.find("date") != std::string::npos || line.find("value") != std::string::npos || line.find("|") == std::string::npos) {
            continue ;
         }
      }

      size_t pipePos = line.find('|');
      if (pipePos == std::string::npos) {
         std::cerr << "Error: bad input format " << line << std::endl;
         continue;
      }
      date = line.substr(0, pipePos);
      trim(date);
      if (isValidDate(date) == false) {
         std::cerr << "Error: bad date format " << date << std::endl;
         continue ;
      }
      valueStr = line.substr(pipePos + 1);
      trim(valueStr);
         
      if (isValidValue(valueStr, value, 1)) {
         double rate = findClosestRate(date);
         double res = value * rate;
         std::cout << date << " -> " << value << " = " << res << std::endl;
      }
   }
   file.close();
}

void BitcoinExchange::parseAndDisplay(const std::string &filename) {

   const char *dataBase = "data.csv";
   parseDataBase(dataBase);
   processInputFile(filename);
}

//2014-05-13,442.45

//2011-01-03 | 3
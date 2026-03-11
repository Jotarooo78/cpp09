#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>

class BitcoinExchange {

   private :
      std::map<std::string, double> _database;
      bool isValidDate(const std::string &date);
      bool isValidValue(const std::string &value);
      double findClosestRate(const std::string &date);
      void parseDataBase(const std::string &file);

   public :
      BitcoinExchange();
      ~BitcoinExchange();
      BitcoinExchange(const BitcoinExchange &copy);
      BitcoinExchange &operator=(const BitcoinExchange &copy);

      void processInputFile(const std::string& filename);
      std::string trim(std::string &line);

      // class BitcoinException : public std::exception {
      //    private:
      //       std::string _message;
      //    public:
      //       BitcoinException(const std::string& msg) : _message(msg) {}
      //       virtual const char* what() const throw() {
      //          return _message.c_str();
      //       }
      //       virtual ~BitcoinException() throw() {}
      // };
} ;


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:08:35 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/24 18:18:17 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <limits>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &copy) {
    (void)copy;
}

RPN &RPN::operator=(const RPN &copy) {
        if (this != &copy) {
        (void)copy;
    }
    return *this;
}


bool isOperator(char word) {
    if (word == '-' || word == '+' || word == '*' || word == '/')
        return true;
    return false;
}

bool RPN::algo(char *arg) {
    
    std::istringstream iss(arg);
    std::string word;
    char op;
    long long insertNum = 0;
    long long num1 = 0;
    long long num2 = 0;
    int numCount = 0;
    int opCount = 0;
    long long res = 0;

    while (iss >> word) {
        if (word.empty())
            return false;
        if (word.length() > 1 || word.length() < 1)
            return false;
        if (isdigit(word[0])) {
            insertNum = word[0] - '0';
            _stack.push(insertNum);
            numCount++;
        }
        else if (isOperator(word[0])) {
            if (_stack.size() < 2) {
                std::cerr << "Invalid position or number of operator signs" << std::endl;
                return false;
            }
            opCount++;
            op = word[0];
            num2 = _stack.top();
            _stack.pop();
            num1 = _stack.top();
            _stack.pop();
            switch(op) {
                case '+' : 
                    res = num1 + num2;
                    break;
                case '-' : 
                    res = num1 - num2;
                    break;
                case '*' : 
                    res = num1 * num2;
                    break;
                case '/' : 
                    if (op == '/' && num2 == 0)
                        return false;
                    res = num1 / num2;
                    break;
                default : return false;
            }
            if (res > std::numeric_limits<int>::max() || res < std::numeric_limits<int>::min()) {
                std::cerr << "Int Overflow or Underflow" << std::endl;
                return false;
            }
            _stack.push(res);
        }
        else {
            std::cerr << "Unauthorized character found : " << word[0] << std::endl;
            return false;
        }
    }
    res = _stack.top();
    _stack.pop();
    if (numCount - 1 != opCount) {
        std::cerr << "Too many or few numbers" << std::endl;
        return false;
    }
    std::cout << res << std::endl;
    return true;
}

//$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
// 42
// $> ./RPN "7 7 * 7 -"
// 42
// $> ./RPN "1 2 * 2 / 2 * 2 4 - +"
// 0
// $> ./RPN "(1 + 1)"
// Error
// $>



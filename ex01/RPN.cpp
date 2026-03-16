/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaunito <armaunito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:08:35 by armaunito         #+#    #+#             */
/*   Updated: 2026/03/16 19:15:05 by armaunito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

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

int RPN::add(int a, int b) {
    return a + b;
}

int RPN::sub(int a, int b) {
    return a - b;
}

int RPN::mul(int a, int b) {
    return a * b;
}

int RPN::divi(int a, int b) {
    return a / b;
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
    int insertNum;
    int num1;
    int num2;
    int res;
    int numCount = 0;
    int opCount = 0;

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
                std::cerr << "Too many or few operator signs" << std::endl;
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
                    res = add(num1, num2);
                    break;
                case '-' : 
                    res = sub(num1, num2);
                    break;
                case '*' : 
                    res = mul(num1, num2);
                    break;
                case '/' : 
                    if (op == '/' && num2 == 0)
                        return false;
                    res = divi(num1, num2);
                    break;
                default : return false;
            }
        }
        else {
            std::cerr << "Unauthorized character found : " << word[0] << std::endl;
            return false;
        }
        _stack.push(res);
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
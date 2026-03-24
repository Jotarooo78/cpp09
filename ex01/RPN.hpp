#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <algorithm>
#include <stack>
#include <sstream>

class RPN {

    private :
        std::stack<int> _stack;

    public :
        RPN();
        ~RPN();
        RPN(const RPN &copy);
        RPN &operator=(const RPN &copy);

        bool algo(char *arg);
} ;

#endif
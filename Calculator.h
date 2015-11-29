
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Operations.h"
#include <map>
#include <functional>
#include <iostream>

template <typename T> class Calculator {
public:
    // constructor
    Calculator() {
        operation.insert(std::make_pair('+',addition<T>()));
        operation.insert(std::make_pair('-',subtraction<T>()));
        operation.insert(std::make_pair('*',multiplication<T>()));
        operation.insert(std::make_pair('/',division<T>()));
    }
    // overload function call to access operation
    T operator()(char c, const T& t1, const T& t2) {
        if (check_operattion(c)) {return operation[c](t1,t2);}
        std::cerr << c << " not a valid operation\n";
        return 0;
    }
private:
    std::map<char,std::function<T(T,T)>> operation;
    bool check_operattion(char c) {
        if (operation.find(c) == operation.end()) {return false;}
        return true;
    }
};

#endif


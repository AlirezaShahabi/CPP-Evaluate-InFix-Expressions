
#include "Stack.h"
#include "Calculator.h"
#include <sstream>
#include <iostream>
#include <string>

// check if a character represent a number
bool is_char_digit(char c) {
    if (c >= '0' && c <= '9') {return true;}
    return false;
}

// check if a character represents an operation
bool is_char_operator(char c) {
    if (operation_list.find(c) != std::string::npos) {return true;}
    return false;
}

// check if an string of characters represents a number
bool is_str_integer(const std::string& str) {
    for (const auto& c:str) {if (!is_char_digit(c)) {return false;}}
    return true;
}

// check if an string of characters represents an operation
bool is_str_operator(std::string str) {
    if (is_char_operator(str[0]) && str.length() == 1) {return true;}
    return false;
}

// check if string is "("
bool is_open_par(std::string str) {
    if (str[0] == '(' && str.length() == 1) {return true;}
    return false;
}

// check if string is ")"
bool is_close_par(std::string str) {
    if (str[0] == ')' && str.length() == 1) {return true;}
    return false;
}

// check if operator1 has higher precedence tham operator2
bool higher_precedence(std::string operator1, std::string operator2) {
    if (operator1 == "+" && operator2 == "-") {return true;}
    if (operator1 == "-" && operator2 == "+") {return true;}
    int pos1 = operation_list.find(operator1[0]);
    int pos2 = operation_list.find(operator2[0]);
    if (pos1 <= pos2) {return true;}
    return false;
}

// transform character string of integers into integer
// e.g. "429" to 429
int string_to_integer(const std::string& str) {
    Stack<int> digits;
    int ref = static_cast<int>('0');
    for (const auto& c:str) {
        digits.push(static_cast<int>(c) - ref);
    }
    int number = 0;
    int ten_power = 1;
    for (int i = 0; i < str.size(); ++i) {
        number += digits.top() * ten_power;
        digits.pop();
        ten_power *= 10;
    }
    return number;
}

// transform a messy expression to a nicely space separated
// expression. e.g. "3*(  4+2)- 5" to "3 * ( 4 + 2 ) - 5"
void space_separate(const std::string& messy, std::string& nice) {
    size_t i = 0;
    char sep = ' ';
    while (i != messy.size()) {
        if (messy[i] == ' ') {
            ++i;
        } else if (messy[i] == '(' || messy[i] == ')' ||
                   is_char_operator(messy[i])) {
            nice.push_back(messy[i]);
            nice.push_back(sep);
            ++i;
        } else if (is_char_digit(messy[i])) {
            while (is_char_digit(messy[i])) {
                nice.push_back(messy[i]);
                ++i;
            }
            nice.push_back(sep);
        } else {
            std::cerr << "undefined character\n";
            return;
        }
    }
}


// transform a space separated in-fix expression into a
// post-fix expression
void infix_to_postfix(const std::string& infix, std::string& postfix) {
    Stack<std::string> operators;
    std::istringstream iss(infix);
    std::string token;
    std::string sep = " ";
    while (iss >> token) {
        if (is_str_integer(token)) {
            postfix += token;
            postfix += sep;
        } else if (is_str_operator(token)) {
            while (!operators.is_empty() && !is_open_par(operators.top()) &&
                   higher_precedence(operators.top(), token)) {
                postfix += operators.top();
                postfix += sep;
                operators.pop();
            }
            operators.push(token);
        } else if (is_open_par(token)) {
            operators.push(token);
        } else if (is_close_par(token)) {
            while (!operators.is_empty() && !is_open_par(operators.top())) {
                postfix += operators.top();
                postfix += sep;
                operators.pop();
            }
            operators.pop();
        } else {
            std::cerr << "undefined character\n";
            return;
        }
    }
    while (!operators.is_empty()) {
        postfix += operators.top();
        postfix += sep;
        operators.pop();
    }
}

// evaluate the value of a post-fix expression
// all operands and operations are separated by single space
int postfix_evaluate(const std::string& expression) {
    Stack<int> post_fix;
    Calculator<int> cal;
    std::string token;
    std::istringstream iss(expression);
    while (iss >> token) {
        if (is_str_integer(token)) {
            post_fix.push(string_to_integer(token));
        } else if (is_str_operator(token)) {
            int number2 = post_fix.top();
            post_fix.pop();
            int number1 = post_fix.top();
            post_fix.pop();
            post_fix.push(cal(token[0], number1, number2));
        } else {
            std::cerr << "undefined character\n";
            return -1;
        }
    }
    return post_fix.top();
}

// Main function: evaluates the value of an expression made of:
// positive integers
// operators: + - * /
// paranthesis: ( )
int Evaluate_Expression(const std::string& expression) {
    std::string space_sep_exp = "";
    space_separate(expression, space_sep_exp);
    std::string postfix_expression = "";
    infix_to_postfix(space_sep_exp, postfix_expression);
    int result = postfix_evaluate(postfix_expression);
    return result;
}




#include "Functions.cpp"
#include <iostream>
#include <string>


int main() {
    
    std::string exp1 = "21+5*(24-14)-(70/7)";
    std::cout << Evaluate_Expression(exp1) << std::endl;
    
    std::string exp2 ="3   *3 +   4 *4-5* 5";
    std::cout << Evaluate_Expression(exp2) << std::endl;

    std::string exp3 = "1*100/10 + (5 - (44/11)*(8-9)) +(1)";
    std::cout << Evaluate_Expression(exp3) << std::endl;
    
    std::string exp4 = " (245 + 405 - 50) /(2-5+5+13)";
    std::cout << Evaluate_Expression(exp4) << std::endl;
    
    std::string exp5 = "20*3*8/4*10*2";
    std::cout << Evaluate_Expression(exp5) << std::endl;
    return 0;
}


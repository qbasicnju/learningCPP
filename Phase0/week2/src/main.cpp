#include <iostream>
#include "numeric_utils.hpp"

// TODO: write a numeric_utils.hpp with mean, stddev, linspace, clamp
// (overloaded for float and double), then exercise them here.

int main()
{
    std::cout << "Week 2 Project\n";
    std::vector<double> data {1.1, 2.5, 6.5, 7.6, 15.2, 9.36};
    double m = mean(data);
    double sigma = stddev(data);
    std::cout << "The mean of the data sets is " << m << std::endl;
    std::cout << "The standard deviation of the data set is " << sigma << std::endl;

    double d_val = clamp(5.0, -2.5, 10.0);
    float f_val = clamp(5.0f, -2.5f, 10.0f);

    std::cout << "Function overload" << std::endl;
    std::cout << "The value of d_val: " << d_val << std::endl;
    std::cout << "The value of f_val: " << f_val << std::endl;  
    std::cout << "The size of data type of d_val (double) is " <<sizeof(d_val) << std::endl;
    std::cout << "The size of data type of f_val (float) is " <<sizeof(f_val) << std::endl;

    std::vector<double> res = linspace(0.0, 10.0, 5);
    for(double val : res){
        std::cout << val << " ";
    }
    std::cout << std::endl;

    /*
    int threshold = 1;
    if(res.size() < threshold) { } //  warning: comparison of integer expressions of different signedness; the warning becomes error under -Werror
    */
    return 0;
}

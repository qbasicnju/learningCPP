#include"numeric_utils.hpp"
#include<stdexcept>

double mean(const std::vector<double>& data) 
{
    if(data.empty()) {
        throw std::invalid_argument("mean: input vector can not be empty!");
    }

    double sum{0.0};
    for(double value : data) {
        sum += value; 
    }
    return sum / data.size();
}

double stddev(const std::vector<double>& data)
{
    if(data.empty()) {
        throw std::invalid_argument("stddev: input vector can not be empty!");
    }

    double sum{0.0};
    double mu = mean(data);
    for (double val : data) {
        sum += (val - mu) * (val - mu);
    }
    double variance = sum / data.size();
    return std::sqrt(variance);
}

double clamp(const double value, const double min, const double max)
{
    if(value < min) {
        return min;
    }
    else if(value > max) {
        return max;
    }
    else {
        return value;
    }
}

float clamp(const float value, const float min, const float max)
{
    if(value < min) {
        return min;
    }
    else if(value > max) {
        return max;
    }
    else {
        return value;
    }
}

std::vector<double> linspace(const double start, const double end, const int num_points)
{
    if(num_points < 2) {
        throw std::invalid_argument("linspace: the nums of points can not be less than 2!");
    }

    double left  = std::min(start, end);
    double right = std::max(start, end);

    double increment = (right - left) / (num_points - 1);

    std::vector<double> results(num_points);
    double val = left;
    for(int i{0}; i < num_points; ++i) {
        results.push_back(val);
        val += increment;
    }

    return results;
}
#pragma once
#include<cmath>
#include<vector>

double mean(const std::vector<double>& data);

double stddev(const std::vector<double>& data);

std::vector<double> linspace(const double start, const double end, const int num_points);

constexpr double clamp(const double value, const double min, const double max)
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

constexpr float clamp(const float value, const float min, const float max)
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
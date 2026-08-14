#pragma once
#include<cmath>
#include<vector>

double mean(const std::vector<double>& data);

double stddev(const std::vector<double>& data);

double clamp(const double value, const double min, const double max);
float clamp(const float value, const float min, const float max);
std::vector<double> linspace(const double start, const double end, const int num_points);

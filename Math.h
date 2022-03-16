#ifndef MATH_H
#define MATH_H
#include <vector>
double scalar_mul(const std::vector<double>& x,
	const std::vector<double>& y);
double sigmoid(const double& x);
double sigmoid_der(const double& x);
std::vector<double> normalize ( const std::vector<std::vector<double>>& x);
std::vector<double> vector_diff(const std::vector<double>& x,
	const std::vector<double>& y);
std::vector<double> vector_sum(const std::vector<double>& x,
	const std::vector<double>& y);
#endif

#include "Math.h"
#include <cmath>
double scalar_mul(const std::vector<double>& x,
	const std::vector<double>& y){
    double res = 0;
    for (int i = 0; i < x.size(); i++) {
        res += x[i] * y[i];
    }
    return res;
}

double sigmoid(const double& x)
{
    return 1 / (1 + exp(-x));
}

double sigmoid_der(const double& x)
{
    return x*(1-x);
}

std::vector<double> normalize(const std::vector<std::vector<double>>& x)
{
    std::vector<double> res(x[1].size());
    for (std::vector<double> vec : x) {
        res = vector_sum(res, vec);
    }
    for (double& iter : res) {
        iter /= x.size();
    }
    return res;
}

std::vector<double> vector_diff(const std::vector<double>& x, const std::vector<double>& y)
{
    std::vector<double> res(x.size());
    for (int i = 0; i < res.size(); i++) {
        res[i] = x[i] - y[i];
    }
    return res;
}

std::vector<double> vector_sum(const std::vector<double>& x, const std::vector<double>& y)
{
    std::vector<double> res(x.size());
    for (int i = 0; i < res.size(); i++) {
        res[i] = x[i] + y[i];
    }
    return res;
}

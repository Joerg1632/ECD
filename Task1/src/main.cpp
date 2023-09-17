#include <iostream>
#include <cmath>
using namespace std;

double factorial(int n) {
    double result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double power(double x, int n) {
    double result = 1;
    for (int i = 0; i < n; ++i) {
        result *= x;
    }
    return result;
}

double sinTaylorSeries(double x, int terms) {
    double result = 0;
    for (int n = 0; n < terms; ++n) {
        double term = power(-1, n) * power(x, 2 * n + 1) / factorial(2 * n + 1);
        result += term;
    }
    return result;
}

int main() {
    double x = 5;
    int N = 50000;

    double sinX = sinTaylorSeries(x, N);

    return 0;
}
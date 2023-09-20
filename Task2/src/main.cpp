#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

double fact(long long n) {
    long long result = 1;
    for (long long i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double sinTaylorSeries(double x, long long terms) {
    long double result = 0;
    for (long long n = 0; n < terms; ++n) {
        long double term = pow(-1, n) * pow(x, 2 * n + 1) / fact(2 * n + 1);
        result += term;
    }
    return result;
}

int main(int argc, char* argv[]) {
    long double x = 5;
    size_t n = stoull (argv[1]);

    long double sinX = sinTaylorSeries(x, n);

    return 0;
}


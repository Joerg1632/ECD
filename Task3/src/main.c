#include <stdio.h>
#include <math.h>

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
    size_t n = strtoull(argv[1], NULL, 10);

    long double sinX = sinTaylorSeries(x, n);
    printf("%Lf\n", sinX);
    return 0;
}

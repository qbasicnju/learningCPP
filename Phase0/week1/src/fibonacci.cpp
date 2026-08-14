#include "fibonacci.hpp"

long long fibonacci(int n) {
    long long prePrev {0};
    long long prev {1};
    long long result {0};
    if (n == 1){
        return prev;
    }
    for (int i = 2; i <= n; ++i) {
        result = prePrev + prev;
        prePrev = prev;
        prev = result;
    }
    return result;
}
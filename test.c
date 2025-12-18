#include <math.h>
#include <stdio.h>
#include <limits.h>

int main() {
    int n = -2147483648;
    int m = n << 8;
    int b = m >> 8;
    printf("%d %d %d\n", n);
    return 0;
}

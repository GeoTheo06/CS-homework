#include <stdio.h>

int is_palindrome(long long x) {
    long long reversed = 0, original = x;
    while (x > 0) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }
    return reversed == original;
}

int main() {
    long long n;
    scanf("%lld", &n);
    const long long max = 2147483647;

    while (1) {
        if (is_palindrome(n)) {
            printf("NO\n");
            return 0;
        }
        long long rev = 0, temp = n;
        while (temp > 0) {
            rev = rev * 10 + temp % 10;
            temp /= 10;
        }
        long long new_n = n + rev;
        if (new_n > max) {
            printf("YES\n");
            return 0;
        }
        n = new_n;
    }
}
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte, boolean;
// Euler's Linear sieve
#define MAXN 100000

boolean not_prime[MAXN + 5];
int primes[MAXN + 5], nprime = 0;

void prime_init(int n) {
    not_prime[0] = not_prime[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!not_prime[i])
            primes[nprime++] = i;
        for (int j = 0; j < nprime && i * primes[j] <= n; j++) {
            not_prime[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main()
{
    prime_init(MAXN);
    int n;
    scanf("%d", &n);
    while (n--) {
        int x;
        scanf("%d", &x);
        if (!not_prime[x])
            printf("%d ", x);
    }
    return 0;
}
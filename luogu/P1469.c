#include <stdio.h>
int main()
{
    int n, x, s = 0;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &x);
        s ^= x;
    }
    printf("%d", s);
    return 0;
}
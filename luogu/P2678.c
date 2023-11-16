#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max(a,b) ((a)>(b)?(a):(b))
int dis[50005];// [0]: start, [N + 1] : finish
int L, N, M;

bool check(int Length) {
    int cnt = 0;
    int p = 0, q = 0;
    if (Length > L) return false;
    for (q = 1; q <= N ; q++) { // q < N?
        if (dis[q] - dis[p] < Length)
            cnt++;
        else p = q;
    }
    return cnt <= M;
}

int main()
{
    scanf("%d%d%d", &L, &N, &M);
    dis[0] = 0; dis[N + 1] = L;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &dis[i]);
    }

    int l = 0, r = L;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        bool f1 = check(mid);
        bool f2 = l < L && check(mid + 1);
        if(f1 && !f2) {
            printf("%d", mid);
            break;
        }
        else if (f1 && f2) l = mid + 1;
        else r = mid - 1;
    }


    return 0;
}
/*
25 5 2 
2
11
14
17 
21
*/
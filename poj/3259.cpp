#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FOR_RANGE_EQ(iter,start,end) for (int iter = start; iter <= end; ++iter)
#define FOR_RANGE_LT(iter,start,end) for (int iter = start; iter < end; ++iter)
inline static void update_max(int *v, const int m) { if (m > *v) *v = m; }
inline static void update_min(int *v, const int m) { if (m < *v) *v = m; }

#define N 500
int dist[N + 5][N + 5];

int main(int argc, char *argv[]) {
    int F;
    scanf("%d", &F);
    while (F--) {
        int n, m, w;
        scanf("%d%d%d", &n, &m, &w);
        memset(dist, 0x3f, sizeof(dist));
        FOR_RANGE_EQ(i, 1, n)
            dist[i][i] = 0;
        FOR_RANGE_EQ(i, 1, m) {
            int s, e, t;
            scanf("%d%d%d", &s, &e, &t);
            update_min(&dist[s][e], t);
            update_min(&dist[e][s], t);
        }
        FOR_RANGE_EQ(i, 1, w) {
            int s, e, t;
            scanf("%d%d%d", &s, &e, &t);
            update_min(&dist[s][e], -t);
        }

        int flg = 0;
        FOR_RANGE_EQ(k, 1, n) {
            FOR_RANGE_EQ(i, 1, n) {
                FOR_RANGE_EQ(j, 1, n)
                    update_min(&dist[i][j], dist[i][k] + dist[k][j]);
                if (dist[i][i] < 0) {
                    flg = 1;
                    k = n + 1;
                    break;
                }
            }
        }
        if (flg)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
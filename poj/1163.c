#include <stdio.h>

int tri[105][105];
int s[105][105];

inline static int my_max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &tri[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            s[i][j] = tri[i][j];
            int m = 0;
            if (i >= 1) {
                m = s[i - 1][j];
                if (j >= 1)
                    m = my_max(m, s[i - 1][j - 1]);
                s[i][j] += m;
            }
            // fprintf(stderr, "%d ", s[i][j]);
        }
        // fprintf(stderr, "\n");
    }
    int ans = 0;
    for (int j = 0; j < n; j++) {
        ans = my_max(ans, s[n - 1][j]);
    }

    printf("%d\n", ans);

    return 0;
}
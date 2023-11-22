#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>

#define MAXN 1000
#define EPS 1e-12

int main() {
    int n;
    double t;
    while (scanf("%d %lf", &n, &t) > 0) {
        static double d[MAXN], s[MAXN];
        double s_min = MAXN;
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &d[i], &s[i]);
            if (s[i] < s_min)
                s_min = s[i];
        }
        double c_min = -s_min, c_max = 1e9+7;
        double c = c_max;
        while ((c_max - c_min) >= EPS) {
            c = (c_min + c_max) / 2;
            // check
            double t_sum = 0;
            for (int i = 0; i < n; i++) {
                t_sum += d[i] / (s[i] + c);
            }
            if (fabs(t_sum - t) < EPS)
                break;
            else if (t_sum > t)
                c_min = c;
            else
                c_max = c;
        }
        printf("%.15lf\n", c);
    }
    return 0;
}
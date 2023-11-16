#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <map>
#include <set>
using namespace std;

#define FOR_REPEAT(times) for (int __i = 0; __i < times; ++__i)
#define FOR_RANGE(iter,start,end) for (int iter = start; iter <= end; ++iter)
#define FOR_ITER(iter,container,type) for (type::iterator iter = container.begin(); iter != container.end(); ++iter)
template<typename T> inline static T update_max(T &m, const T &v) { if (v > m) m = v; return m; }
template<typename T> inline static T update_min(T &m, const T &v) { if (v < m) m = v; return m; }
inline static bool isclosef(float a, float b, float eps=1e-6) { return fabs(a - b) < eps; }
inline static bool isclose(double a, double b, double eps=1e-8) { return std::abs(a - b) < eps; }

struct Range {
    double start;
    double end;
    Range(double start, double end): start(start), end(end) {}
    friend ostream& operator<< (ostream &os, const Range &r) {
        os << "[" << r.start << "," << r.end << "]";
        return os;
    }
    // sort by end
    bool operator < (const Range &r) const {
        if (isclose(this->end, r.end))
            return this->start < r.start;
        return this->end < r.end;
    }
};

int main(int argc, char *argv[]) {
    int n, d;
    int cs = 0;
    while (scanf("%d %d", &n, &d) != EOF) {
        if (n == 0 && d == 0) break;
        vector<Range> ranges;
        bool flag = true;
        FOR_RANGE(i, 1, n) {
            double x, y;
            // cin >> x >> y;
            scanf("%lf %lf", &x, &y);

            // $x \pm \sqrt{d^2-y^2}$
            // assert(d >= y);
            if (isless((double) d, y)) {
                flag = false;
            } else {
                double dx = std::sqrt(d*d - y*y);
                ranges.push_back(Range(x - dx, x + dx));
            }
        }
        if (!flag) {
            // cout << "Case " << (++cs) << ": " << -1 << endl;
            printf("Case %d: %d\n", (++cs), -1);
            continue;
        }
        assert(ranges.size() == n);
        sort(ranges.begin(), ranges.end());
#ifdef DEBUG
        FOR_ITER(it, ranges, vector<Range>) { cerr << *it << " "; } cerr << endl;
#endif
        Range *cur = NULL;
        int cnt = 0;
        FOR_ITER(it, ranges, vector<Range>) {
            if (!cur || (isgreater((it->start), (cur->end)))) {
                ++cnt;
                cur = &(*it);
            }
        }
        // cout << "Case " << (++cs) << ": " << cnt << endl;
        printf("Case %d: %d\n", (++cs), cnt);
    }
    return 0;
}
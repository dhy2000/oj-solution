#pragma GCC optimize("O2")
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
#define FOR_RANGE_EQ(iter,start,end) for (int iter = start; iter <= end; ++iter)
#define FOR_RANGE_LT(iter,start,end) for (int iter = start; iter < end; ++iter)
#define FOR_ITER(iter,container,type) for (type::iterator iter = container.begin(); iter != container.end(); ++iter)
// #define FOR_ITER_CONST(iter,container,type) for (type::const_iterator iter = container.cbegin(); iter != container.cend(); ++iter)
template<typename T> inline static T update_max(T &m, const T &v) { if (v > m) m = v; return m; }
template<typename T> inline static T update_min(T &m, const T &v) { if (v < m) m = v; return m; }
inline static bool isclosef(float a, float b, float eps=1e-6) { return fabs(a - b) < eps; }
inline static bool isclose(double a, double b, double eps=1e-8) { return std::abs(a - b) < eps; }

vector<int> pos;
vector<int> weights;

// typedef map<int, long long> kv_t;
// kv_t torques[25]; // k: torque, v: methods count

long long torques[25][15005];
#define torques_get(i,j) torques[(i)][(j) + 7502]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int c, g;
    cin >> c >> g;
    FOR_RANGE_EQ(i, 1, c) {
        int x; cin >> x;
        assert(pos.empty() || pos.at(pos.size() - 1) < x);
        pos.push_back(x);
    }
    FOR_RANGE_EQ(i, 1, g) {
        int x; cin >> x;
        assert(x > 0);
        assert(weights.empty() || weights.at(weights.size() - 1) <= x);
        weights.push_back(x);
    }
    // reverse(weights.begin(), weights.end());
    assert(pos[0] < 0 && pos[pos.size() - 1] > 0);
    torques_get(0,0) = 1;

    FOR_RANGE_LT(i, 0, g) {
        int w = weights[i];
        FOR_RANGE_LT(j, 0, c) {
            int p = pos[j];
            FOR_RANGE_EQ(t, -7500, 7500) {
                torques_get(i + 1, (t + w * p)) += torques_get(i, t);
#ifdef DEBUG
                if (torques_get(i, t) > 0) {
                    cerr << "dp[" << i + 1 << "][" << (t + w * p) << "]: " << torques_get(i + 1, (t + w * p))
                    << " += " << "dp[" << i - 1 << "][" << t << "]: " << torques_get(i, t)
                    << endl;
                }
#endif
            }
        }
    }
    cout << torques_get(g, 0) << endl;
    return 0;
}
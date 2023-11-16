#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <climits>
#include <limits>
#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <map>
#include <set>

using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::stack;
using std::queue;
using std::priority_queue;
using std::map;
using std::set;

typedef long long ll;
typedef unsigned long long ull;

#define FOR_REPEAT(times) for (int __i = 0; __i < times; ++__i)
#define FOR_RANGE_EQ(iter,start,end) for (int iter = (start); iter <= (end); ++iter)
#define FOR_RANGE_LT(iter,start,end) for (int iter = (start); iter < (end); ++iter)
#define FOR_REV_EQ(iter,start,end) for (int iter = (start); iter >= (end); --iter)
#define FOR_REV_GT(iter,start,end) for (int iter = (start); iter > (end); --iter)
#define FOR_ITER(iter,container,type) for (type::iterator iter = container.begin(); iter != container.end(); ++iter)
#define CLEAR(data) memset(&(data), 0, sizeof(data))

#ifdef DEBUG
#define debug(x) (std::cerr << "[" __FILE__ << ":" << __LINE__ << "] " << #x << " = " << x << std::endl, x)
#else
#define debug(x) x
#endif

#define panic(x) do { std::cerr << "[" __FILE__ << ":" << __LINE__ << "] " << x << std::endl; exit (1); } while (0)

#define MOD 1000000007
#define EPS 1e-6

template<typename T> inline static bool update_max(T& m, const T& v) { if (m < v) { m = v; return true; } return false; }
template<typename T> inline static bool update_min(T& m, const T& v) { if (v < m) { m = v; return true; } return false; }
template<typename T> inline static bool isequal_o(const T& m, const T& n) { return !(m < n) && !(n < m); }
inline static bool isclose_f(float a, float b, float eps = 1e-6) { return fabs(a - b) < eps; }
inline static bool isclose_d(double a, double b, double eps = 1e-8) { return fabs(a - b) < eps; }
inline static bool isdigit_c(char c) { return c >= '0' && c <= '9'; }
inline static bool islower_c(char c) { return c >= 'a' && c <= 'z'; }
inline static bool isupper_c(char c) { return c >= 'A' && c <= 'Z'; }
inline static bool isalpha_c(char c) { return islower_c(c) || isupper_c(c); }
inline static bool isalnum_c(char c) { return isalpha_c(c) || isdigit_c(c); }
inline static size_t trim_strlen(char* s) { size_t len = strlen(s); while (isspace(s[len - 1])) s[--len] = 0; return len; }
inline static ll ceil_div(ll a, ll b) { return (a / b) + !!(a % b); }
inline static ll fmamod(ll a, ll b, ll c, ll p = MOD) { return ((a * b) % p + c) % p; }
inline static ll powmod(ll a, ll b, ll p = MOD) {
    ll prod = 1, base = a;
    while (b) {
        if (b & 1)
            prod = (prod * base) % p;
        base = (base * base) % p;
        b >>= 1;
    }
    return prod;
}

inline static ll getint(FILE* __stream = stdin) {
    ll v = 0, sgn = 1;
    char c = 0;
    while (!feof(__stream)) {
        c = fgetc(__stream);
        if (isdigit_c(c) || c == '-' || c == '+')
            break;
    }
    if (feof(__stream))
        return -1;
    if (c == '-')
        sgn = -sgn;
    else if (isdigit_c(c))
        v = c - '0';
    while (!feof(__stream)) {
        c = fgetc(__stream);
        if (!isdigit_c(c)) break;
        v = (v << 3) + (v << 1) + (c - '0');
    }
    return sgn > 0 ? v : -v;
}

// Matrix Chain Multiplication

#define N 100

ll ring[N + 5], chain[N + 5];
ll dp[N + 5][N + 5];

// ll dfs(int i, int j) {
//     if (i == j)
//         return 0;
//     if (dp[i][j])
//         return dp[i][j];
    
//     FOR_RANGE_EQ(k, i + 1, j) {
//         assert(i < k && k <= j);
//         update_max(dp[i][j], dfs(i, k - 1) + dfs(k, j) + chain[i] * chain[k] * chain[j + 1]);
//     }
//     return dp[i][j];
// }

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll n = getint();
    FOR_RANGE_LT(i, 0, n) {
        ring[i] = getint();
    }
    ll ans = 0;
    // chain start position
    FOR_RANGE_LT(s, 0, n) {
        // build chain: n matrixs => (n + 1) sizes
        FOR_RANGE_LT(i, 0, n) {
            chain[i] = ring[(i + s) % n];
        }
        chain[n] = chain[0];
        // reset result
        CLEAR(dp);
        FOR_RANGE_LT(d, 1, n) { // start position
            FOR_RANGE_LT(i, 0, n - d) {
                dp[i][i] = 0;
                int j = i + d;
                assert(j < n);
                assert(dp[i][j] == 0);
                FOR_RANGE_EQ(k, i + 1, j) {
                    assert(i < k && k <= j);
                    assert(k - 1 - i < d);
                    assert(j - k < d);
                    assert(i == k - 1 || dp[i][k - 1] != 0);
                    assert(k == j || dp[k][j] != 0);
                    update_max(dp[i][j], dp[i][k - 1] + dp[k][j] + chain[i] * chain[k] * chain[j + 1]);
                }
            }
        }
        update_max(ans, dp[0][n - 1]);
    }
    printf("%lld\n", ans);
    return 0;
}
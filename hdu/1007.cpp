#pragma GCC optimize("O2")
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

// Nearest-points

#define N 500000

struct Point {
    double x, y;
    Point(): x(0.0), y(0.0) {}
    Point(double x, double y): x(x), y(y) {}
    double dist(const Point &p) const {
        return ((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
};

bool cmp_x(const Point &p1, const Point &p2) {
    if (isclose_d(p1.x, p2.x))
        return p1.y < p2.y;
    return p1.x < p2.x;
}

bool cmp_y(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

double nearest_points(const Point *pts, int left, int right) {
    // printf("(%d, %d)\n", left, right);
    if (right - left <= 2) {
        double min_dist = pts[left].dist(pts[right]);
        FOR_RANGE_EQ(i, left, right) FOR_RANGE_EQ(j, i + 1, right) {
            update_min(min_dist, pts[i].dist(pts[j]));
        }
        return min_dist;
    }
    int mid = (left + right) >> 1; // [left, mid], [mid + 1, right]
    assert(mid - left + 1 >= 2 && right - mid >= 2);
    double x_mid = pts[mid].x;
    double h1 = nearest_points(pts, left, mid), h2 = nearest_points(pts, mid + 1, right);
    double h = h1 < h2 ? h1 : h2;
    int l = mid, r = mid; // subset B: [l, r]: |x_p - x_mid| <= h
    while (l > left && dpow(x_mid - pts[l - 1].x, 2) <= h) --l;
    while (r < right && dpow(pts[r + 1].x - x_mid, 2) <= h) ++r;
    
    static Point setb[N + 5];
    int sizb = r - l + 1;
    memcpy(setb, pts + l, sizb * sizeof(Point));
    std::sort(setb, setb + sizb, cmp_y);

    double min_dist = h;
    FOR_RANGE_LT(i, 0, sizb) FOR_RANGE_LT(j, i + 1, sizb) {
        if (dpow(setb[j].y - setb[i].y, 2) >= min_dist)
            break;
        update_min(min_dist, setb[i].dist(setb[j]));
    }
    return min_dist;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        static Point pts[N + 5];
        FOR_RANGE_LT(i, 0, n) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            pts[i].x = x; pts[i].y = y;
        }
        std::sort(pts, pts + n, cmp_x);
        double min_dist = nearest_points(pts, 0, n - 1);
        // printf("%.4f\n", sqrt(min_dist));
        printf("%.2f\n", sqrt(min_dist) / 2);
    }

    return 0;
}
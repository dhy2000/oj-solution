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

struct Area {
    ll length, width;
    Area(ll length, ll width): length(length), width(width) {
        set_size(length, width);
    }
    void set_size(ll length, ll width) {
#ifdef DEBUG
        assert(length > 0 && width > 0);
#endif
        if (length < width) {
            ll t = length; length = width; width = t;
        }
        this->length = length; this->width = width;
    }
    bool contains(const Area &b) const {
        return b.length < length && b.width < width;
    }
    bool operator < (const Area &b) const {
        if (length == b.length)
            return width < b.width;
        return length < b.length;
    }
    string to_string() const {
        std::stringstream ss;
        ss << "[" << length << " x " << width << "]";
        return ss.str();
    }
};

typedef map<Area, ll> TopHeight;
typedef map<Area, TopHeight> BottomTopHeight;

BottomTopHeight solved;

void update_height(BottomTopHeight& mp, const Area& bottom, const Area& top, ll height) {
    if (mp.count(bottom)) {
        if (mp[bottom].count(top))
            update_max(mp[bottom][top], height);
        else
            mp[bottom][top] = height;
    }
    else {
        mp[bottom] = TopHeight();
        mp[bottom][top] = height;
    }
}

void print_map(BottomTopHeight& mp, string name = "solved", FILE* fp = stderr) {
    fprintf(fp, "%s:", name.c_str());
    FOR_ITER(itb, mp, BottomTopHeight)
        FOR_ITER(itt, itb->second, TopHeight) {
            fprintf(fp, " %s->%s=%lld", itb->first.to_string().c_str(), itt->first.to_string().c_str(), itt->second);
        }
    fprintf(fp, "\n");
}

void solve(const Area &area, ll height) {
    BottomTopHeight inc;
    // Append to top or bottom
    FOR_ITER(itb, solved, BottomTopHeight)
        FOR_ITER(itt, itb->second, TopHeight) {
            if (itt->first.contains(area))
                update_height(inc, itb->first, area, itt->second + height);
            if (area.contains(itb->first))
                update_height(inc, area, itt->first, itt->second + height);
        }
    // Add itself
    update_height(inc, area, area, height);
    // Merge into solved
    FOR_ITER(itb, inc, BottomTopHeight)
        FOR_ITER(itt, itb->second, TopHeight) {
            update_height(solved, itb->first, itt->first, itt->second);
        }
    BottomTopHeight comb;
    // Combine increased and solved
    FOR_ITER(itb, inc, BottomTopHeight)
        FOR_ITER(itt, itb->second, TopHeight) {
            FOR_ITER(itbs, solved, BottomTopHeight) {
                if (itt->first.contains(itbs->first)) {
                    FOR_ITER(itts, itbs->second, TopHeight) {
                        update_height(comb, itb->first, itts->first, itt->second + itts->second);
                    }
                }
            }
        }
    // Merge into solved
    FOR_ITER(itb, comb, BottomTopHeight)
        FOR_ITER(itt, itb->second, TopHeight) {
            update_height(solved, itb->first, itt->first, itt->second);
        }
#ifdef DEBUG
    print_map(inc, "inc");
    print_map(comb, "comb");
    print_map(solved, "solved");
#endif
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, T = 0;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        solved.clear();
        FOR_RANGE_LT(i, 0, n) {
            ll x = getint(), y = getint(), z = getint();
            solve(Area(x, y), z);
            solve(Area(y, z), x);
            solve(Area(z, x), y);
        }
        ll ans = 0;
        FOR_ITER(itb, solved, BottomTopHeight)
            FOR_ITER(itt, itb->second, TopHeight) {
                update_max(ans, itt->second);
            }

        printf("Case %d: maximum height = %lld\n", ++T, ans);
    }
    return 0;
}
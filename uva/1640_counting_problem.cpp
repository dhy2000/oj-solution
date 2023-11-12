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

struct Digits {
    ll count[10]; // 0-9
    Digits(ll n = 0): count() {
        FOR_RANGE_LT(i, 0, 10)
            count[i] = n;
    }

    Digits operator + (const Digits &b) const {
        Digits s;
        FOR_RANGE_LT(i, 0, 10)
            s.count[i] = this->count[i] + b.count[i];
        return s;
    }

    Digits operator - (const Digits &b) const {
        Digits s;
        FOR_RANGE_LT(i, 0, 10)
            s.count[i] = this->count[i] - b.count[i];
        return s;
    }

    Digits operator * (const ll &b) const {
        Digits s;
        FOR_RANGE_LT(i, 0, 10)
            s.count[i] = this->count[i] * b;
        return s;
    }

    bool operator == (const Digits &b) const {
        FOR_RANGE_LT(i, 0, 10)
            if (this->count[i] != b.count[i])
                return false;
        return true;
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << count[0];
        FOR_RANGE_LT(i, 1, 10)
            ss << " " << count[i];
        return ss.str();
    }
};

inline static ll digits_per_round(ll pwr) {
    if (pwr == 0)
        return 0;
    // 0-9: 1; 00-99: 20; 000-999: 300, 0000-9999: 4000
    return pwr * powmod(10, pwr - 1, LLONG_MAX);
}

Digits num_to_digits(ll n) {
    Digits s;
    while (n) {
        s.count[n % 10]++;
        n /= 10;
    }
    return s;
}

Digits count_n(ll n) {
    // 1 + ... + (n - 1)
    Digits total;
    ll base, pwr;
    for (base = 1, pwr = 0; base <= n; base *= 10, ++pwr) {
        ll prefix = n / (base * 10);
        ll curbit = (n / base) % 10;
        assert(0 <= curbit && curbit <= 9);
        Digits d_prefix = num_to_digits(prefix);
        Digits d_curbit(0);
        FOR_RANGE_LT(b, 0, curbit) {
            d_curbit.count[b] = 1;
        }
        Digits d_base(digits_per_round(pwr));
        Digits part = (d_prefix * (curbit * base)) + d_curbit * base + d_base * curbit;
        total = total + part;
    }
    // eliminate prefix-zero
    ll nzero = 0;
    FOR_RANGE_LT(i, 0, pwr) {
        nzero += powmod(10, i, LLONG_MAX);
    }
    Digits d_zero;
    d_zero.count[0] = nzero;
    return total - d_zero;
}

// #define DEBUG

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

#ifdef DEBUG
    FOR_RANGE_LT(i, 1, 10000) {
        Digits d = count_n(i);
        printf("%d: %s\n", i, d.to_string().c_str());
        if (i > 1)
            assert(d == count_n(i - 1) + num_to_digits(i - 1));
    }
#else

    while (1) {
        ll a = getint(), b = getint();
        if (!a && !b) break;
        if (a > b) { ll t = a; a = b; b = t; }
        Digits s1 = count_n(a), s2 = count_n(b + 1);
        Digits s = s2 - s1;
        puts(s.to_string().c_str());
    }

#endif

    return 0;
}
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

/*
    n hyperplanes divide m-dimensional space:
    $$
    \sum_{i=0}^{\min (n, m)} C_{n}^{i}
    $$
*/

inline static ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a < b) { ll t = a; a = b; b = t; }
    assert(a != 0 || b != 0);
    while (b) {
        // (a, b) -> (b, a % b)
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}

struct Fractional {
    ll p, q; // "p/q"

    Fractional(): p(0), q(1) {}
    Fractional(ll a): p(a), q(1) {}
    Fractional(ll a, ll b): p(a), q(b) { assert(b != 0); simplify(); assert(q >= 1); }

    void simplify() {
        ll g = gcd(p, q);
        p /= g, q /= g;
        if (q < 0) p = -p, q = -q;
    }

    Fractional operator + (const Fractional &b) const {
        ll nq = q / gcd(q, b.q) * b.q;
        ll np = p * (nq / q) + b.p * (nq / b.q);
        return Fractional(np, nq);
    }

    Fractional operator - (const Fractional &b) const {
        return (*this) + Fractional(-b.p, b.q);
    }

    Fractional operator + () const {
        return *this;
    }

    Fractional operator - () const {
        return Fractional(-p, q);
    }

    Fractional operator * (const Fractional &b) const {
        Fractional f1(p, b.q), f2(b.p, q);
        return Fractional(f1.p * f2.p, f1.q * f2.q);
    }

    Fractional operator / (const Fractional &b) const {
        assert(b.q != 0);
        return (*this) / Fractional(b.q, b.p);
    }

    bool operator < (const Fractional &b) const {
        return ((*this) - b).p < 0;
    }

    bool operator > (const Fractional &b) const {
        return b < (*this);
    }

    bool operator == (const Fractional &b) const {
        return !((*this) < b) && !(b < (*this));
    }

    bool operator != (const Fractional &b) const {
        return !((*this) == b);
    }

    bool operator >= (const Fractional &b) const {
        return !((*this) < b);
    }

    bool operator <= (const Fractional &b) const {
        return !(b < (*this));
    }

    bool is_integer() const {
        return q == 1;
    }

    Fractional absolute() const {
        return Fractional(abs(p), q);
    }

    ll sign() const {
        if (p == 0) return 0;
        return p < 0 ? -1 : 1;
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << p;
        // if (!is_integer()) 
        ss << "/" << q;
        return ss.str();
    }

    Fractional find_abs_larger() const {
        const ll r = 10;
        Fractional f(this->absolute());
        return Fractional(f.p * r + 1, f.q) * sign();
    }

    Fractional find_abs_smaller() const {
        if ((*this) == 0) return *this;
        const ll r = 10;
        Fractional f(this->absolute());
        return Fractional(f.p * r - 1, f.q) * sign();
    }
};

#define N 18

// coeff of n's item
void rprod(set<int> *used, int depth, ll n, ll start, ll prod, ll *sum) {
    if (depth == 0) {
        *sum += prod;
        return;
    }
    
    FOR_RANGE_EQ(i, start, n - 1) {
        if (used->count(i))
            continue;
        used->insert(i);
        rprod(used, depth - 1, n, i + 1, prod * (-i), sum);
        used->erase(i);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    static Fractional coeff[N + 5];
    int n = getint();
    printf("%d\n", n);
    FOR_RANGE_EQ(i, 0, n) {
        coeff[i] = 0;
    }
    coeff[0] = 1;

    ll prod = 1;

    FOR_RANGE_EQ(i, 1, n) { // i-th comb
        prod *= i;
        FOR_RANGE_EQ(j, 0, i) { // j's item
            set<int> used;
            ll sum = 0;
            rprod(&used, i - j, i, 0, 1, &sum);
            coeff[j] = coeff[j] + Fractional(sum, prod);
        }
    }

    FOR_REV_EQ(i, n, 0) {
        printf("%s", coeff[i].to_string().c_str());
        if (i > 0) printf(" ");
    }
    printf("\n");
    return 0;
}
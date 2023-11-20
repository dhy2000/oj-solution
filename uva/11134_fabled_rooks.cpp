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

#define N 50000

struct Rook {
    int id;
    int row_l, row_r;
    int col_l, col_r;
    int rpos, cpos;
};

bool cmp_row(const Rook& r1, const Rook& r2) {
    if (r1.row_r == r2.row_r)
        return (r1.row_r - r1.row_l) < (r2.row_r - r2.row_l);
    return r1.row_r < r2.row_r;
}

bool cmp_col(const Rook& r1, const Rook& r2) {
    if (r1.col_r == r2.col_r)
        return (r1.col_r - r1.col_l) < (r2.col_r - r2.col_l);
    return r1.col_r < r2.col_r;
}

bool cmp_id(const Rook& r1, const Rook& r2) {
    return r1.id < r2.id;
}

int main(int argc, const char* argv[], const char* envp[]) {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    while (1) {
        int n = getint();
        if (n == 0)
            break;
        static Rook rooks[N];
        FOR_RANGE_LT(i, 0, n) {
            rooks[i].id = i + 1;
            rooks[i].row_l = getint();
            rooks[i].col_l = getint();
            rooks[i].row_r = getint();
            rooks[i].col_r = getint();
        }
        static bool rows[N], cols[N];
        CLEAR(rows);
        CLEAR(cols);
        std::sort(rooks, rooks + n, cmp_row);
        bool avai = true;
        FOR_RANGE_LT(i, 0, n) {
            bool placed = false;
            FOR_RANGE_EQ(r, rooks[i].row_l, rooks[i].row_r) {
                if (!rows[r]) {
                    rows[r] = true;
                    rooks[i].rpos = r;
                    placed = true;
                    break;
                }
            }
            if (!placed) {
                avai = false;
                break;
            }
        }
        std::sort(rooks, rooks + n, cmp_col);
        FOR_RANGE_LT(i, 0, n) {
            bool placed = false;
            FOR_RANGE_EQ(c, rooks[i].col_l, rooks[i].col_r) {
                if (!cols[c]) {
                    cols[c] = true;
                    rooks[i].cpos = c;
                    placed = true;
                    break;
                }
            }
            if (!placed) {
                avai = false;
                break;
            }
        }
        
        if (!avai) {
            printf("IMPOSSIBLE\n");
        } else {
            std::sort(rooks, rooks + n, cmp_id);
            FOR_RANGE_LT(i, 0, n) {
                printf("%d %d\n", rooks[i].rpos, rooks[i].cpos);
            }
        }

    }
    return 0;
}
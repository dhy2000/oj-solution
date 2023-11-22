/* includes */
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

/* use stds */
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

/* typedefs */
typedef char i8;
typedef unsigned char u8, byte, boolean;
typedef int i32;
typedef unsigned int u32;
typedef long long i64, ll;
typedef unsigned long long u64, ull;
typedef float f32;
typedef double f64;

typedef i32 data_t;

/* function-like macros */
#define FOR_REPEAT(times) for (int __i = 0; __i < times; ++__i)
#define FOR_RANGE_EQ(iter,start,end) for (int iter = (start); iter <= (end); ++iter)
#define FOR_RANGE_LT(iter,start,end) for (int iter = (start); iter < (end); ++iter)
#define FOR_REV_EQ(iter,start,end) for (int iter = (start); iter >= (end); --iter)
#define FOR_REV_GT(iter,start,end) for (int iter = (start); iter > (end); --iter)
#define FOR_ITER(iter,container,type) for (type::iterator iter = container.begin(); iter != container.end(); ++iter)
#define CLEAR(data) memset(&(data), 0, sizeof(data))
#define WRAP(i,n) (((i)+(n))%(n))

/* value macros */
#define MOD 1000000007
#define EPS 1e-6
#define MAXN 1000

/* pre-defined functions */
template<typename T> inline static bool update_max(T& m, const T& v) { if (m < v) { m = v; return true; } return false; }
template<typename T> inline static bool update_min(T& m, const T& v) { if (v < m) { m = v; return true; } return false; }
template<typename T> inline static bool isequal_o(const T& m, const T& n) { return !(m < n) && !(n < m); }
inline static bool isdigit_c(char c) { return c >= '0' && c <= '9'; }

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

/* Binary Indexed Tree */

inline static ll lowbit(ll x) { return x & (-x); }

namespace BIT {

inline static data_t _add(data_t x, data_t y) { return (x + y) % MOD; }

inline static void add(data_t* a, size_t len, size_t index, data_t val) {
    // assert(0 <= index && index < len);
    index += 1;
    while (index <= len) {
        a[index] = _add(a[index], val);
        index += lowbit(index);
    }
}

inline static int query(const data_t* a, size_t len, size_t index) {
    // assert(0 <= index && index < len);
    data_t result = 0;
    index += 1;
    while (index > 0) {
        result = _add(result, a[index]);
        index -= lowbit(index);
    }
    return result;
}

inline static int range(const data_t* a, size_t len, size_t left, size_t right) {
    data_t r = query(a, len, right), l = (left == 0) ? 0 : query(a, len, left - 1);
    return WRAP((r - l) % MOD, MOD);
}

}

/* Discretize */
struct Elem {
    data_t val;
    size_t index;
};

bool cmp_val(const Elem& a, const Elem& b) {
    if (a.val == b.val)
        return a.index < b.index;
    return a.val < b.val;
}

bool cmp_index(const Elem& a, const Elem& b) {
    return a.index < b.index;
}

void discretize(data_t* data, size_t len) {
    static Elem elem[MAXN + 1];
    FOR_RANGE_LT(i, 0, len) {
        elem[i].val = data[i];
        elem[i].index = i;
    }
    std::sort(elem, elem + len, cmp_val);
    data_t last_val = 0;
    size_t last_index = 0;
    FOR_RANGE_LT(i, 0, len) {
        if (i == 0 || elem[i].val != last_val) {
            last_index = i;
            last_val = elem[i].val;
        }
        elem[i].val = last_index;
    }
    std::sort(elem, elem + len, cmp_index);
    FOR_RANGE_LT(i, 0, len)
        data[i] = elem[i].val;
}

int main(int argc, const char* argv[]) {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T = getint();
    FOR_RANGE_EQ(Ti, 1, T) {
        int n = getint(), m = getint();
        static data_t data[MAXN + 1];
        FOR_RANGE_LT(i, 0, n) {
            data[i] = getint();
        }
        discretize(data, n);
        static data_t bit[MAXN + 1][MAXN + 1];
        CLEAR(bit);

        data_t ans = 0;
        if (m == 1)
            ans = n;
        else {
            FOR_RANGE_LT(i, 0, n) {
                BIT::add(bit[0], n, data[i], 1);
                FOR_RANGE_EQ(j, 2, m) {
                    data_t k = 0;
                    k = (data[i] == 0) ? 0 : BIT::query(bit[j - 2], n, data[i] - 1);
                    BIT::add(bit[j - 1], n, data[i], k);
                    if (j == m)
                        ans = (ans + k) % MOD;
                }
            }
        }
        printf("Case #%d: %d\n", Ti, (int) ans);
    }
    return 0;
}
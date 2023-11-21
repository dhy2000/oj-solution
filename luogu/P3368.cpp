/* includes */
#include <algorithm>
#include <functional>
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

/* function-like macros */
#define FOR_REPEAT(times) for (int __i = 0; __i < times; ++__i)
#define FOR_RANGE_EQ(iter,start,end) for (int iter = (start); iter <= (end); ++iter)
#define FOR_RANGE_LT(iter,start,end) for (int iter = (start); iter < (end); ++iter)
#define FOR_REV_EQ(iter,start,end) for (int iter = (start); iter >= (end); --iter)
#define FOR_REV_GT(iter,start,end) for (int iter = (start); iter > (end); --iter)
#define FOR_ITER(iter,container,type) for (type::iterator iter = container.begin(); iter != container.end(); ++iter)
#define CLEAR(data) memset(&(data), 0, sizeof(data))
#define WRAP(i,n) ((((i)%(n))+(n))%(n))

/* value macros */
#define MOD 1000000007
#define EPS 1e-6
#define MAXN 1000000

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

struct BinaryIndexedTree {
#define BIT_OP(x,y) ((x)+(y))
#define BIT_I 0
    const size_t len;
    ll vals[MAXN + 1];   // starts from 1

    BinaryIndexedTree(size_t n): len(n) {
        CLEAR(vals);
        FOR_RANGE_LT(i, 0, len) {
            update(i, BIT_I);
        }
    }

    // sum[0..=index]
    ll query(size_t index) {
        assert(0 <= index && index < len);
        ll result = BIT_I;
        index += 1;
        while (index > 0) {
            result = BIT_OP(result, vals[index]);
            index -= lowbit(index);
        }
        return result;
    }

    void update(size_t index, ll val) {
        assert(0 <= index && index < len);
        index += 1;
        while (index <= len) {
            vals[index] = BIT_OP(vals[index], val);
            index += lowbit(index);
        }
    }

    // sum[l..=r]
    ll range(size_t l, size_t r) {
        ll right = query(r);
        ll left = l == 0 ? 0 : query(l - 1);
        return right - left;
    }
#undef BIT_OP
#undef BIT_I
};

int main(int argc, const char* argv[]) {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m;
    while (scanf("%d %d", &n, &m) > 0) {
        BinaryIndexedTree bit(n);
        int last = 0;
        FOR_RANGE_LT(i, 0, n) {
            int x = getint();
            bit.update(i, x - last);
            last = x;
        }
        FOR_RANGE_LT(i, 0, m) {
            int op = getint();
            if (op == 1) {
                int x = getint(), y = getint(), k = getint();
                bit.update(x - 1, k);
                if (y < n)
                    bit.update(y, -k);
            } else {
                int x = getint();
                printf("%lld\n", bit.query(x - 1));
            }
        }
    }

    return 0;
}
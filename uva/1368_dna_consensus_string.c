// My C99 Template
/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include <limits.h>

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
#define FOR_RANGE_EQ(iter,start,end) for (int iter = (start); iter <= (end); ++iter)
#define FOR_RANGE_LT(iter,start,end) for (int iter = (start); iter < (end); ++iter)
#define FOR_REV_EQ(iter,start,end) for (int iter = (start); iter >= (end); --iter)
#define FOR_REV_GT(iter,start,end) for (int iter = (start); iter > (end); --iter)
#define CLEAR(data) memset(&(data), 0, sizeof(data))

#ifdef DEBUG
#define debugf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define debugf(...) __VA_ARGS__
#endif // DEBUG

/* value macros */
#define MOD 1000000007
#define EPS 1e-6

/* pre-defined functions */
inline static void swap_i32(i32* a, i32* b) { i32 t = *a; *a = *b; *b = t; }
inline static void swap_i64(i64* a, i64* b) { i64 t = *a; *a = *b; *b = t; }
inline static int cmp_i32(i32 a, i32 b) { if (a == b) return 0; return a < b ? -1 : 1; }
inline static int cmp_i64(i64 a, i64 b) { if (a == b) return 0; return a < b ? -1 : 1; }
inline static int cmp_then(int first, int second) { if (0 == first) return second; return first; }
inline static boolean update_max_i32(i32* m, const i32 v) { if (*m < v) { *m = v; return 1; } return 0; }
inline static boolean update_min_i32(i32* m, const i32 v) { if (*m < v) { *m = v; return 1; } return 0; }
inline static boolean update_max_i64(i64* m, const i64 v) { if (*m < v) { *m = v; return 1; } return 0; }
inline static boolean update_min_i64(i64* m, const i64 v) { if (*m < v) { *m = v; return 1; } return 0; }
inline static boolean isclose_f64(double a, double b, double eps) { return fabs(a - b) < eps; }
inline static size_t trim_strlen(char* s) { size_t len = strlen(s); while (isspace(s[len - 1])) s[--len] = 0; return len; }
inline static ll ceil_div(ll a, ll b) { return (a / b) + !!(a % b); }
inline static ll fmamod(ll a, ll b, ll c, ll p) { return ((a * b) % p + c) % p; }
inline static ll powmod(ll a, ll b, ll p) {
    ll prod = 1, base = a;
    while (b) {
        if (b & 1)
            prod = (prod * base) % p;
        base = (base * base) % p;
        b >>= 1;
    }
    return prod;
}
inline static ll getint(FILE* __stream) {
    ll v = 0, sgn = 1;
    char c = 0;
    while (!feof(__stream)) {
        c = fgetc(__stream);
        if (isdigit(c) || c == '-' || c == '+')
            break;
    }
    if (feof(__stream))
        return -1;
    if (c == '-')
        sgn = -sgn;
    else if (isdigit(c))
        v = c - '0';
    while (!feof(__stream)) {
        c = fgetc(__stream);
        if (!isdigit(c)) break;
        v = (v << 3) + (v << 1) + (c - '0');
    }
    return sgn > 0 ? v : -v;
}

/* struct qsort */
struct Pair {
    ll x, y;
};

int cmp(const void *_pa, const void *_pb) {
    const struct Pair *pa = (const struct Pair*)_pa, *pb = (const struct Pair*)_pb;
    return cmp_then(cmp_i64(pa->x, pb->x), cmp_i64(pa->y, pb->y));
}

#define MAXN 100000

int main(int argc, const char* const argv[]) {
    int T = getint(stdin);
    while (T--) {
        int num = getint(stdin), length = getint(stdin);
        static char dna[MAXN + 5];
        static int count[MAXN][26];
        CLEAR(count);
        FOR_RANGE_LT(n, 0, num) {
            scanf("%s", dna);
            assert(trim_strlen(dna) == length);
            FOR_RANGE_LT(i, 0, length) {
                count[i][dna[i] - 'A']++;
            }
        }
        static int max_count[MAXN];
        CLEAR(max_count);
        FOR_RANGE_LT(i, 0, length) {
            FOR_RANGE_LT(j, 0, 26) {
                if (update_max_i32(&max_count[i], count[i][j])) {
                    dna[i] = j + 'A';
                }
            }
        }
        dna[length] = 0;
        int total_errors = 0;
        FOR_RANGE_LT(i, 0, length) {
            FOR_RANGE_LT(j, 0, 26) {
                if (j == dna[i] - 'A')
                    continue;
                total_errors += count[i][j];
            }
        }
        printf("%s\n%d\n", dna, total_errors);
    }
    return 0;
}
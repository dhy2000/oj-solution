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

// 16x16 Sudoku
/*
 * POJ 3076 http://poj.org/problem?id=3076
 * UVa 1309 https://www.udebug.com/UVa/1309
 * SPOJ SUDOKU https://www.spoj.com/problems/SUDOKU/
 */

#define N (4)
#define L ((N)*(N))

char sudoku[L + 6][L + 6];
int mask[L + 6][L + 6];
bool solved;

inline static int popcnt(int n) {
    int cnt = 0;
    FOR_RANGE_LT(i, 0, 8 * sizeof(n))
        if (n & (1 << i))
            cnt++;
    return cnt;
}
inline static int lowidx(int n) {
    FOR_RANGE_LT(i, 0, 8 * sizeof(n))
        if (n & (1 << i))
            return i;
    return -1;
}

void print_sudoku(FILE* const fp = stderr) {
    FOR_RANGE_LT(i, 0, L)
        fprintf(fp, "%s\n", sudoku[i]);
}
void print_status(FILE* const fp = stderr) {
    FOR_RANGE_LT(i, 0, L) {
        FOR_RANGE_LT(j, 0, L) {
            if (sudoku[i][j] == '-') {
                fputc('[', fp);
                FOR_RANGE_LT(k, 0, L) {
                    if (mask[i][j] & (1 << k))
                        fputc('A' + k, fp);
                    else
                        fputc('-', fp);
                }
                fputc(']', fp);
                fprintf(fp, "(%2d)", popcnt(mask[i][j]));
            }
            else {
                fputc('<', fp);
                FOR_RANGE_LT(k, 0, L) {
                    if (sudoku[i][j] == 'A' + k)
                        fputc('A' + k, fp);
                    else
                        fputc(' ', fp);
                }
                fputc('>', fp);
                fprintf(fp, "(  )");
            }

            fputc(' ', fp);
        }
        fputc('\n', fp);
    }
}

bool fill_one(int pi, int pj, char c, int kind = 0) {
    int a = c - 'A', b = 1 << a;
    if (sudoku[pi][pj] != '-' || !(mask[pi][pj] & b))
        return false;
    sudoku[pi][pj] = c;
    mask[pi][pj] = 0;
#ifdef DEBUG
    fprintf(stderr, "[Fill %d] %c->(%2d, %2d)\n", kind, c, pi, pj);
#endif
    // Line
    FOR_RANGE_LT(i, 0, L) {
        if (i == pi)
            continue;
        if (sudoku[i][pj] == '-' && (mask[i][pj] & b))
            mask[i][pj] &= (~b);
    }
    // Column
    FOR_RANGE_LT(j, 0, L) {
        if (j == pj)
            continue;
        if (sudoku[pi][j] == '-' && (mask[pi][j] & b))
            mask[pi][j] &= (~b);
    }
    // Cell
    int cell_i = pi / N, cell_j = pj / N;
    FOR_RANGE_LT(di, 0, N) FOR_RANGE_LT(dj, 0, N) {
        int i = cell_i * N + di, j = cell_j * N + dj;
        if (i == pi && j == pj)
            continue;
        if (sudoku[i][j] == '-' && (mask[i][j] & b))
            mask[i][j] &= (~b);
    }
    return true;
}

struct Fill {
    int i, j;
    char c;
};

int fill_certain() {
    // return -1 if error
    int cntfill = 0;
    while (1) {
        bool hasfill = false;
        // A position has only one available alphabet.
        bool hasempty = false;
        FOR_RANGE_LT(i, 0, L) FOR_RANGE_LT(j, 0, L) {
            if (sudoku[i][j] != '-') continue;
            int pcnt = popcnt(mask[i][j]);
            hasempty = true;
            if (pcnt == 0) return -1; // unsolvable status
            if (pcnt == 1) {
                assert(fill_one(i, j, lowidx(mask[i][j]) + 'A', 1));
                hasfill = true; cntfill++;
            }
        }
        if (!hasempty) {
            solved = true;
            return cntfill;
        }
        // A row/column/cell has an alphabet with only one available position.
        static bool alpha_vis[L];
        static int alpha_cnt[L];    // available positions of each alpha
        static Fill alpha_avai[L][L];
        // Row
        FOR_RANGE_LT(i, 0, L) {
            CLEAR(alpha_vis); CLEAR(alpha_cnt); CLEAR(alpha_avai);
            FOR_RANGE_LT(j, 0, L) {
                if (sudoku[i][j] != '-')
                    alpha_vis[sudoku[i][j] - 'A'] = true;
                else {
                    FOR_RANGE_LT(a, 0, L) {
                        int b = 1 << a;
                        if (mask[i][j] & b) {
                            alpha_avai[a][alpha_cnt[a]].i = i;
                            alpha_avai[a][alpha_cnt[a]].j = j;
                            ++alpha_cnt[a];
                        }
                    }
                }
            }
            FOR_RANGE_LT(a, 0, L) {
                char c = a + 'A';
                if (alpha_vis[a]) {
                    assert(!alpha_cnt[a]);
                    continue;
                }
                if (alpha_cnt[a] == 0) return -1; // no place for a
                if (alpha_cnt[a] == 1) {
                    if (!fill_one(alpha_avai[a][0].i, alpha_avai[a][0].j, c, 2)) return -1; // conflict
                    hasfill = true; cntfill++;
                }
            }
        }
        // Column
        FOR_RANGE_LT(j, 0, L) {
            CLEAR(alpha_vis); CLEAR(alpha_cnt); CLEAR(alpha_avai);
            FOR_RANGE_LT(i, 0, L) {
                if (sudoku[i][j] != '-')
                    alpha_vis[sudoku[i][j] - 'A'] = true;
                else {
                    FOR_RANGE_LT(a, 0, L) {
                        int b = 1 << a;
                        if (mask[i][j] & b) {
                            alpha_avai[a][alpha_cnt[a]].i = i;
                            alpha_avai[a][alpha_cnt[a]].j = j;
                            ++alpha_cnt[a];
                        }
                    }
                }
            }
            FOR_RANGE_LT(a, 0, L) {
                char c = a + 'A';
                if (alpha_vis[a]) {
                    assert(!alpha_cnt[a]);
                    continue;
                }
                if (alpha_cnt[a] == 0) return -1;
                if (alpha_cnt[a] == 1) {
                    if (!fill_one(alpha_avai[a][0].i, alpha_avai[a][0].j, c, 3)) return -1;
                    hasfill = true; cntfill++;
                }
            }
        }
        // Cell
        FOR_RANGE_LT(cell_i, 0, N) FOR_RANGE_LT(cell_j, 0, N) {
            CLEAR(alpha_vis); CLEAR(alpha_cnt); CLEAR(alpha_avai);
            FOR_RANGE_LT(di, 0, N) FOR_RANGE_LT(dj, 0, N) {
                int i = cell_i * N + di, j = cell_j * N + dj;
                if (sudoku[i][j] != '-')
                    alpha_vis[sudoku[i][j] - 'A'] = true;
                else {
                    FOR_RANGE_LT(a, 0, L) {
                        int b = 1 << a;
                        if (mask[i][j] & b) {
                            alpha_avai[a][alpha_cnt[a]].i = i;
                            alpha_avai[a][alpha_cnt[a]].j = j;
                            ++alpha_cnt[a];
                        }
                    }
                }
            }
            FOR_RANGE_LT(a, 0, L) {
                char c = a + 'A';
                if (alpha_vis[a]) {
                    assert(!alpha_cnt[a]);
                    continue;
                }
                if (alpha_cnt[a] == 0) return -1;
                if (alpha_cnt[a] == 1) {
                    if (!fill_one(alpha_avai[a][0].i, alpha_avai[a][0].j, c, 4)) return -1;
                    hasfill = true; cntfill++;
                }
            }
        }
        if (!hasfill) break;
    }
    return cntfill;
}

void least_available_choices(Fill* choices, int* p_num_choices) {
    assert((void*)choices && (void*)p_num_choices);
    // Position with the least available alphabets.
    int min_popcnt = INT_MAX;
    int pos_i, pos_j;
    FOR_RANGE_LT(i, 0, L) FOR_RANGE_LT(j, 0, L) {
        if (sudoku[i][j] != '-')
            continue;
        int pcnt = popcnt(mask[i][j]);
        assert(pcnt >= 2);
        if (update_min(min_popcnt, pcnt))
            pos_i = i, pos_j = j;
    }
    int num_choices = 0;
    FOR_RANGE_LT(a, 0, L) {
        int b = 1 << a;
        if (!(mask[pos_i][pos_j] & b))
            continue;
        choices[num_choices].i = pos_i;
        choices[num_choices].j = pos_j;
        choices[num_choices].c = a + 'A';
        ++num_choices;
    }
    assert(num_choices == min_popcnt);

    // Alphabets with the least available positions in a scope
    static bool alpha_vis[L];
    static int alpha_cnt[L];    // available positions of each alpha
    static Fill alpha_avai[L][L];
    // Row
    FOR_RANGE_LT(i, 0, L) {
        CLEAR(alpha_vis); CLEAR(alpha_cnt); CLEAR(alpha_avai);
        FOR_RANGE_LT(j, 0, L) {
            if (sudoku[i][j] != '-')
                alpha_vis[sudoku[i][j] - 'A'] = true;
            else {
                FOR_RANGE_LT(a, 0, L) {
                    int b = 1 << a; char c = a + 'A';
                    if (mask[i][j] & b) {
                        alpha_avai[a][alpha_cnt[a]].i = i;
                        alpha_avai[a][alpha_cnt[a]].j = j;
                        alpha_avai[a][alpha_cnt[a]].c = c;
                        ++alpha_cnt[a];
                    }
                }
            }
        }
        FOR_RANGE_LT(a, 0, L) {
            if (alpha_vis[a]) {
                assert(!alpha_cnt[a]);
                continue;
            }
            assert(alpha_cnt[a] >= 2);
            if (update_min(num_choices, alpha_cnt[a])) {
                memcpy(choices, alpha_avai[a], alpha_cnt[a] * sizeof(Fill));
            }
        }
    }
    // Column
    FOR_RANGE_LT(j, 0, L) {
        CLEAR(alpha_vis); CLEAR(alpha_cnt); CLEAR(alpha_avai);
        FOR_RANGE_LT(i, 0, L) {
            if (sudoku[i][j] != '-')
                alpha_vis[sudoku[i][j] - 'A'] = true;
            else {
                FOR_RANGE_LT(a, 0, L) {
                    int b = 1 << a; char c = a + 'A';
                    if (mask[i][j] & b) {
                        alpha_avai[a][alpha_cnt[a]].i = i;
                        alpha_avai[a][alpha_cnt[a]].j = j;
                        alpha_avai[a][alpha_cnt[a]].c = c;
                        ++alpha_cnt[a];
                    }
                }
            }
        }
        FOR_RANGE_LT(a, 0, L) {
            if (alpha_vis[a]) {
                assert(!alpha_cnt[a]);
                continue;
            }
            assert(alpha_cnt[a] >= 2);
            if (update_min(num_choices, alpha_cnt[a])) {
                memcpy(choices, alpha_avai[a], alpha_cnt[a] * sizeof(Fill));
            }
        }
    }
    // Cell
    FOR_RANGE_LT(cell_i, 0, N) FOR_RANGE_LT(cell_j, 0, N) {
        CLEAR(alpha_vis); CLEAR(alpha_cnt); CLEAR(alpha_avai);
        FOR_RANGE_LT(di, 0, N) FOR_RANGE_LT(dj, 0, N) {
            int i = cell_i * N + di, j = cell_j * N + dj;
            if (sudoku[i][j] != '-')
                alpha_vis[sudoku[i][j] - 'A'] = true;
            else {
                FOR_RANGE_LT(a, 0, L) {
                    int b = 1 << a; char c = a + 'A';
                    if (mask[i][j] & b) {
                        alpha_avai[a][alpha_cnt[a]].i = i;
                        alpha_avai[a][alpha_cnt[a]].j = j;
                        alpha_avai[a][alpha_cnt[a]].c = c;
                        ++alpha_cnt[a];
                    }
                }
            }
        }
        FOR_RANGE_LT(a, 0, L) {
            if (alpha_vis[a]) {
                assert(!alpha_cnt[a]);
                continue;
            }
            assert(alpha_cnt[a] >= 2);
            if (update_min(num_choices, alpha_cnt[a])) {
                memcpy(choices, alpha_avai[a], alpha_cnt[a] * sizeof(Fill));
            }
        }
    }
    assert(num_choices >= 2 && num_choices <= 16);
    *p_num_choices = num_choices;
}

void dfs(int depth) {
#ifdef DEBUG
    static int count = 0;
    fprintf(stderr, "[dfs] depth=%3d, count=%d\n", depth, ++count);
#endif

    // 1. Fill all certain positions
    int num_certain = fill_certain();
    if (num_certain < 0 || solved)   // error or solved
        return;
    // 2. Find a scope with the least choices
    int num_choices;
    Fill choices[L];
    least_available_choices(choices, &num_choices);

    // 3. Enumerate each choice and search deeper
    unsigned char s_sudoku[sizeof(sudoku) + 6], s_mask[sizeof(mask) + 6];
#define ctx_save() do { memcpy(s_sudoku, sudoku, sizeof(sudoku)); memcpy(s_mask, mask, sizeof(mask)); } while(0)
#define ctx_restore() do { memcpy(sudoku, s_sudoku, sizeof(sudoku)); memcpy(mask, s_mask, sizeof(mask)); } while (0)

    ctx_save();
    FOR_RANGE_LT(n, 0, num_choices) {
        fill_one(choices[n].i, choices[n].j, choices[n].c);
        dfs(depth + num_certain + 1);
        if (solved)
            break;
        ctx_restore();
    }

#undef ctx_save
#undef ctx_restore
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

#ifdef SPOJ
    getint(); // input T
#endif
    bool first = false;
    while (scanf("%s", sudoku[0]) != EOF) {
        assert(trim_strlen(sudoku[0]) == L);
        FOR_RANGE_LT(i, 1, L) {
            assert(scanf("%s", sudoku[i]) == 1);    // eliminate O2 warning
            assert(trim_strlen(sudoku[i]) == L);
        }
        solved = false;
        FOR_RANGE_LT(i, 0, L) FOR_RANGE_LT(j, 0, L)
            mask[i][j] = (1 << L) - 1;
        FOR_RANGE_LT(i, 0, L) FOR_RANGE_LT(j, 0, L) {
            char c = sudoku[i][j];
            if (c == '-')
                continue;
            sudoku[i][j] = '-';
            fill_one(i, j, c);
        }
        dfs(0);
        assert(solved);
        if (first)
            printf("\n");
        print_sudoku(stdout);
        first = true;
    }

    return 0;
}
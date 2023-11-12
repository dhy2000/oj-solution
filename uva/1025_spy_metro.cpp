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

#define N 50
#define T 200

struct GIndex {
    int id, tim;
};

struct Edge {
    GIndex to;
    int w;
    Edge(int id, int tim, int w): to({id, tim}), w(w) {}
    // less-priority-queue
    bool operator < (const Edge &b) const {
        return w > b.w;
    }
};

struct Node {
    GIndex index;
    vector<Edge> edges;
};

Node graph[N + 5][T + 5];
int dist[N + 5][T + 5];
bool vis[N + 5][T + 5];

void shortest_path() {
    memset(dist, 0x3f, sizeof(dist));
    CLEAR(vis);
    dist[0][0] = 0;
    priority_queue<Edge> pq;
    pq.emplace(0, 0, 0);
    while (!pq.empty()) {
        Edge h = pq.top();
        pq.pop();
        if (vis[h.to.id][h.to.tim])
            continue;
        vis[h.to.id][h.to.tim] = true;
        FOR_ITER(it, graph[h.to.id][h.to.tim].edges, vector<Edge>) {
            if (dist[it->to.id][it->to.tim] > dist[h.to.id][h.to.tim] + it->w) {
                dist[it->to.id][it->to.tim] = dist[h.to.id][h.to.tim] + it->w;
                pq.emplace(it->to.id, it->to.tim, dist[it->to.id][it->to.tim]);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int case_id = 0;
    while (1) {
        int n_station = getint();
        ++case_id;
        if (n_station == 0)
            break;
        int t_fin = getint();
        static int tim_between[N + 5];
        FOR_RANGE_LT(i, 0, n_station - 1)
            tim_between[i] = getint();
        int n_start, n_end;
        static int dept_st[N + 5], dept_ed[N + 5];
        n_start = getint();
        FOR_RANGE_LT(i, 0, n_start)
            dept_st[i] = getint();
        n_end = getint();
        FOR_RANGE_LT(i, 0, n_end)
            dept_ed[i] = getint();
        
        // Build Graph
        FOR_RANGE_LT(i, 0, n_station)
            FOR_RANGE_EQ(j, 0, t_fin) {
                graph[i][j].index.id = i;
                graph[i][j].index.tim = j;
                graph[i][j].edges.clear();
                if (j > 0)
                    graph[i][j - 1].edges.emplace_back(i, j, 1);
            }
        // Add Forward Train
        FOR_RANGE_LT(train, 0, n_start) {
            int time_cur = dept_st[train];
            if (time_cur > t_fin)
                break;
            FOR_RANGE_LT(station, 0, n_station - 1) {
                // station[j] to station[j + 1]: tim_between[j]
                if (time_cur + tim_between[station] > t_fin)
                    break;
                graph[station][time_cur].edges.emplace_back(station + 1, time_cur + tim_between[station], 0);
                time_cur += tim_between[station];
            }
        }
        // Add Backword Train
        FOR_RANGE_LT(train, 0, n_end) {
            int time_cur = dept_ed[train];
            if (time_cur > t_fin)
                break;
            FOR_REV_GT(station, n_station - 1, 0) {
                if (time_cur + tim_between[station - 1] > t_fin)
                    break;
                graph[station][time_cur].edges.emplace_back(station - 1, time_cur + tim_between[station - 1], 0);
                time_cur += tim_between[station - 1];
            }
        }
#ifdef DEBUG
        // Dump the graph
        fprintf(stderr, "# Case %d\n\n", case_id);
        fprintf(stderr, "```mermaid\ngraph TD;\n");
        FOR_RANGE_LT(i, 0, n_station)
            FOR_RANGE_EQ(j, 0, t_fin)
                fprintf(stderr, "G_%d_%d(\"(%d @: %d)\");\n", i, j, i, j);
        FOR_RANGE_LT(i, 0, n_station)
            FOR_RANGE_EQ(j, 0, t_fin)
                FOR_ITER(it, graph[i][j].edges, vector<Edge>) {
                    fprintf(stderr, "G_%d_%d-->|%d|G_%d_%d;\n", i, j, it->w, it->to.id, it->to.tim);
                }
        fprintf(stderr, "```\n\n");
#endif
        // Shortest Path
        shortest_path();
        if (vis[n_station - 1][t_fin])
            printf("Case Number %d: %d\n", case_id, dist[n_station - 1][t_fin]);
        else
            printf("Case Number %d: impossible\n", case_id);
    }

    return 0;
}
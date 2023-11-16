#pragma GCC optimize("O2")
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <map>
#include <set>
using namespace std;

#define FOR_REPEAT(times) for (int __i = 0; __i < times; ++__i)
#define FOR_RANGE_EQ(iter,start,end) for (int iter = start; iter <= end; ++iter)
#define FOR_RANGE_LT(iter,start,end) for (int iter = start; iter < end; ++iter)
#define FOR_ITER(iter,container,type) for (type::iterator iter = container.begin(); iter != container.end(); ++iter)
template<typename T> inline static T update_max(T &m, const T &v) { if (v > m) m = v; return m; }
template<typename T> inline static T update_min(T &m, const T &v) { if (v < m) m = v; return m; }
inline static bool isclosef(float a, float b, float eps=1e-6) { return fabs(a - b) < eps; }
inline static bool isclose(double a, double b, double eps=1e-8) { return std::abs(a - b) < eps; }

#define N 2000
int n;
int dist[N + 5][N + 5];
char code[N + 5][16]; // code length is 7

inline static int distance_code(const char *s1, const char *s2) {
    const int len = 7;
    assert(strlen(s1) == len && strlen(s2) == len);
    int d = 0;
    FOR_RANGE_LT(i, 0, len) {
        if (s1[i] != s2[i]) ++d;
    }
    return d;
}

struct Edge {
    int from, to, value;
    Edge(): from(0), to(0), value(0) {}
    Edge(int from, int to, int value): from(from), to(to), value(value) {}
    void display(FILE *f) {
        fprintf(f, "%d-->%d(%d)\n", from, to, value);
    }
    bool operator < (const Edge &e) const {
        return value < e.value;
    }
};

int u_find(int* rt, int n) {
    if (rt[n] == n)
        return n;
    return (rt[n] = u_find(rt, rt[n]));
}

void u_join(int* rt, int m, int n) {
    int rm = u_find(rt, m);
    int rn = u_find(rt, n);
    assert(rm != rn);
    rt[rm] = rt[rn];
    u_find(rt, m); u_find(rt, n);
}

int cmp(const void *_p1, const void *_p2) {
    const Edge *p1 = (const Edge *)_p1;
    const Edge *p2 = (const Edge *)_p2;
    return (p1->value == p2->value) ? 0 : (p1->value < p2->value ? -1 : 1); 
}

int minimum_spanning_tree() {
    vector<Edge> edges;
    // kruskal, disjoint-union
    FOR_RANGE_LT(i, 0, n)
        FOR_RANGE_LT(j, 0, i) {
            edges.push_back(Edge(i, j, dist[i][j]));
        }
    // sort(edges.begin(), edges.end());
    qsort(edges.data(), edges.size(), sizeof(edges.data()[0]), cmp);
    // disjoint-union
    int uni[N + 5];
    FOR_RANGE_LT(i, 0, n) uni[i] = i;
    int cnt = 0, mst = 0;
    FOR_ITER(it, edges, vector<Edge>) {
        Edge e = *it;
        if (u_find(uni, e.from) == u_find(uni, e.to))
            continue;
#ifdef DEBUG
        e.display(stderr);
#endif
        mst += e.value;
        ++cnt;
        u_join(uni, e.from, e.to);
    }
    assert(cnt == n - 1);
    return mst;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        if (n == 0)
            break;
        FOR_RANGE_LT(i, 0, n) {
            assert(scanf("%s", code[i]) != EOF);
        }
        FOR_RANGE_LT(i, 0, n) {
            FOR_RANGE_LT(j, 0, i) {
                dist[i][j] = distance_code(code[i], code[j]);
            }
        }
#ifdef DEBUG
        FOR_RANGE_LT(i, 0, n)
            FOR_RANGE_LT(j, 0, i)
                fprintf(stderr, "%d%c", dist[i][j], j + 1 == i ? '\n' : ' ');
#endif
        int mst = minimum_spanning_tree();
        printf("The highest possible quality is 1/%d.\n", mst);
    }
    return 0;
}
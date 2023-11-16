/* Kosaraju's algorithm for solving Strongly Connected Component */

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>

using namespace std;

/* IO */
int getint() {
    char ch = getchar();
    int ret = 0;
    while (ch != EOF && !(ch >= '0' && ch <= '9')) 
        ch = getchar();
    if (ch == EOF) return EOF;
    while (ch >= '0' && ch <= '9')
        ret = (ret << 3) + (ret << 1) + (ch ^ '0'),
        ch = getchar();
    return ret;
}
void putint(int n) {
    char buf[12];
    int siz = 0;
    while (n > 0) {
        buf[siz] = (n % 10) + '0';
        siz++;
        n /= 10;
    }
    if (siz == 0) buf[0] = '0', siz = 1;
    while (siz--) {
        putchar(buf[siz]);
    }
}

using Graph_t = vector<unordered_set<int> >;
using Op_t = function<void (int)>;  // try functional in C++11

Graph_t graph, rgraph, sgraph;      // rgraph: reversed; sgraph: graph of scc, must be dag
unordered_set<int> visited;         // dfs visited
vector<int> finish;
Graph_t scc;    // strongly-connected-component
unordered_map<int, int> ofScc;      // vertex belongs to which scc

// dfs method with general use
void dfs(const Graph_t &g, int cur, const Op_t &func) {
    visited.insert(cur);
    for (int to : g[cur]) {
        if (visited.count(to)) continue;
        dfs(g, to, func);
    }
    func(cur);
}

int main() {
    // Initialize and input
    int n = getint(), m = getint();
    graph.resize(n + 1);
    rgraph.resize(n + 1);
    while (m--) {
        int x = getint(), y = getint();
        graph[x].insert(y);
        rgraph[y].insert(x);
    }
    // DFS on reversed graph
    visited.clear();
    auto getFinishTime = [] (int cur) {
        finish.push_back(cur);
    };
    for (int i = 1; i <= n; i++) {
        if (!visited.count(i)) 
            dfs(rgraph, i, getFinishTime);
    }
    // DFS on graph by last finish order
    reverse(finish.begin(), finish.end());
    visited.clear();
    for (int i : finish) {
        if (!visited.count(i)) {
            unordered_set<int> component;
            auto addToComponent = [&component] (int cur) {
                component.insert(cur);
                ofScc[cur] = scc.size();
            };
            dfs(graph, i, addToComponent);
            scc.push_back(move(component));
        }
    }
    
    #ifdef DEBUG
    // output sccs
    printf("Total %d sccs.\n", scc.size());
    for (unordered_set<int> component : scc) {
        for (int i : component) {
            putint(i);
            putchar(' ');
        }
        putchar('\n');
    }
    #endif

    // build graph of scc (should be reversed)
    vector<int> outdeg;
    int sccCount = scc.size();
    outdeg.resize(sccCount);
    sgraph.resize(sccCount);
    for (int i = 0; i < sccCount; i++) {
        for (int u : scc[i]) {
            for (int v : graph[u]) {
                int j = ofScc[v];
                if (i != j && !sgraph[i].count(j)) {
                    sgraph[i].insert(j);
                    outdeg[i]++; // out degree
                }
            }
        }
    }
    int welcome = -1, cnt = 0;
    for (int i = 0; i < sccCount; i++) {
        if (outdeg[i] == 0) {
            welcome = i;
            cnt++;
        }
    }

    if (cnt != 1) {
        putint(0);
    } else {
        putint(scc[welcome].size());
    }

    return 0;
}
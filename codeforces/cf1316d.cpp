// Nash Matrix
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define rep(_i,_l,_r) for (int _i = _l; _i <= _r; _i++)
#define repall rep(i,1,n) rep(j,1,n)
const int MAXN = 1001;
int n;
struct point {
    int x, y;
    inline point operator + (const point& b) const {
        return { x + b.x, y + b.y };
    }
    inline bool operator == (const point& b) const {
        return x == b.x and y == b.y;
    }
    inline bool valid() { return x >= 1 && x <= n && y >= 0 && y <= n; }
};
map<char, point> side{ {'D',{1,0}},{'U',{-1,0}},{'R',{0,1}},{'L',{0,-1}} };
map<char, char> oppo{ {'U','D'},{'D','U'},{'L','R'},{'R','L'} };
char mp[MAXN + 1][MAXN + 1];
point dest[MAXN + 1][MAXN + 1];
int viscnt = 0;
void dfs(point pos) { // 起点必须是-1-1或者X
    for (auto dx : side) {
        point nxt = pos + dx.second;
        if (mp[nxt.x][nxt.y]) continue; // 该点被搜过
        if (dest[nxt.x][nxt.y] == dest[pos.x][pos.y]) {
            mp[nxt.x][nxt.y] = oppo[dx.first]; viscnt++;
            dfs(nxt);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin >> n; repall{
        int x,y; cin >> x >> y;
        dest[i][j] = {x, y};
        if (point{i,j} == point{x,y}) mp[i][j] = 'X', viscnt++;
    }
        repall{
            if (dest[i][j] == point{-1,-1} && !mp[i][j]) dfs({i,j});
            else if (mp[i][j] == 'X')dfs({i,j});
    }
    if (viscnt < n * n) { cout << "INVALID\n"; }
    else {
        cout << "VALID\n";
        rep(i, 1, n) {
            cout << mp[i] + 1 << "\n";
        }
    }
    return 0;
}
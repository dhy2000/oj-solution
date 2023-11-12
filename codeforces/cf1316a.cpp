#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        int total = 0;
        for (int i = 0; i < n; i++) { int x; cin >> x; total += x; }
        cout << (total > m ? m : total) << "\n";
    }
    return 0;
}
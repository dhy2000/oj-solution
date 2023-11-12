// cf1316b String Modification
/*
首先是找规律。题意中的操作大致像一个长度为k的滑动窗口，每次将这k个元素翻转，然后滑动窗口前进，直到末端到达字符串尾部。
可以先试着找规律，例如a b c d e f，k=3
则前几次的操作大致为：[cba]def, c[dab]ef, cd[eba]f, cde[fab]
可以看到其实本质上相当于将前k-1个字符 "移动" 至字符串的末尾，移动奇数次则再反转一下，字符串的主体后缀不动。
题目要求是选取一个最小的k使得转化完的字符串字典序最小。

*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string oper(string s, int k) {
    string s1 = s.substr(0, k - 1), s2 = s.substr(k - 1);
    if (s2.size() % 2 == 1) reverse(s1.begin(), s1.end());
    return s2 + s1;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T; while (T--) {
        int l; string s; cin >> l >> s;
        int ans = 1; string mns = s;
        for (int k = 1; k <= l; k++) {
            string oped = oper(s, k);
            if (oped < mns) { mns = oped; ans = k; }
        }
        cout << mns << "\n" << ans << "\n";
    }
    return 0;
}
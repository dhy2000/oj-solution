#include <stdio.h>
#include <stdlib.h>

char ch[1025][1025];

void solve(int px, int py, int rd) {
    if (rd == 0) return ;
    // top-left
    int r = (1 << (rd - 1));
    for (int i = 0; i < r; i++)
    for (int j = 0; j < r; j++)
        ch[px + i][py + j] = 1; // shemian
    solve(px + r, py, rd - 1);
    solve(px, py + r, rd - 1);
    solve(px + r, py + r, rd - 1);
}

int main()
{
    int n; scanf("%d", &n);
    solve(0, 0, n);
    int r = (1 << n);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            if (ch[i][j] == 0) putchar('1');
            else putchar('0');
            if (j < r - 1) putchar(' ');
        }
        putchar('\n');
    }

    return 0;
}
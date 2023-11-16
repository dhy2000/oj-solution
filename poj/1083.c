#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        assert(1 <= n && n <= 200);
        int cnt[205] = {};
        int mask[505] = {};
        int m = n;
        int mc = 0;
        while (n--) {
            int st, ed;
            scanf("%d %d", &st, &ed);
            assert(1 <= st && st <= 400);
            assert(1 <= ed && ed <= 400);
            if (st > ed) {
                int t = st;
                st = ed;
                ed = t;
            }
            assert(st <= ed);
            assert(!mask[st] && !mask[ed]);
            mask[st] = mask[ed] = 1;
            st = (st + 1) / 2;
            ed = (ed + 1) / 2;
            // fprintf(stderr, "%d -> %d\n", st, ed);
           
            for (int i = st; i <= ed; i++) {
                assert(i >= 0 && i <= 201);
                cnt[i]++;
                if (cnt[i] > mc) mc = cnt[i];
            }
        }
        assert(mc <= m);
        printf("%d\n", mc * 10);
    }
    return 0;
}
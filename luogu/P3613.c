#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Pool[10000005], *pool_sp = Pool;

int *mymalloc(int siz) {
    if (siz == 0) return NULL;
    int *ret = pool_sp;
    pool_sp += siz;
    return ret;
}
#define max(a,b) ((a)>(b)?(a):(b))

int *locker[100005], lim[100005];

typedef struct Input {
    int op, i, j, k;
}Input;
Input buf[100005];
Input readln() {
    int op, i, j, k = -1;
    scanf("%d", &op);
    if (op == 1) scanf("%d %d %d", &i, &j, &k);
    else scanf("%d %d", &i, &j);
    Input ret = {op, i, j, k};
    return ret;
}


int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < q; i++) {
        buf[i] = readln();
        lim[buf[i].i] = max(lim[buf[i].i], buf[i].j);
    }
    for (int i = 1; i <= n; i++) {
        locker[i] = mymalloc(lim[i]);
    }
    for (int i = 0; i < q; i++) {
        if (buf[i].op == 1) {
            *(locker[buf[i].i] + buf[i].j) = buf[i].k;
        }
        else {
            printf("%d\n", *(locker[buf[i].i] + buf[i].j));
        }
    }


    return 0;
}

/*
5 4
1 3 10000 114514
1 1 1 1
2 3 10000
2 1 1
*/
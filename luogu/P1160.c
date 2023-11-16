#include <stdio.h>
#include <stdlib.h>

typedef struct Person {
    // int id;
    int left, right;
    int del;
}Person;
Person stu[100005];

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 2; i <= N; i++) {
        int k, p;
        scanf("%d %d",&k,&p);
        if (p == 0) {
            // 插入左边
            if (stu[k].left == 0) {
                stu[k].left = i;
                stu[i].right = k;
            }
            else {
                stu[i].left = stu[k].left;
                stu[stu[k].left].right = i;
                stu[i].right = k;
                stu[k].left = i;
            }
        }
        else {
            if (stu[k].right == 0) {
                stu[k].right = i;
                stu[i].left = k;
            }
            else {
                stu[i].right = stu[k].right;
                stu[stu[k].right].left = i;
                stu[i].left = k;
                stu[k].right = i;
            }
        }
    }
    // 找最左边的人是谁
    int head = 1;
    while (stu[head].left != 0) head = stu[head].left;
    int M, del;
    scanf("%d", &M);
    while (M--) {
        scanf("%d", &del);
        stu[del].del = 1;
    }
    int prt = 0;
    for (int cur = head; cur != 0; cur = stu[cur].right) {
        if (stu[cur].del) continue;
        if (prt) putchar(32);
        prt = 1;
        printf("%d", cur);
    }
    putchar(10);

    return 0;
}
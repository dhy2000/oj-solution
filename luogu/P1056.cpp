#include <cstdio>
#include <algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
int M,N,K,L,D;
struct paircnt
{
    int pos, cnt;
};
paircnt r[1005], c[1005];
bool cmp1(paircnt a, paircnt b)
{
    return a.cnt > b.cnt;
}
bool cmp2(paircnt a, paircnt b)
{
    return a.pos < b.pos;
}
int main()
{
    scanf("%d%d%d%d%d",&M,&N,&K,&L,&D);
    for (int i = 1;i<=M;i++)
        r[i].pos = i;
    for (int i = 1;i<=N;i++)
        c[i].pos = i;
    for (int i = 1;i <= D;i++)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if (x1 == x2)
        {
            int y = min(y1,y2);
            c[y].cnt++;
        }
        else
        {
            int x = min(x1,x2);
            r[x].cnt++;
        }
    }
    sort(r+1,r+M+1,cmp1);
    sort(c+1,c+N+1,cmp1);
    if (K > 1)sort(r+1,r+K+1,cmp2);
    if (L > 1)sort(c+1,c+L+1,cmp2);
    for (int i = 1;i<=K;i++)
    {
        printf("%d%s",r[i].pos, i == K ? "" : " ");
    }
    printf("\n");
    for (int i = 1;i<=L;i++)
    {
        printf("%d%s",c[i].pos, i == L ? "" : " ");
    }
    printf("\n");
    return 0;
}

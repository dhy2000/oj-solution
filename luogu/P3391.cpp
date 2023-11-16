#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;
typedef int pnode;
const int INF = INT_MAX, MAXN = 1000005;
inline void swap(int &a, int &b)
{
    int tmp = a; a = b; b = tmp;
}
struct node
{
    int val, sz;
    bool rev;//值，子树大小，反转标记
    int father, child[2];//child[0]:左儿子，child[1]:右儿子
}tree[MAXN];
int m, n;
int tsize = 0;
pnode root;
inline void push_up(pnode x)
{
    if (x)
    {
        tree[x].sz = 1;
        if (tree[x].child[0])
            tree[x].sz += tree[tree[x].child[0]].sz;
        if (tree[x].child[1])
            tree[x].sz += tree[tree[x].child[1]].sz;
    }
}
inline void push_down(int x)
{
    if (tree[x].rev)
    {
        if (tree[x].child[0])
        {
            tree[tree[x].child[0]].rev ^= 1;//状态反转
            swap(tree[tree[x].child[0]].child[0], tree[tree[x].child[0]].child[1]);
        }
        if (tree[x].child[1])
        {
            tree[tree[x].child[1]].rev ^= 1;
            swap(tree[tree[x].child[1]].child[0], tree[tree[x].child[1]].child[1]);
        }
        tree[x].rev = 0;
    }
}
inline void rotate(pnode x, int kind)//kind = 0左旋，kind = 1右旋
{
    pnode fa = tree[x].father, ffa = tree[fa].father;
    pnode ch = tree[x].child[kind];
    tree[x].child[kind] = fa, tree[x].father = ffa;
    tree[fa].child[!kind] = ch, tree[fa].father = x;
    tree[ffa].child[tree[ffa].child[1] == fa] = x;
    tree[ch].father = fa;
    push_up(fa), push_up(x);
}
inline void splay(pnode x, pnode goal)
{
    if (x == goal)return;
    while (tree[x].father != goal)
    {
        int fa = tree[x].father, ffa = tree[fa].father;
        push_down(ffa), push_down(fa), push_down(x);
        bool isrson1 = tree[fa].child[1] == x, isrson2 = tree[ffa].child[1] == fa;
        if (ffa == goal)
            rotate(x, !isrson1);
        else
        {
            if (isrson1 == isrson2)
                rotate(fa, !isrson2);
            else
                rotate(x, !isrson1);
            rotate(x, !isrson2);
        }
    }
    if (goal == 0)root = x;
}
inline int createNode(int val, int fa)
{
    tsize++;
    tree[tsize].val = val;
    tree[tsize].father = fa;
    tree[tsize].child[0] = tree[tsize].child[1] = 0;
    tree[tsize].sz = 1;
    return tsize;
}
inline int query(int x)//找树中第x大的数，即Splay之排名检索
{
    int now = root;
    while (tree[tree[now].child[0]].sz + 1 != x)
    {
        if (tree[tree[now].child[0]].sz + 1 > x)
            now = tree[now].child[0];
        else
        {
            x -= tree[tree[now].child[0]].sz + 1;
            now = tree[now].child[1];
        }
        push_down(now);
    }
    return now;
}
inline void interval_reverse(int l, int r)
{
    splay(query(l - 1), 0);
    splay(query(r + 1), root);
    int t = tree[tree[root].child[1]].child[0];
    tree[t].rev ^= 1;
    swap(tree[t].child[0], tree[t].child[1]);
}
inline int build_tree(int l, int r, int f)
{
    if (l > r)return 0;
    int mid = (l + r) >> 1, x = ++tsize;
    node newnode = {mid - 1, 1, false, f, {0,0}};
    tree[x] = newnode;
    tree[x].child[0] = build_tree(l, mid - 1, x);
    tree[x].child[1] = build_tree(mid + 1, r, x);
    push_up(x);
    return x;
}


int prt[MAXN], prtsp;
inline void traverse(int x)
{
    push_down(x);
    if (tree[x].child[0])traverse(tree[x].child[0]);
    if (tree[x].val >= 1 && tree[x].val <= n)
        // printf("%d\n", tree[x].val);
        prt[++prtsp] = tree[x].val;
    if (tree[x].child[1])traverse(tree[x].child[1]);
}

int main()
{
    scanf("%d%d", &n, &m);
    root = build_tree(1, n + 2, 0);

    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        interval_reverse(l + 1, r + 1);
    }

    traverse(root);
    for (int i = 1; i <= prtsp; i++) {
        printf("%d ", prt[i]);
    }
    return 0;
}

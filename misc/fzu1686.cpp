// 验证原题
// 原题出处: FZU 1686 神龙的难题

// Key: DLX 可重复覆盖问题
/* DLX模型: 把R*R的矩形中每个木箱子当成列，把泡泡炸弹能覆盖到的范围当成行, 一个泡泡弹能覆盖几个木箱，这一行就有哪些列是1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXR 15 // 地图的格数
int R, C, a, b;
char mp[MAXR + 5][MAXR + 5];
int boxcnt[MAXR + 5][MAXR + 5]; // boxcnt: 给每个有木箱子的格子编上号
#define MAXMAT ((MAXR)*(MAXR))
char DLMat[MAXMAT + 5][MAXMAT + 5]; // [覆盖问题]模板的矩形(从1开始用)
// Dancing Link List
typedef struct DLXNode {
    // int R, C; // row col, 这个节点是第几行第几列
    int l, r, u, d; // 四个方向的next
}DLXNode;
int DLRow, DLCol; // 覆盖矩阵的行数(多少种安放炸弹的位置)和列数(多少个木箱子)
DLXNode DLX[MAXMAT + 5][MAXMAT + 5];
/* DLX二维数组: [0][0]表示head, [0][i]表示第i列的列首, [i][j]表示第i行第j列的节点 */
/* 关于l r u d四个分量的解释:
   对于DLX[i][j], 这个节点的right为DLX[i][DLX[i][j].r], 其up为DLX[DLX[i][j].u][j], 以此类推.
   即: 每个分量表示自己在这个行/列方向的链接到的节点的行/列坐标.
 */
// #define pos2idx(i,j) ((i)*R+(j)+1)


int inputdata() {
    int flg = scanf("%d %d", &R, &C);
    if (flg == EOF) return 0;
    memset(mp, 0, sizeof(mp));
    memset(boxcnt, 0, sizeof(boxcnt));
    int cnt = 0;
    for (int i = 0; i < R; i++) {
        // scanf("%s", mp[i]);
        for (int j = 0; j < C; j++) {
            scanf(" %c", &mp[i][j]);
            if (mp[i][j] == '1') {
                boxcnt[i][j] = (++cnt);
            }
        }
    }
    scanf("%d %d", &a, &b);
    DLCol = cnt; // 一共这么多个可以炸掉的木箱子
    return 1;
}

void initDLX() { // 初始化跳舞链表
    memset(DLX, 0, sizeof(DLX));
    // 先将列首串联起来
    DLX[0][0].r = 1; DLX[0][0].l = DLCol;
    DLX[0][DLCol].l = DLCol - 1; DLX[0][DLCol].r = 0;
    for (int i = 1; i < DLCol; i++) {
        DLX[0][i].l = i - 1;
        DLX[0][i].r = i + 1;
    }
}

void buildXmat() {
    // int cntbomb = 0;
    DLRow = 0;
    memset(DLMat, 0, sizeof(DLMat));
    for (int i = 0; i + a <= R; i++) {
        for (int j = 0; j + b <= C; j++) {
            // 外层循环: 枚举矩形炸弹的位置
            int flg = 0;
            for (int ii = 0; ii < a; ii++) {
                for (int jj = 0; jj < b; jj++) {
                    // 内层循环: 枚举这个矩形炸弹里边有没有木箱子
                    if (mp[i + ii][j + jj] == '1') {
                        if (!flg) DLRow++;
                        flg = 1;
                        DLMat[DLRow][boxcnt[i + ii][j + jj]] = 1;
                    }
                }
            }
        }
    }
}

void buildDancingList() { // 构造跳舞链表
    // 依据DLMat矩阵建立
    // 第一个循环: 把每一列拉起来
    for (int j = 1; j <= DLCol; j++) {
        int last1 = 0;
        // 拉起上下方向的循环链表
        for (int i = 1; i <= DLRow; i++) {
            if (DLMat[i][j] == 1) {
                DLX[last1][j].d = i;
                DLX[i][j].u = last1;
                last1 = i;
            }
        }
        DLX[0][j].u = last1;
        DLX[last1][j].d = 0;
    }
    // 第二个循环: 把每一行拉起来
    for (int i = 1; i <= DLRow; i++) {
        int first1 = -1, last1 = -1;
        // 先找到这一行的第一个1
        for (int j = 1; j <= DLCol; j++) {
            if (DLMat[i][j] == 1) {first1 = j; break;}
        }
        last1 = first1;
        // 拉起左右方向的循环链表
        for (int j = last1 + 1; j <= DLCol; j++) {
            if (DLMat[i][j] == 1) {
                DLX[i][last1].r = j;
                DLX[i][j].l = last1;
                last1 = j;
            }
        }
        DLX[i][last1].r = first1;
        DLX[i][first1].l = last1;
    }
}

// 删节点: 分方向，等同于双向链表的删节点
#define rmNodeLR(i,j) ({DLX[i][DLX[i][j].r].l = DLX[i][j].l, DLX[i][DLX[i][j].l].r = DLX[i][j].r;})
#define rmNodeUD(i,j) ({DLX[DLX[i][j].u][j].d = DLX[i][j].d, DLX[DLX[i][j].d][j].u = DLX[i][j].u;})
// 恢复节点：也是分方向，利用被"删"节点原有的指针域信息找回(要按删的顺序逆序找回)
#define rstNodeLR(i,j) ({DLX[i][DLX[i][j].r].l = j, DLX[i][DLX[i][j].l].r = j;})
#define rstNodeUD(i,j) ({DLX[DLX[i][j].u][j].d = i, DLX[DLX[i][j].d][j].u = i;})

// https://blog.csdn.net/ling_wang/article/details/81204010
// 这篇博客对于精确覆盖的讲解较为详细，要将其转化为可重复覆盖问题，只需将删链表的规则稍加修改: 
// 选中了C1列中的某行之后，直接删掉这一行有的节点对应的列即可, 不需要删多余橙色的节点.

void dispDLX() ;
void dispDLM() ;

void removeCol(int i, int j) { // 删列
    // 使这一列对于它的左右而言消失，但保留列内部的上下关系
    int cur_i = 0; // 从列首开始
    do {
        if (cur_i != i) // 控制删列这一行的左右连接信息不能删
            rmNodeLR(cur_i, j);
        cur_i = DLX[cur_i][j].d;
    }while (cur_i != 0);
}
void removeRow(int i, int j) { // 删行
    // 根据这一行里的所有出现的1，删掉这些对应的列
    // int j: 标示这一行首个出现的1
    // 对于这一行而言，使其相对于其上下消失，而不改变行内部的左右关系
    int cur_j = j;
    do {
        removeCol(i, cur_j);
        dispDLX();
        cur_j = DLX[i][cur_j].r;
    }while (cur_j != j);
}
void restoreCol(int i, int j) { // 恢复列
    int cur_i = 0;
    do {
        if (cur_i != i) // 最初导致删列的这一行不用动
            rstNodeLR(cur_i, j);
        cur_i = DLX[cur_i][j].d;
    }while (cur_i != 0);
}
void restoreRow(int i, int j) { // 恢复行
    int cur_j = DLX[i][j].l;
    while (cur_j != j) {
        restoreCol(i, cur_j); // 倒着沿这行的节点去恢复列
        dispDLX();
        cur_j = DLX[i][cur_j].l; // 倒着来
    }
    restoreCol(i, j);
}
int nBombMax; // 最多所需炸弹个数
int rowSelected[MAXMAT + 5], rowSelNum = 0; // 答案的栈, 选中了第几行

int minAnswer = 99999999;


// 暴搜过不去，要加剪枝

int EX_calc() {
    int vis[MAXMAT + 5] = {0};
    int ret = 0;
    // for (int c = DLX[0][0].r; c != 0; c = DLX[0][c].r) vis[c] = 1;
    for (int c = DLX[0][0].r; c != 0; c = DLX[0][c].r) {
        if (vis[c]) continue;
        ret++;
        vis[c] = 1;
        for (int i = DLX[0][c].d; i != 0; i = DLX[i][c].d) {
            /*int st_j = DLX[i][0].r, j = st_j;
            do {
                vis[j] = 1;
                j = DLX[i][j].r;
            }while (j != st_j);*/
            for (int j = DLX[i][c].r; j != c; j = DLX[i][j].r) {
                vis[j] = 1;
            }
        }
    }
    return ret;
}

void dfs() {
    if (DLX[0][0].r == 0) { // Head->Right == Head
        // 此时答案已经找到了
        minAnswer = rowSelNum < minAnswer ? rowSelNum : minAnswer; // 更新一下答案

        // debug
        /*printf("Selected: ");
        for (int i = 0; i < rowSelNum; i++) {
            printf("%d ", rowSelected[i]);
        }
        printf("\n");*/

        return ;
    }


    // 强剪枝:
    if (rowSelNum + EX_calc() >= minAnswer) return ; // 别搜了


    // <del>// 从Head->Right开始找</del>
    // 从尚存的列当中选择1个数最少的
    // int cur_j = DLX[0][0].r;
    int cur_j = 0, mincnt1 = 9999999;
    for (int j = DLX[0][0].r; j != 0; j = DLX[0][j].r) {
        // 数这列多少个1
        int cnt1 = 0;
        for (int i = DLX[0][j].d; i != 0; i = DLX[i][j].d) cnt1++;
        if (cnt1 < mincnt1) mincnt1 = cnt1, cur_j = j;
    }
    // cur_j = DLX[0][0].r;
    int i = DLX[0][cur_j].d;
    while (i != 0) {
        // 从这开始继续搜索
        // 删除行列+压栈
        removeRow(i, cur_j);
        dispDLX();
        rowSelected[rowSelNum++] = i;

        dfs();

        // 恢复行列+退栈
        restoreRow(i, cur_j);
        dispDLX();
        rowSelected[--rowSelNum] = 0;

        // 选下一行
        i = DLX[i][cur_j].d;
    }// while (i != 0);
}



// #define _DEBUG
#ifdef _DEBUG
void dispDLM() {
    for (int i = 1; i <= DLRow; i++) {
        for (int j = 1; j <= DLCol; j++) {
            printf("%d ", (int)DLMat[i][j]);
        }
        printf("\n");
    }
}
void dispDLX() {
    for (int i = 0; i <= DLRow; i++) {
        for (int j = 0; j <= DLCol; j++) {
            printf("[%2d,%2d,%2d,%2d] ", DLX[i][j].l, DLX[i][j].r, DLX[i][j].u, DLX[i][j].d);
        }
        printf("\n");
    }
}

#else
void dispDLX() {}
void dispDLM() {}
#endif


int main()
{
    
    while (inputdata()) {
        minAnswer = 99999999;
        initDLX(); // OKAY

        buildXmat(); // OKAY
        buildDancingList(); // OKAY
//         dispDLM();
//         dispDLX();
        dfs();
        printf("%d\n", minAnswer);

    }
    return 0;
}

/*

Input #1: 
4 4
1 0 0 1
0 1 1 0
0 1 1 0
1 0 0 1
2 2
4 4 
0 0 0 0
0 1 1 0
0 1 1 0
0 0 0 0
2 2
4 4
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
2 2


Output #1:
4
1


*/
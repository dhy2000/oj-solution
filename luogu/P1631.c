#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 100005
int n, a[MAXN], b[MAXN];
typedef struct Node {
    int i, j;
}Node;

/* ------ Declaration of Heap ------ */
typedef Node h_Elemtype;
// if min-heap, return b - a;
int cmpElem(h_Elemtype ea, h_Elemtype eb) {
    /*if (a == b) return 0;
    else return a < b ? 1 : -1;*/
    int s1 = a[ea.i] + b[ea.j], s2 = a[eb.i] + b[eb.j];
    if (s1 == s2) return 0;
    else return s1 < s2 ? 1 : -1;
}
#define MAX_HEAPSIZE 1000005
typedef struct Heap {
    // starts with index 1
    int siz;
    bool isdel;
    h_Elemtype elm[MAX_HEAPSIZE];
}Heap;
bool h_empty(Heap *heap) {
    return heap->siz == 0;
}
int h_size(Heap *heap) {
    return heap->siz;
}
void siftup(Heap *heap, int pos) {
    h_Elemtype tmp = heap->elm[pos];
    while (pos > 1) {
        int fa = pos >> 1;
        if (cmpElem(tmp, heap->elm[fa]) > 0) heap->elm[pos] = heap->elm[fa];
        else break;
        pos = fa;
    }
    heap->elm[pos] = tmp;
}
void siftdown(Heap *heap, int pos) {
    h_Elemtype tmp = heap->elm[pos];
    while (pos < heap->siz) {
        int nxt = pos << 1;
        if (nxt > heap->siz) break;
        if (nxt + 1 <= heap->siz && cmpElem(heap->elm[nxt], heap->elm[nxt + 1]) < 0) {
            nxt = nxt + 1;
        }
        if (cmpElem(tmp, heap->elm[nxt]) > 0) break;
        heap->elm[pos] = heap->elm[nxt];
        pos = nxt;
    }
    heap->elm[pos] = tmp;
}
void h_push(Heap *heap, h_Elemtype x) {
    if (heap->isdel) {
        heap->elm[1] = x;
        siftdown(heap, 1);
        heap->isdel = false;
    }
    else {
        heap->elm[++heap->siz] = x;
        siftup(heap, heap->siz);
    }
}
void h_pop(Heap *heap) {
    if (heap->isdel) {
        heap->elm[1] = heap->elm[heap->siz--];
        siftdown(heap, 1);
    }
    else {
        heap->isdel = 1;
    }
}
h_Elemtype h_top(Heap *heap) {
    if (heap->isdel) {
        heap->elm[1] = heap->elm[heap->siz--];
        siftdown(heap, 1);
        heap->isdel = false;
    }
    return heap->elm[1];
}

Heap pq;

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
        scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) 
        scanf("%d", &b[i]);
    for (int i = 0; i < n; i++) {
        // push a[i] + b[0] into pq
        Node nd = {i, 0};
        h_push(&pq, nd);
    }
    for (int i = 0; i < n; i++) {
        Node top = h_top(&pq);
        h_pop(&pq);
        printf("%d", a[top.i] + b[top.j]);
        if (i != n - 1) putchar(' ');
        top.j++;
        h_push(&pq, top);
    }
    return 0;
}

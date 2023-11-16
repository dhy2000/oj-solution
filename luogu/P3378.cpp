#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAX_HEAPSIZE = 1000005;
template <typename T>
struct heap {
    T Ele[MAX_HEAPSIZE] = {}; 
    int heapsize;
    bool isdel = false;
    heap() {heapsize = 0; memset(Ele, 0, sizeof(Ele));}

    void siftdown(int pos) {
        // 维护大顶堆
        // 左儿子和右儿子里找到比自己大并且最大的元素交换，如果没有交换则停止
        T tmp = Ele[pos];
        while (pos < heapsize) {
            int nxt = pos << 1;
            if (nxt > heapsize) break;
            if (nxt + 1 <= heapsize && Ele[nxt] < Ele[nxt + 1])
                nxt++;
            if (Ele[nxt] < tmp) break;
            Ele[pos] = Ele[nxt];
            pos = nxt;
        }
        Ele[pos] = tmp;
    }
    void siftup(int pos) {
        T tmp = Ele[pos];
        while (pos > 1) {
            int fa = pos >> 1;
            if (Ele[fa] < tmp) Ele[pos] = Ele[fa];
            else break;
            pos = fa;
        }
        Ele[pos] = tmp;
    }

    inline bool empty() {return !heapsize || !(heapsize - isdel);}
    inline int size() {return heapsize - isdel;}
    inline void push(T x) {
        if (isdel) {
            Ele[1] = x;
            siftdown(1);
            isdel = false;
        }
        else {
            Ele[++heapsize] = x;
            siftup(heapsize);
        }
    }
    inline void pop() {
        if (isdel) {
            Ele[1] = Ele[heapsize--];
            siftdown(1);
        }
        else isdel = true;
    }
    inline T top() {
        if (isdel) {
            Ele[1] = Ele[heapsize--];
            siftdown(1);
            isdel = false;
        }
        return Ele[1];
    }
};
struct P {
    int x;
    inline bool operator < (const P &b) const {
        return x > b.x;
    }
};
heap<P> hp;
inline int read() {
    int ret = 0; char c = getchar();
    while ((c<'0'||c>'9'))c = getchar();
    while ((c>='0'&&c<='9'))ret = ret * 10 + (c - '0'), c = getchar();
    return ret;
}

int main() {
    int op, q, x;
    q = read();
    while (q--) {
        op = read();
        switch (op) {
            case 1:
                x = read();
                hp.push({x});
                break;
            case 2:
                x = hp.top().x;
                printf("%d\n", x);
                break;
            case 3:
                hp.pop();
                break;
        }
    }
    return 0;
}
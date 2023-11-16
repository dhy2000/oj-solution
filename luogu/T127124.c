#include <stdio.h>
#include <limits.h>
// using namespace std;
typedef unsigned int ui;
int main()
{
    int a, n1, n2;
    char op;
    scanf("a+%d%c%d", &n1,&op, &n2);
    // int n = n2 - n1;
    ui sol;
    if (op == '>')
    {
        // ui lw = n, up = (ui)INT_MAX+1U - n1;
        // sol = up - lw - 1;
        sol = (ui)INT_MAX - n2;
    }
    else {
        // sol = (ui)INT_MAX+1U + n + n1;
        sol = (ui)INT_MAX + 1 + n2;
    }
    printf("%u\n", sol);
}
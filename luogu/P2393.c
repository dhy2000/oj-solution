#include <cstdio>
#include <cstring>
using namespace std;
typedef unsigned long long ull;
int decbase[] = {1,10,100,1000,10000,100000,1000000};
char s[22];
ull sum = 0;
bool isnum(char c)
{
    return (c >= '0' && c <= '9');
}
int approx(int x)
{
    if (x % 10 >= 5)
    {
        x += (10 - (x % 10));
    }
    else
    {
        x -= (x % 10);
    }
    return x;
}
ull extract_ull(const char *s)
{
    int I = 0, F = 0, i;
    int l = strlen(s),d = 0;
    for (i = 0;i<l && s[i] != '.';i++)
    {
        if (isnum(s[i]))
            I = I * 10 + (s[i] - '0');
    }
    for (i++;i<l;i++)
    {
        if (isnum(s[i]))
            F = F * 10 + (s[i] - '0'),d++;
    }
    F *= decbase[6 - d];
    return (ull)I * 1000000 + F;
}
int main()
{
    while (scanf("%s",s) != EOF)
        sum += extract_ull(s);
    int f = approx(int(sum % 1000000));
    f /= 10;
    ull d = sum / 1000000;
    //printf("sum = %llu, d = %llu, f = %d\n",sum,d,f);
    while (f >= 1000000)f -= 1000000, d++;
    printf("%llu.%05d",d,f);
    return 0;
}

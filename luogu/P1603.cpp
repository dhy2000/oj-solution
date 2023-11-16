#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <climits>
using namespace std;
char num[][11] = {"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty"};
char word[22];
int sqrs[7];
int perm[7] = {1,2,3,4,5,6,7};
int len;
typedef unsigned long long ull;
int mystricmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && toupper(*(s1)) == toupper(*(s2)))s1++, s2++;
    if (toupper(*s1) < toupper(*s2))return -1;
    else if (toupper(*s1) > toupper(*s2))return 1;
    else return 0;
}
int findnum(const char *s)
{
    for (int i = 1;i<=20;i++)
    {
        if (mystricmp(num[i],s) == 0)return i;
    }
    if (!mystricmp(s, "a"))return 1;
    else if ((!mystricmp(s, "both")))return 2;
    else if ((!mystricmp(s, "another")))return 2;
    else if ((!mystricmp(s, "first")))return 1;
    else if ((!mystricmp(s, "second")))return 2;
    else if ((!mystricmp(s, "third")))return 3;
    return -1;
}
ull genline()
{
    ull s = 0;
    for (int i = 0;i < len;i++)
    {
        s = s * 100 + 1LLU * sqrs[perm[i] - 1];
    }
    return s;
}
int main()
{
    while (cin>>word)
    {
        int l = strlen(word);
        while (l > 0 && word[l - 1] == '.')word[--l] = 0;
        int nm = findnum(word);
        if (nm > -1)
        {
            sqrs[len++] = (nm * nm) % 100;
        }
    }
    unsigned long long mx = ULLONG_MAX;
    do
    {
        unsigned long long cd = genline();
        if (cd < mx)mx = cd;
    }while (next_permutation(perm, perm + len));
    cout<<mx<<endl;
    return 0;
}

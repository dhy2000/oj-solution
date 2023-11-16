#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
using namespace std;
enum TIMECOMPLEX {NONE,CONSTANT,LINEAR};
struct loop
{
    char var;
    TIMECOMPLEX tm;
};
stack<loop> stk;//char var;
bool var_used[27];
int main()
{
    int T;
    system("pause");
    cin>>T;
    while (T--)
    {
        memset(var_used,false,sizeof(var_used));
        while (!stk.empty())stk.pop();
        bool grammar = true;
        int O_times = 0, O_max = 0;
        int lines, timeO_exp = 0;
        char time_complex[105];
        int nonloop_depth = 0;

        cin>>lines>>time_complex;
        if (strcmp(time_complex, "O(1)") != 0){
            if (strcmp(time_complex, "O(n)") == 0)timeO_exp = 1;
            else sscanf(time_complex, "O(n^%d)", &timeO_exp);
        }
        while (lines--)
        {
            char ctrl;
            cin>>ctrl;
            if (ctrl == 'F')
            {
                char var;
                char st[101],ed[101];
                while ((var = getchar()) != EOF && !(var >= 'a' && var <= 'z'));
                cin>>st>>ed;
                if (!grammar)continue;
                /*检验语法错误*/
                if (var_used[var - 'a']){
                    grammar = false;
                }
                var_used[var - 'a'] = true;
                loop newloop = {var,NONE};
                if (st[0] == 'n')//判断循环时间复杂度,本层O(1)或者O(0)
                {
                    if (ed[0] == 'n')newloop.tm = CONSTANT;
                    else newloop.tm = NONE, nonloop_depth++;
                }
                if (st[0] != 'n')//本层循环O(n)复杂度
                {
                    if (ed[0] == 'n')newloop.tm = LINEAR;
                    else{
                        int ist,ied;
                        sscanf(st,"%d",&ist); sscanf(ed,"%d",&ied);
                        if (ist <= ied)newloop.tm = CONSTANT;
                        else newloop.tm = NONE, nonloop_depth++;
                    }
                }
                /*压栈*/
                stk.push(newloop);
                if (!nonloop_depth && newloop.tm == LINEAR)O_times++;
                if (O_times > O_max)O_max = O_times;
            }
            else if (ctrl == 'E')
            {
                if (!grammar)continue;
                if (stk.empty()){grammar = false;}
                else{
                    loop top = stk.top();
                    if (top.tm == NONE)nonloop_depth--;
                    if (top.tm == LINEAR && !nonloop_depth)O_times--;
                    var_used[top.var - 'a'] = false;
                    stk.pop();
                }
            }
            else
            {
                grammar = false;
            }
        }

        if (!grammar || stk.size())printf("ERR\n");
        else if (O_max == timeO_exp)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

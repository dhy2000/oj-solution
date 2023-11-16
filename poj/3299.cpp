#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

#define FOR_ITER(iter,container,type) for (type::iterator iter = container.begin(); iter != container.end(); iter++)

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    char t1, t2;
    double v1, v2;

    while (cin >> t1) {
        if (t1 == 'E') break;
        cin >> v1 >> t2 >> v2;
        double vT, vD, vH;
        bool hT = false, hD = false, hH = false;
        if (t1 == 'T') 
            hT = true, vT = v1;
        if (t1 == 'D')
            hD = true, vD = v1;
        if (t1 == 'H')
            hH = true, vH = v1;
        if (t2 == 'T') 
            hT = true, vT = v2;
        if (t2 == 'D')
            hD = true, vD = v2;
        if (t2 == 'H')
            hH = true, vH = v2;
        assert(t1 != t2);
        assert((int)hT + (int)hD + (int)hH == 2);

        double humidex = vH, temperature = vT, dewpoint = vD;
        // [1]: humidex = temperature + h
        // [2]: h = (0.5555) * (e - 10.0)
        // [3]: e = 6.11 × exp [5417.7530 × ((1/273.16) - (1/(dewpoint+273.16)))]

        // dewpoint => e => h
        // if missing dewpoint
        // h = humidex - temperature
        // e = h / 0.5555 + 10
        // Ln(e / 6.11) = 5417.7530 × ((1/273.16) - (1/(dewpoint+273.16)))
        // Ln(e / 6.11) / 5417.7530 = (1/273.16) - (1/(dewpoint+273.16))
        // (1/(dewpoint+273.16)) = (1/273.16) - (Ln(e / 6.11) / 5417.7530)
        // (dewpoint+273.16) = 1 / ((1/273.16) - (Ln(e / 6.11) / 5417.7530))
        // dewpoint = 1 / ((1/273.16) - (Ln(e / 6.11) / 5417.7530)) - 273.16
        double h, e;
        if (hD) {
            e = 6.11 * exp(5417.7530 * ((1/273.16) - (1/(dewpoint+273.16))));
            h = (0.5555) * (e - 10.0);
            if (hT)
                humidex = temperature + h;
            else {
                assert(hH);
                temperature = humidex - h;
            }
        }
        else {
            assert(hH && hT);
            h = humidex - temperature;
            e = h / 0.5555 + 10;
            dewpoint = 1 / ((1/273.16) - (log(e / 6.11) / 5417.7530)) - 273.16;
        }
        cout << "T " << fixed << setprecision(1) << temperature 
            << " D " << fixed << setprecision(1) << dewpoint
            << " H " << fixed << setprecision(1) << humidex
            << endl; 
    }

    return 0;
}
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using namespace std;
const int MN = -1e9;

int gcd(int a, int b) {
    int c;
    while (b) {
       c = a % b;
       a = b;
       b = c;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //freopen("input.txt", "r", stdin);

    int b, d;
    string a_raw;
    
    cin >> b >> d >> a_raw;

    int cnt_2, cnt_5;
    cnt_2 = cnt_5 = 0;
    int tmp_b = b;
    while (!(tmp_b%2)) {
        tmp_b /= 2;
        ++cnt_2;
    }
    while (!(tmp_b%5)) {
        tmp_b /= 5;
        ++cnt_5;
    }

    vector<int> po_2(cnt_2 + 1), po_5(cnt_5 + 1);
    po_2[0] = 1;
    for(int i = 1; i <= cnt_2; ++i) 
        po_2[i] = po_2[i - 1] * 2; 
    po_5[0] = 1;
    for(int i = 1; i <= cnt_5; ++i) 
        po_5[i] = po_5[i - 1] * 5; 

    int n = a_raw.length();

    vector<int> a;
    a.reserve(n);
    for(auto& c: a_raw) a.push_back(c - '0');

    vector<int> remd(n + 1), rem10(n + 1);
    vector<bool> ge(n + 1);
    rem10[0] = 1;
    for(int i = 1; i <= n; ++i) {
        rem10[i] = rem10[i - 1] * 10 % b;
    }

    ge[n] = true;
    for(int i = n - 1; i >= 0; --i) {
        remd[i] = (remd[i + 1] + d * rem10[n - 1 - i]) % b;
        if (a[i] > d) 
            ge[i] = true;
        if (a[i] < d) 
            ge[i] = false;
        if (a[i] == d)
            ge[i] = ge[i + 1];
    }
    
    if (d != 0 && ge[0] && !remd[0]) {
        cout << n << endl;
        return 0;
    }

    int it = 0;
    for(; it < n; ++it) {
        if (d != 0 && !remd[it + 1]) {
            cout << n - 1 - it << endl;
            return 0;
        }
        int t_rem = (b - remd[it + 1]) % b; 
        int c_rem10 = rem10[n - 1 - it];
        int g = po_2[min(cnt_2, n - 1 - it)] * po_5[min(cnt_5, n - 1 - it)];
        //cout << it << " " << t_rem << " " << c_rem10 << " " << g << endl;
        if (t_rem % g == 0) {
            int lim = 0;
            if (it > 7) {
                cout << n - 1 - it << endl;
                return 0;
            } else {
                for(int i = 0; i <= it; ++i) {
                    lim = lim * 10 + a[i];
                }
            }
            if (!ge[it + 1]) --lim;
            int rem = 0;
            for(int i = 1; i <= lim; ++i) {
                rem = (rem + c_rem10) % b;         
                if (rem == t_rem) {
                    cout << n - 1 - it << endl;
                    return 0;
                }
            }
        }
    }
    cout << 0 << endl;
}

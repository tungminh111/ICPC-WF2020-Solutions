#include <bits/stdc++.h>

using namespace std;
int n, v, c;
vector<pair<int, int>> d;

bool comp(const pair<int, int>& c1, const pair<int, int>& c2) {
    return c1.first - c2.first < (c2.second * v - 1) / c - (c1.second * v - 1) / c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen("input.txt", "r", stdin);
    cin >> n >> v >> c;

    d = vector<pair<int, int>>(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i].first >> d[i].second;
    }

    sort(d.begin(), d.end(), comp);

    int mx = 0;
    vector<bool> f(5e6, false);
    f[0] = true;
    for(int i = 0; i < n; ++i) {
        int rep = min(mx, (d[i].second * v - 1) / c);
        for(int j = rep; j >= 0; --j) if (f[j]) {
            int new_j = j + d[i].first;
            f[new_j] = true;
            if (new_j > mx) mx = new_j;
        }
    }

    long long ret = 0;
    for(int i = 0; i < n; ++i)
        ret += d[i].first;
    ret += (long long)(c - 1) * mx;
    cout << ret << endl;

    return 0;
}

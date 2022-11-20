#include <bits/stdc++.h>

using namespace std;
int n, c;
vector<vector<pair<int, int>>> to;
vector<int> val, pos, e;
vector<vector<unsigned int>> f;
vector<unsigned int> g;

void init(const int& x, const int& p) {
    for(auto& [y, z]: to[x]) if (y != p) {
        e[y] = z;
        init(y, x);
    }
}

void solve(const int& x, const int& p) {
    unsigned int c_ret = x == 0? 0: c;
    int max_e = e[x];
    for(auto& [y, z]: to[x])
        if (y != p) max_e = max(max_e, e[y]);
    for(int i = pos[e[x]]; i < pos[max_e]; ++i)
        f[x][i - pos[e[x]]] = 4e9;

    for(auto& [y, z]: to[x]) if (y != p) {
        solve(y, x);
        for(int i = pos[max_e]; i < val.size(); ++i) {
            f[x][i - pos[e[x]]] += f[y][i - pos[e[y]]];
        }
        c_ret += g[y] + c;
    }
    for(int i = pos[e[x]]; i < val.size(); ++i) {
        f[x][i - pos[e[x]]] = min(f[x][i - pos[e[x]]], c_ret) + val[i] - e[x];
        g[x] = min(g[x], f[x][i - pos[e[x]]]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen("input.txt", "r", stdin);
    cin >> n >> c;
    to = vector<vector<pair<int, int>>>(n);
    val.reserve(n);
    for(int i = 0; i < n - 1; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        --x; --y;
        to[x].emplace_back(y, z);
        to[y].emplace_back(x, z);
        val.push_back(z);
    }

    e = vector<int>(n);
    init(0, -1);

    sort(val.begin(), val.end());
    pos = vector<int>(*max_element(val.begin(), val.end())+ 1);
    for(int i = 0; i < val.size(); ++i)
        pos[val[i]] = i;
    e[0] = val[0];

    f = vector<vector<unsigned int>>(n);
    g = vector<unsigned int> (n, 4e9);
    for(int i = 0; i < n; ++i) {
        f[i] = vector<unsigned int>(val.size() - pos[e[i]], 0);
    }

    solve(0, -1);
    unsigned int ret = 4e9;
    for(int i = pos[e[0]]; i < val.size(); ++i) {
        ret = min(ret, f[0][i - pos[e[0]]] - val[i] + e[0]);
    }
    cout << ret << endl;
    return 0;
}

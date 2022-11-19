#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen("input.txt", "r", stdin);
    int r, c;
    cin >> r >> c;

    vector<int> fret;
    auto dis = [&r, &c](const int& i, const int& j) {
        int center_i = r / 2 + (r&1 || i > r / 2 - 1) - 1;
        int center_j = c / 2 + (c&1 || j > c / 2 - 1) - 1;
        return abs(i - center_i) + abs(j - center_j);
    };

    for(int i = 0; i < c; ++i) {
        long long lo = (long long)i * r;
        long long hi = ((long long)i + 1) * r - 1;

        int ret_i, ret_j;
        long long ret_index;
        ret_i = -1;
        bool dup = false;
        for(int j = lo / c; j <= hi / c; ++j) {
            long long index = (long long)i * r + j;
            int row = index / c;
            if (row == j) {
                if (ret_i != -1)
                    dup = true;
                ret_i = j;
                ret_j = index % c;
                ret_index = index;
            }
        }
        if (dup) continue;

        function<int(long long)> solve = [&solve, &ret_index, &i, &r, &c](const long long& index) {
            if (index == ret_index)
                return 0;
            return solve((long long)i * r + index / c) + 1;
        };

        int ret = max(solve(lo) + (lo / c > 0), solve(hi) + (hi / c < r - 1));
        if (fret.empty()
            || dis(fret[1], fret[2]) > dis(ret_i, ret_j)
            || dis(fret[1], fret[2]) == dis(ret_i, ret_j) && fret[0] > i) {
            fret = {i, ret_i, ret_j, ret};
        }
    }
    cout << fret[0] + 1 << " " << fret[1] + 1 << " " << fret[2] + 1 << " " << fret[3] << endl;

    return 0;
}

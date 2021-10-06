#include "bits/stdc++.h"
#define For(i, a, b) for(int i = a; i <= b; i++)
#define Ford(i, a, b) for(int i = a; i >= b; i--)
 
using namespace std;
const int N = 2e5 + 1067, M = 1e5 + 1067;
int t;
long long r, c;

pair<int, int> getRC(long long pos) {
    int row = (pos - 1) / c + 1;
    int col = pos - c * (row - 1);
    return make_pair(row, col);
}

int getStep(int p) {
    int lo = 1;
    int hi = r;
    int result = 0;
    long long startPos = (p - 1) * r + 1;
    while (lo != hi) {
        pair<int, int> startRC = getRC(startPos + lo - 1); 
        pair<int, int> endRC = getRC(startPos + hi - 1); 
        if (lo == startRC.first && hi == endRC.first) break;
        result += 1;
        lo = startRC.first; hi = endRC.first;
    }
    return result + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);;

    // cin >> t;
    t = 1;
    For(test, 1, t) {
        cin >> r >> c;
        vector<pair<int, int> > centerPos;
        if (r % 2) {
            if (c % 2) {
                centerPos.push_back(make_pair(r / 2 + 1, c / 2 + 1));
            } else {
                centerPos.push_back(make_pair(r / 2 + 1, c / 2));
                centerPos.push_back(make_pair(r / 2 + 1, c / 2 + 1));
            }
        } else {
            if (c % 2) {
                centerPos.push_back(make_pair(r / 2, c / 2 + 1));
                centerPos.push_back(make_pair(r / 2 + 1, c / 2 + 1));
            } else {
                centerPos.push_back(make_pair(r / 2 + 1, c / 2));
                centerPos.push_back(make_pair(r / 2 + 1, c / 2 + 1));
                centerPos.push_back(make_pair(r / 2, c / 2 + 1));
                centerPos.push_back(make_pair(r / 2 + 1, c / 2));
            }
        }
        int curRow = 1;
        pair<int, int> finalRC = make_pair(-1, -1);
        int finalDistance = r + c;
        int finalP = -1;
        int finalStep = -1;
        For(p, 1, c) {
            long long startPos = r * (p - 1) + 1;
            while (true) {
                if (curRow == 7) break;
                long long curPos = startPos + curRow - 1;
                pair<int, int> curRC = getRC(curPos);
                // cout << curRow << " " << curPos << " " << curRC.first << endl;
                if (curRC.first > curRow) curRow += 1; else break;
            }
            if (curRow <= r) {
                pair<int, int> rc = getRC(startPos + curRow);
                if (rc.first == curRow + 1) {
                     continue; 
                }
            }
            pair<int, int> rc = getRC(startPos + curRow - 1);
            int distance = r + c;
            for (auto pr: centerPos) {
                distance = min(abs(rc.first- pr.first) + abs(rc.second - pr.second), distance);
            }
            if (distance < finalDistance) {
                finalDistance = distance;
                finalRC = rc; 
                finalP = p;
            }


        }
        finalStep = getStep(finalP); 
        cout << finalP << " " << finalRC.first << " " << finalRC.second << " " << finalStep << endl;
    }
}

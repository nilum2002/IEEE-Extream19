#include <bits/stdc++.h>
using namespace std;

int find(vector<int> &p, int x) {
    if (p[x] == x) return x;
    return p[x] = find(p, p[x]);
}

void union_sets(vector<int> &p, int x, int y) {
    x = find(p, x);
    y = find(p, y);
    if (x != y) p[x] = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int M;
        cin >> M;
        vector<pair<int, int>> domino(M);
        for (int i = 0; i < M; i++) {
            int x, y;
            cin >> x >> y;
            domino[i] = {x, y};
        }
        long long ans = 0;
        int NN = 1 << M;
        for (int mask = 1; mask < NN; mask++) {
            vector<int> deg(8, 0);
            vector<int> p(8);
            for (int i = 1; i <= 7; i++) p[i] = i;
            int used = 0;
            for (int b = 0; b < M; b++) if (mask & (1 << b)) {
                int x = domino[b].first, y = domino[b].second;
                deg[x]++;
                deg[y]++;
                union_sets(p, x, y);
                used |= (1 << (x - 1)) | (1 << (y - 1));
            }
            int odd = 0;
            for (int i = 0; i < 7; i++) if (used & (1 << i)) if (deg[i + 1] % 2) odd++;
            if (odd != 0 && odd != 2) continue;
            int comp = 0;
            for (int i = 0; i < 7; i++) if (used & (1 << i)) if (find(p, i + 1) == i + 1) comp++;
            if (comp == 1) ans++;
        }
        cout << ans << '\n';
    }
    return 0;
}
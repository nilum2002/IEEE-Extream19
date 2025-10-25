#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& parent, int i) {
    if (parent[i] != i) parent[i] = find(parent, parent[i]);
    return parent[i];
}

void unite(vector<int>& parent, vector<int>& rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    if (xroot == yroot) return;
    if (rank[xroot] < rank[yroot]) parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot]) parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int M;
        cin >> M;
        vector<pair<int, int>> d(M);
        for (int i = 0; i < M; ++i) {
            cin >> d[i].first >> d[i].second;
        }
        int ans = 0;
        for (int mask = 1; mask < (1 << M); ++mask) {
            vector<int> degree(8, 0);
            vector<int> parent(8);
            vector<int> rank(8, 0);
            set<int> used;
            for (int i = 1; i <= 7; ++i) parent[i] = i;
            for (int i = 0; i < M; ++i) {
                if (mask & (1 << i)) {
                    int x = d[i].first, y = d[i].second;
                    degree[x]++;
                    degree[y]++;
                    used.insert(x);
                    used.insert(y);
                    unite(parent, rank, x, y);
                }
            }
            int odd = 0;
            for (int i = 1; i <= 7; ++i) {
                if (degree[i] % 2 == 1) odd++;
            }
            if (odd > 2) continue;
            if (used.empty()) continue;
            int root = find(parent, *used.begin());
            bool conn = true;
            for (int v : used) {
                if (find(parent, v) != root) {
                    conn = false;
                    break;
                }
            }
            if (conn) ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
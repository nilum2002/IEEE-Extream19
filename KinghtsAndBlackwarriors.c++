#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int LOG = 20;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<int> color(N + 1);
    for (int i = 1; i <= N; i++) cin >> color[i];
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // Compute D: distance to nearest white
    vector<int> D(N + 1, -1);
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (color[i] == 1) {
            D[i] = 0;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (D[v] == -1) {
                D[v] = D[u] + 1;
                q.push(v);
            }
        }
    }
    // Root at 1, compute depths and parents
    vector<int> dep(N + 1, 0);
    vector<int> parent(N + 1, 0);
    vector<bool> vis(N + 1, false);
    queue<int> qq;
    qq.push(1);
    dep[1] = 0;
    parent[1] = 0;
    vis[1] = true;
    while (!qq.empty()) {
        int u = qq.front();
        qq.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                parent[v] = u;
                dep[v] = dep[u] + 1;
                qq.push(v);
            }
        }
    }
    // Binary lifting for ancestors and min_up
    vector<vector<int>> up(N + 1, vector<int>(LOG, 0));
    vector<vector<int>> minup(N + 1, vector<int>(LOG, INF));
    for (int i = 1; i <= N; i++) {
        up[i][0] = parent[i];
        if (parent[i] != 0) {
            minup[i][0] = min(D[i], D[parent[i]]);
        } else {
            minup[i][0] = D[i];
        }
    }
    for (int k = 1; k < LOG; k++) {
        for (int i = 1; i <= N; i++) {
            int mid = up[i][k - 1];
            if (mid != 0) {
                up[i][k] = up[mid][k - 1];
                minup[i][k] = min(minup[i][k - 1], minup[mid][k - 1]);
            }
        }
    }
    // LCA function
    auto lcaf = [&](int uu, int vv) -> int {
        int u = uu, v = vv;
        if (dep[u] > dep[v]) swap(u, v);
        int diff = dep[v] - dep[u];
        for (int k = 0; k < LOG; k++) {
            if (diff & (1 << k)) {
                v = up[v][k];
            }
        }
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[u][k] != up[v][k]) {
                u = up[u][k];
                v = up[v][k];
            }
        }
        return up[u][0];
    };
    // Get min from desc to anc inclusive
    auto getmin = [&](int desc, int anc) -> int {
        if (desc == anc) return D[anc];
        int res = INF;
        int diff = dep[desc] - dep[anc];
        int cur = desc;
        for (int k = 0; k < LOG; k++) {
            if (diff & (1 << k)) {
                res = min(res, minup[cur][k]);
                cur = up[cur][k];
            }
        }
        res = min(res, D[anc]);
        return res;
    };
    // Process queries
    for (int i = 0; i < Q; i++) {
        int u, v;
        cin >> u >> v;
        int l = lcaf(u, v);
        int m1 = getmin(u, l);
        int m2 = getmin(v, l);
        int ans = min(m1, m2);
        cout << ans << '\n';
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

struct Edge {
    int u, v, r;
    ll w;
};

bool cmp(const Edge& a, const Edge& b) {
    return a.r < b.r;
}

struct DSU {
    vector<int> p, rankk;
    DSU(int n) {
        p.resize(n + 1);
        rankk.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool union_set(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rankk[x] < rankk[y]) swap(x, y);
        p[y] = x;
        if (rankk[x] == rankk[y]) ++rankk[x];
        return true;
    }
};

int main() {

    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, M;
        cin >> N >> M;
        vector<Edge> edges(M);
        for (int i = 0; i < M; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w >> edges[i].r;
        }
        vector<Edge> sorted_edges = edges;
        sort(sorted_edges.begin(), sorted_edges.end(), cmp);

        DSU dsu(N);
        int min_maxR = -1;
        for (auto& e : sorted_edges) {
            dsu.union_set(e.u, e.v);
            if (dsu.find(1) == dsu.find(N)) {
                min_maxR = e.r;
                break;
            }
        }

        if (min_maxR == -1) {
            cout << -1 << endl;
            continue;
        }

        vector<vector<pair<int, ll>>> adj(N + 1);
        for (auto& e : edges) {
            if (e.r <= min_maxR) {
                adj[e.u].push_back({e.v, e.w});
                adj[e.v].push_back({e.u, e.w});
            }
        }

        vector<ll> dist(N + 1, 1LL << 60); // Large INF
        dist[1] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        pq.push({0, 1});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        ll totalT = dist[N];
        if (totalT >= (1LL << 60)) {
            cout << -1 << endl;
        } else {
            cout << min_maxR << " " << totalT << endl;
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;

const ull BASE = 911382323ULL;
const ull MOD = (1ULL << 61) - 1;

ull modmul(ull a, ull b) {
    __uint128_t res = (__uint128_t)a * b;
    res = (res >> 61) + (res & MOD);
    if (res >= MOD) res -= MOD;
    return res;
}

ull modadd(ull a, ull b) {
    ull res = a + b;
    if (res >= MOD) res -= MOD;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ull> subtree_hash(N + 1);

    function<ull(int, int)> compute_hash = [&](int u, int p) -> ull {
        vector<ull> ch;
        for (int v : adj[u]) {
            if (v != p) {
                ch.push_back(compute_hash(v, u));
            }
        }
        sort(ch.begin(), ch.end());
        ull h = 1237ULL;
        for (auto c : ch) {
            h = modadd(modmul(h, BASE), c);
        }
        subtree_hash[u] = h;
        return h;
    };

    compute_hash(1, -1);

    ll ans = 0;

    function<void(int, int, bool)> count_unique = [&](int u, int p, bool path_unique) {
        if (path_unique) ++ans;
        vector<pair<ull, int>> child_list;
        for (int v : adj[u]) {
            if (v != p) {
                child_list.emplace_back(subtree_hash[v], v);
            }
        }
        if (child_list.empty()) return;
        sort(child_list.begin(), child_list.end());
        int i = 0;
        int sz = child_list.size();
        while (i < sz) {
            int j = i;
            ull curr_h = child_list[i].first;
            while (j < sz && child_list[j].first == curr_h) ++j;
            int mult = j - i;
            bool child_uni = path_unique && (mult == 1);
            for (int k = i; k < j; ++k) {
                int v = child_list[k].second;
                count_unique(v, u, child_uni);
            }
            i = j;
        }
    };

    count_unique(1, -1, true);

    cout << ans << "\n";
    return 0;
}
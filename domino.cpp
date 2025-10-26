#include <bits/stdc++.h>
using namespace std;

long long ans;
// Stores the K distinct domino types and their counts
vector<pair<pair<int, int>, int>> domino_counts;
int K; // Number of distinct types (K <= 21)

// Use std::array for fast stack-based copies
using DsuArray = array<int, 8>;
using DegArray = array<int, 8>;

// Find with path compression (safe since we copy the array)
int find(DsuArray &p, int x) {
    if (p[x] == x) return x;
    return p[x] = find(p, p[x]);
}

void union_sets(DsuArray &p, int x, int y) {
    x = find(p, x);
    y = find(p, y);
    if (x != y) p[x] = y;
}

bool is_valid(DsuArray &p, DegArray &deg) {
    int odd = 0;
    int nodes_used = 0;
    for (int i = 1; i <= 7; i++) {
        if (deg[i] > 0) {
            nodes_used++;
            if (deg[i] % 2) {
                odd++;
            }
        }
    }
    
    // Check for non-empty set
    if (nodes_used == 0) {
        return false;
    }
    
    // Check degrees
    if (odd != 0 && odd != 2) {
        return false;
    }
    
    // Check connectivity
    int root = -1;
    for (int i = 1; i <= 7; i++) {
        if (deg[i] > 0) {
            if (root == -1) {
                root = find(p, i);
            } else if (find(p, i) != root) {
                return false; // Not connected
            }
        }
    }
    
    return true;
}

// Recurse on K types, passing arrays by value (fast copy)
void solve(int type_idx, DsuArray p, DegArray deg) {
    if (type_idx == K) {
        if (is_valid(p, deg)) {
            ans++;
        }
        return;
    }
    
    auto& dom_info = domino_counts[type_idx];
    int x = dom_info.first.first;
    int y = dom_info.first.second;
    int max_k = dom_info.second; 
    
    // Branch 1: Use k=0
    solve(type_idx + 1, p, deg);
    
    // Branch 2: Use k=1 (represents all ODD k)
    if (max_k >= 1) {
        DsuArray next_p = p;
        DegArray next_deg = deg;
        
        next_deg[x]++;
        next_deg[y]++;
        union_sets(next_p, x, y);
        
        solve(type_idx + 1, next_p, next_deg);
    }
    
    // Branch 3: Use k=2 (represents all non-zero EVEN k)
    if (max_k >= 2) {
        DsuArray next_p = p;
        DegArray next_deg = deg;
        
        next_deg[x] += 2;
        next_deg[y] += 2;
        union_sets(next_p, x, y);
        
        solve(type_idx + 1, next_p, next_deg);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    while (T--) {
        int M;
        cin >> M;
        
        map<pair<int, int>, int> counts;
        for (int i = 0; i < M; i++) {
            int x, y;
            cin >> x >> y;
            if (x > y) swap(x, y);
            counts[{x, y}]++;
        }
        
        domino_counts.clear();
        for (auto const& [pair, count] : counts) {
            domino_counts.push_back({pair, count});
        }
        K = domino_counts.size(); // K <= 21
        
        ans = 0;
        DsuArray p;
        DegArray deg;
        deg.fill(0);
        for (int i = 1; i <= 7; i++) p[i] = i;
        
        solve(0, p, deg);
        
        cout << ans << '\n';
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<vector<pair<int, ll>>> adj(N + 1);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  // Precompute LCA with sparse table
  int LOG = 19; // log2(2*3e5) ~18
  vector<ll> d(N + 1, 0);
  vector<int> dep(N + 1, 0);
  vector<int> tour;
  vector<int> dep_tour;
  vector<int> first_occ(N + 1, -1);
  function<void(int, int, ll, int)> dfs_tour = [&](int u, int p, ll dist, int depth) {
    first_occ[u] = tour.size();
    tour.push_back(u);
    dep_tour.push_back(depth);
    d[u] = dist;
    dep[u] = depth;
    for (auto [v, w] : adj[u]) {
      if (v != p) {
        dfs_tour(v, u, dist + w, depth + 1);
        tour.push_back(u);
        dep_tour.push_back(depth);
      }
    }
  };
  dfs_tour(1, -1, 0, 0);
  int tour_sz = tour.size();
  vector<vector<int>> st(LOG, vector<int>(tour_sz));
  for (int i = 0; i < tour_sz; ++i) {
    st[0][i] = i;
  }
  for (int k = 1; k < LOG; ++k) {
    for (int i = 0; i + (1 << k) <= tour_sz; ++i) {
      int idx1 = st[k - 1][i];
      int idx2 = st[k - 1][i + (1 << (k - 1))];
      st[k][i] = (dep_tour[idx1] < dep_tour[idx2] ? idx1 : idx2);
    }
  }
  auto get_lca = [&](int u, int v) -> int {
    int L = first_occ[u], R = first_occ[v];
    if (L > R) swap(L, R);
    int len = R - L + 1;
    int k = 31 - __builtin_clz(len);
    int idx1 = st[k][L];
    int idx2 = st[k][R - (1 << k) + 1];
    int min_idx = (dep_tour[idx1] < dep_tour[idx2] ? idx1 : idx2);
    return tour[min_idx];
  };
  auto get_dist = [&](int u, int v) -> ll {
    int l = get_lca(u, v);
    return d[u] + d[v] - 2 * d[l];
  };

  // For blocks
  const int B = 1800;
  vector<int> A;
  vector<vector<ll>> block_fs;
  int current_fixed = 0;

  // DP arrays
  vector<ll> down(N + 1);
  vector<ll> f(N + 1);
  function<void(int, int, const vector<bool>&)> dfs1 = [&](int u, int p, const vector<bool>& is_target) {
    down[u] = is_target[u] ? 0 : -INF;
    for (auto [v, w] : adj[u]) {
      if (v != p) {
        dfs1(v, u, is_target);
        down[u] = max(down[u], down[v] + w);
      }
    }
  };
  function<void(int, int, ll, const vector<bool>&)> dfs2 = [&](int u, int p, ll up_from_p, const vector<bool>& is_target) {
    f[u] = max(down[u], up_from_p);
    // Prepare child maxes
    ll max1 = -INF, max2 = -INF;
    int child_with_max1 = -1;
    vector<pair<int, ll>> children;
    for (auto [v, w] : adj[u]) {
      if (v != p) {
        children.emplace_back(v, w);
        ll val = down[v] + w;
        if (val > max1) {
          max2 = max1;
          max1 = val;
          child_with_max1 = v;
        } else if (val > max2) {
          max2 = val;
        }
      }
    }
    // For each child
    for (auto [c, w] : children) {
      ll max_sib = (c == child_with_max1 ? max2 : max1);
      ll max_out = max({up_from_p, max_sib, is_target[u] ? 0LL : -INF});
      ll up_for_c = (max_out > -INF / 2 ? max_out + w : -INF);
      dfs2(c, u, up_for_c, is_target);
    }
  };

  int M;
  cin >> M;
  ll last_ans = 0;
  for (int qi = 0; qi < M; ++qi) {
    int type;
    cin >> type;
    if (type == 1) {
      int x_enc;
      cin >> x_enc;
      int x = ((x_enc ^ abs(last_ans)) % N) + 1;
      A.push_back(x);
      if (A.size() - current_fixed == B) {
        // Compute f for this block
        vector<bool> is_target(N + 1, false);
        set<int> uniq;
        for (size_t i = current_fixed; i < A.size(); ++i) {
          uniq.insert(A[i]);
        }
        for (int v : uniq) is_target[v] = true;
        dfs1(1, -1, is_target);
        dfs2(1, -1, -INF, is_target);
        vector<ll> this_f(N + 1);
        for (int i = 1; i <= N; ++i) {
          this_f[i] = f[i];
        }
        block_fs.push_back(move(this_f));
        current_fixed = A.size();
      }
    } else if (type == 2) {
      if (!A.empty()) {
        A.pop_back();
        if (A.size() < current_fixed) {
          block_fs.pop_back();
          current_fixed -= B;
        }
      }
    } else if (type == 3) {
      int l_enc, r_enc, x_enc;
      cin >> l_enc >> r_enc >> x_enc;
      int sz = A.size();
      if (sz == 0) {
        // Should not happen, but
        cout << 0 << '\n';
        last_ans = 0;
        continue;
      }
      ll abs_last = abs(last_ans);
      int x = ((x_enc ^ abs_last) % N) + 1;
      int l = ((l_enc ^ abs_last) % sz) + 1;
      int r = ((r_enc ^ abs_last) % sz) + 1;
      if (l > r) swap(l, r);
      // Now compute max dist(x, A[i-1]) for i=l to r
      int left = l - 1, rite = r - 1;
      ll query_ans = -INF;
      // Handle fixed part [left, rite] cap [0, current_fixed-1]
      int fixed_left = max(left, 0);
      int fixed_rite = min(rite, current_fixed - 1);
      if (fixed_left <= fixed_rite) {
        int first_bk = fixed_left / B;
        int last_bk = fixed_rite / B;
        if (first_bk == last_bk) {
          // loop all
          for (int i = fixed_left; i <= fixed_rite; ++i) {
            query_ans = max(query_ans, get_dist(x, A[i]));
          }
        } else {
          // partial start: fixed_left to (first_bk +1)*B -1
          int end_start_p = min(fixed_rite, (first_bk + 1) * B - 1);
          for (int i = fixed_left; i <= end_start_p; ++i) {
            query_ans = max(query_ans, get_dist(x, A[i]));
          }
          // partial end: last_bk * B to fixed_rite
          int start_end_p = max(fixed_left, last_bk * B);
          for (int i = start_end_p; i <= fixed_rite; ++i) {
            query_ans = max(query_ans, get_dist(x, A[i]));
          }
          // full blocks first_bk+1 to last_bk-1
          for (int bk = first_bk + 1; bk < last_bk; ++bk) {
            query_ans = max(query_ans, block_fs[bk][x]);
          }
        }
      }
      // Handle suffix part [max(left, current_fixed), rite]
      int suffix_left = max(left, current_fixed);
      if (suffix_left <= rite) {
        for (int i = suffix_left; i <= rite; ++i) {
          query_ans = max(query_ans, get_dist(x, A[i]));
        }
      }
      cout << query_ans << '\n';
      last_ans = query_ans;
    }
  }

  return 0;
}
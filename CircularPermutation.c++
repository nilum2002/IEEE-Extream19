#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> cur(N + 1);
  for (int i = 0; i < N; ++i) {
    int h;
    cin >> h;
    cur[h] = i;
  }
  int low = 0, high = (N - 1) / 2;
  int ans = high;
  while (low <= high) {
    int mid = (low + high) / 2;
    bool ok = false;
    for (int orient = 0; orient < 2; ++orient) {
      ll L = 2LL * mid + 1;
      ll KK = N - L;
      vector<pair<ll, ll>> inters;
      for (int k = 1; k <= N; ++k) {
        ll offset = k - 1LL;
        ll ck = (cur[k] + (orient == 0 ? -offset : +offset) + 2LL * N) % N;
        ll start_all = (ck - mid + 2LL * N) % N;
        ll end_all = (start_all + L - 1) % N;
        ll start_forb = (end_all + 1) % N;
        if (KK <= 0) continue;
        ll end_forb = (start_forb + KK - 1) % N;
        if (start_forb <= end_forb) {
          inters.emplace_back(start_forb, end_forb);
        } else {
          inters.emplace_back(start_forb, N - 1LL);
          inters.emplace_back(0LL, end_forb);
        }
      }
      sort(inters.begin(), inters.end());
      vector<pair<ll, ll>> mrg;
      for (auto p : inters) {
        ll l = p.first, r = p.second;
        if (mrg.empty() || mrg.back().second + 1 < l) {
          mrg.push_back(p);
        } else {
          mrg.back().second = max(mrg.back().second, r);
        }
      }
      ll tot = 0;
      for (auto p : mrg) {
        tot += p.second - p.first + 1;
      }
      if (tot < N) {
        ok = true;
        break;
      }
    }
    if (ok) {
      ans = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  cout << ans << '\n';
  return 0;
}
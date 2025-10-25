#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int N = 1000000;
  vector<int> spf(N + 1);
  for (int i = 0; i <= N; ++i) spf[i] = i;
  for (int i = 2; i * i <= N; ++i) {
    if (spf[i] == i) {
      for (int j = i * i; j <= N; j += i) {
        if (spf[j] == j) spf[j] = i;
      }
    }
  }

  vector<char> is_prime(N + 1, 1);
  is_prime[0] = is_prime[1] = 0;
  for (int i = 2; i <= N; ++i) {
    if (spf[i] == i) is_prime[i] = 1;
    else is_prime[i] = 0;
  }

  vector<int> primes;
  for (int i = 2; i <= N; ++i) {
    if (is_prime[i]) primes.push_back(i);
  }

  unordered_map<int, int> pidx;
  for (size_t i = 0; i < primes.size(); ++i) {
    pidx[primes[i]] = i;
  }

  vector<vector<int>> belongs(N + 1);
  for (int k = 2; k <= N; ++k) {
    set<int> distinct_pf;
    int temp = k;
    while (temp > 1) {
      int p = spf[temp];
      distinct_pf.insert(p);
      temp /= p;
    }
    for (int p : distinct_pf) {
      ll other = (ll)k / p;
      if (other > 1 && is_prime[other]) {
        auto it = pidx.find(p);
        if (it != pidx.end()) {
          belongs[k].push_back(it->second);
        }
      }
    }
  }

  int T;
  cin >> T;

  struct Query {
    int l, r, idx;
  };
  vector<Query> queries;
  for (int i = 0; i < T; ++i) {
    int L, R;
    cin >> L >> R;
    queries.push_back({L, R, i});
  }

  int QQ = T;
  int block_size = max(1, (int)(N / sqrt(QQ)));
  sort(queries.begin(), queries.end(), [block_size](const Query& a, const Query& b) {
    int ba = a.l / block_size;
    int bb = b.l / block_size;
    if (ba != bb) return ba < bb;
    return a.r < b.r;
  });

  vector<ll> answers(T);
  ll cur_ans = 0;
  int cur_l = 1, cur_r = 0;
  vector<int> cnt(primes.size(), 0);

  auto add = [&](int pos) {
    for (int gid : belongs[pos]) {
      int old = cnt[gid];
      cnt[gid]++;
      cur_ans += old;
    }
  };

  auto rem = [&](int pos) {
    for (int gid : belongs[pos]) {
      int old = cnt[gid];
      cnt[gid]--;
      cur_ans -= (old - 1);
    }
  };

  for (auto& q : queries) {
    int tl = q.l, tr = q.r;
    while (cur_r < tr) {
      ++cur_r;
      add(cur_r);
    }
    while (cur_l > tl) {
      --cur_l;
      add(cur_l);
    }
    while (cur_r > tr) {
      rem(cur_r);
      --cur_r;
    }
    while (cur_l < tl) {
      rem(cur_l);
      ++cur_l;
    }
    answers[q.idx] = cur_ans;
  }

  for (int i = 0; i < T; ++i) {
    cout << answers[i] << '\n';
  }

  return 0;
}
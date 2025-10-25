#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1000000007;

ll modpow(ll a, ll b, ll mod) {
  ll res = 1;
  while (b) {
    if (b & 1) res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int M;
  cin >> M;
  ll inv6 = modpow(6, MOD - 2, MOD);
  for (int N = 1; N <= M; ++N) {
    ll n2 = (ll)N * N % MOD;
    ll n3 = n2 * N % MOD;
    ll term1 = n3;
    ll term2 = 3LL * n2 % MOD;
    ll term3 = 8LL * N % MOD;
    ll res = (term1 - term2 + MOD) % MOD;
    res = (res + term3) % MOD;
    res = res * inv6 % MOD;
    cout << res << (N == M ? '\n' : ' ');
  }
  return 0;
}
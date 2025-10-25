#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 998244353;

ll modpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        if (N % 2 == 0) {
            cout << 0 << '\n';
        } else {
            ll inv = modpow(N, MOD - 2, MOD);
            cout << inv << '\n';
        }
    }
    return 0;
}
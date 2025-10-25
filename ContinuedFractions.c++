#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 lll;

const ll MOD = 998244353;

ll add(ll a, ll b) {
    ll res = a + b;
    return res >= MOD ? res - MOD : res;
}

ll sub(ll a, ll b) {
    ll res = a - b;
    return res < 0 ? res + MOD : res;
}

ll mul(ll a, ll b) {
    return (lll)a * b % MOD;
}

ll modpow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = mul(res, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return res;
}

vector<ll> batch_inverse(const vector<ll>& vals) {
    int n = vals.size();
    vector<ll> pref(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = mul(pref[i - 1], vals[i - 1]);
    }
    ll p_inv = modpow(pref[n], MOD - 2);
    vector<ll> suff(n + 2, 1);
    for (int i = n; i >= 1; --i) {
        suff[i] = mul(suff[i + 1], vals[i - 1]);
    }
    vector<ll> res(n);
    for (int i = 1; i <= n; ++i) {
        res[i - 1] = mul(p_inv, mul(pref[i - 1], suff[i + 1]));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N, M;
    cin >> N >> M;
    vector<ll> orig(N);
    ll sum_orig = 0;
    for (auto &x : orig) {
        cin >> x;
        sum_orig = add(sum_orig, x);
    }
    ll A = 1, B = 0, C = 0, D = 1;
    ll cur_sum1 = 0;
    ll last_c = -1;
    ll last_d = -1;
    for (ll qi = 0; qi < M; ++qi) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll X;
            cin >> X;
            A = add(A, mul(X, C));
            B = add(B, mul(X, D));
        } else {
            swap(A, C);
            swap(B, D);
        }
        ll cur_sum;
        if (C == 0) {
            ll temp = add(mul(A, sum_orig), mul(N % MOD, B));
            ll inv_D = modpow(D, MOD - 2);
            cur_sum = mul(temp, inv_D);
        } else {
            bool need_comp = (last_c != C || last_d != D);
            if (need_comp) {
                vector<ll> dens(N);
                for (int i = 0; i < N; i++) {
                    dens[i] = add(mul(C, orig[i]), D);
                }
                vector<ll> invs = batch_inverse(dens);
                ll s1 = 0;
                for (ll v : invs) {
                    s1 = add(s1, v);
                }
                cur_sum1 = s1;
                last_c = C;
                last_d = D;
            }
            ll inv_C = modpow(C, MOD - 2);
            ll temp = sub(N % MOD, mul(D, cur_sum1));
            ll sum2 = mul(inv_C, temp);
            cur_sum = add(mul(A, sum2), mul(B, cur_sum1));
        }
        cout << cur_sum << '\n';
    }
    return 0;
}
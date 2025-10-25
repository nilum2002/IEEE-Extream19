#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128;

const ll MOD = 998244353;

inline ll addmod(ll a, ll b) { ll r = a + b; return r >= MOD ? r - MOD : r; }
inline ll submod(ll a, ll b) { ll r = a - b; return r < 0 ? r + MOD : r; }
inline ll mulmod(ll a, ll b) { return (lll)a * b % MOD; }

ll modpow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = mulmod(res, base);
        base = mulmod(base, base);
        exp >>= 1;
    }
    return res;
}

static vector<ll> dens, pref, suff;
static vector<ll> uvals;
static vector<int> ucnt;

inline ll compute_sum1(int U, ll C, ll D) {
    for (int i = 0; i < U; ++i) {
        dens[i] = addmod(mulmod(C, uvals[i]), D);
    }

    pref[0] = 1;
    for (int i = 0; i < U; ++i) {
        pref[i + 1] = mulmod(pref[i], dens[i]);
    }

    ll totalProdInv = modpow(pref[U], MOD - 2);

    suff[U] = 1;
    for (int i = U - 1; i >= 0; --i) {
        suff[i] = mulmod(suff[i + 1], dens[i]);
    }

    ll s1 = 0;
    for (int i = 0; i < U; ++i) {
        ll inv = mulmod(totalProdInv, mulmod(pref[i], suff[i + 1]));
        s1 = addmod(s1, mulmod(inv, (ll)ucnt[i]));
    }
    
    return s1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    
    vector<ll> orig(N);
    ll sum_orig = 0;
    for (int i = 0; i < N; ++i) {
        ll x; cin >> x;
        x %= MOD;
        if (x < 0) x += MOD;
        orig[i] = x;
        sum_orig = addmod(sum_orig, x);
    }

    sort(orig.begin(), orig.end());
    
    uvals.reserve(N);
    ucnt.reserve(N);
    
    for (int i = 0; i < N; ) {
        int j = i;
        while (j < N && orig[j] == orig[i]) ++j;
        uvals.push_back(orig[i]);
        ucnt.push_back(j - i);
        i = j;
    }
    int U = (int)uvals.size();

    dens.resize(U);
    pref.resize(U + 1);
    suff.resize(U + 1);

    // Cache for (C,D) -> sum1 mapping
    unordered_map<ll, ll> cache_sum1;
    cache_sum1.reserve(M);
    
    // Cache for inverses
    unordered_map<ll, ll> inv_cache;
    inv_cache.reserve(M * 2);

    ll A = 1, B = 0, C = 0, D = 1;
    ll N_mod = N % MOD;

    // String buffer for output
    string output;
    output.reserve(M * 15);

    for (int qi = 0; qi < M; ++qi) {
        int type; cin >> type;
        if (type == 1) {
            ll X; cin >> X; 
            X %= MOD;
            if (X < 0) X += MOD;
            A = addmod(A, mulmod(X, C));
            B = addmod(B, mulmod(X, D));
        } else {
            swap(A, C);
            swap(B, D);
        }

        ll cur_sum;
        if (C == 0) {
            ll invD;
            auto it_inv = inv_cache.find(D);
            if (it_inv != inv_cache.end()) {
                invD = it_inv->second;
            } else {
                invD = modpow(D, MOD - 2);
                inv_cache[D] = invD;
            }
            ll temp = addmod(mulmod(A, sum_orig), mulmod(N_mod, B));
            cur_sum = mulmod(temp, invD);
        } else {
            // Use single key for (C,D) pair
            ll key = ((lll)C * MOD + D) % (1LL << 60);
            
            auto it = cache_sum1.find(key);
            ll cur_sum1;
            
            if (it != cache_sum1.end()) {
                cur_sum1 = it->second;
            } else {
                cur_sum1 = compute_sum1(U, C, D);
                cache_sum1[key] = cur_sum1;
            }

            ll invC;
            auto it_inv = inv_cache.find(C);
            if (it_inv != inv_cache.end()) {
                invC = it_inv->second;
            } else {
                invC = modpow(C, MOD - 2);
                inv_cache[C] = invC;
            }
            
            ll temp = submod(N_mod, mulmod(D, cur_sum1));
            ll sum2 = mulmod(invC, temp);
            cur_sum = addmod(mulmod(A, sum2), mulmod(B, cur_sum1));
        }

        output += to_string(cur_sum) + '\n';
    }

    cout << output;

    return 0;
}
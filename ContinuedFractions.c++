// #include <bits/stdc++.h>
// using namespace std;

// typedef long long ll;
// typedef __int128 lll;

// const ll MOD = 998244353;

// ll add(ll a, ll b) {
//     ll res = a + b;
//     return res >= MOD ? res - MOD : res;
// }

// ll sub(ll a, ll b) {
//     ll res = a - b;
//     return res < 0 ? res + MOD : res;
// }

// ll mul(ll a, ll b) {
//     return (lll)a * b % MOD;
// }

// ll modpow(ll base, ll exp) {
//     ll res = 1;
//     while (exp) {
//         if (exp & 1) res = mul(res, base);
//         base = mul(base, base);
//         exp >>= 1;
//     }
//     return res;
// }

// vector<ll> batch_inverse(const vector<ll>& vals) {
//     int n = vals.size();
//     vector<ll> pref(n + 1, 1);
//     for (int i = 1; i <= n; ++i) {
//         pref[i] = mul(pref[i - 1], vals[i - 1]);
//     }
//     ll p_inv = modpow(pref[n], MOD - 2);
//     vector<ll> suff(n + 2, 1);
//     for (int i = n; i >= 1; --i) {
//         suff[i] = mul(suff[i + 1], vals[i - 1]);
//     }
//     vector<ll> res(n);
//     for (int i = 1; i <= n; ++i) {
//         res[i - 1] = mul(p_inv, mul(pref[i - 1], suff[i + 1]));
//     }
//     return res;
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     ll N, M;
//     cin >> N >> M;
//     vector<ll> orig(N);
//     ll sum_orig = 0;
//     for (auto &x : orig) {
//         cin >> x;
//         sum_orig = add(sum_orig, x);
//     }
//     ll A = 1, B = 0, C = 0, D = 1;
//     ll cur_sum1 = 0;
//     ll last_c = -1;
//     ll last_d = -1;
//     for (ll qi = 0; qi < M; ++qi) {
//         ll type;
//         cin >> type;
//         if (type == 1) {
//             ll X;
//             cin >> X;
//             A = add(A, mul(X, C));
//             B = add(B, mul(X, D));
//         } else {
//             swap(A, C);
//             swap(B, D);
//         }
//         ll cur_sum;
//         if (C == 0) {
//             ll temp = add(mul(A, sum_orig), mul(N % MOD, B));
//             ll inv_D = modpow(D, MOD - 2);
//             cur_sum = mul(temp, inv_D);
//         } else {
//             bool need_comp = (last_c != C || last_d != D);
//             if (need_comp) {
//                 vector<ll> dens(N);
//                 for (int i = 0; i < N; i++) {
//                     dens[i] = add(mul(C, orig[i]), D);
//                 }
//                 vector<ll> invs = batch_inverse(dens);
//                 ll s1 = 0;
//                 for (ll v : invs) {
//                     s1 = add(s1, v);
//                 }
//                 cur_sum1 = s1;
//                 last_c = C;
//                 last_d = D;
//             }
//             ll inv_C = modpow(C, MOD - 2);
//             ll temp = sub(N % MOD, mul(D, cur_sum1));
//             ll sum2 = mul(inv_C, temp);
//             cur_sum = add(mul(A, sum2), mul(B, cur_sum1));
//         }
//         cout << cur_sum << '\n';
//     }
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128;

const ll MOD = 998244353;

inline ll addmod(ll a, ll b) { ll r = a + b; return r >= MOD ? r - MOD : r; }
inline ll submod(ll a, ll b) { ll r = a - b; return r < 0 ? r + MOD : r; }
inline ll mulmod(ll a, ll b) { return (lll)a * b % MOD; }

static inline ll modpow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = mulmod(res, base);
        base = mulmod(base, base);
        exp >>= 1;
    }
    return res;
}

// Optimized hash map with better load factor and collision handling
struct FastMap {
    static constexpr uint64_t empty_key = ULLONG_MAX;
    size_t cap;
    size_t mask;
    vector<uint64_t> keys;
    vector<ll> vals;
    size_t count = 0;

    FastMap() : cap(0), mask(0) {}

    void init(size_t n) {
        size_t cap2 = 4;
        while (cap2 < n) cap2 <<= 1;
        cap = cap2;
        mask = cap - 1;
        keys.assign(cap, empty_key);
        vals.assign(cap, 0);
        count = 0;
    }

    inline ll* find(uint64_t k) {
        size_t idx = (k * 11400714819323198485ULL) >> (64 - __builtin_ctzll(cap));
        while (true) {
            uint64_t kk = keys[idx];
            if (kk == empty_key) return nullptr;
            if (kk == k) return &vals[idx];
            idx = (idx + 1) & mask;
        }
    }

    inline ll* insert(uint64_t k, ll v) {
        if ((count + 1) * 4 > cap * 3) {
            rehash(cap * 2);
        }
        size_t idx = (k * 11400714819323198485ULL) >> (64 - __builtin_ctzll(cap));
        while (true) {
            uint64_t kk = keys[idx];
            if (kk == empty_key) {
                keys[idx] = k;
                vals[idx] = v;
                ++count;
                return &vals[idx];
            }
            if (kk == k) {
                vals[idx] = v;
                return &vals[idx];
            }
            idx = (idx + 1) & mask;
        }
    }

    void rehash(size_t newcap) {
        size_t nc = 4;
        while (nc < newcap) nc <<= 1;
        vector<uint64_t> nkeys(nc, empty_key);
        vector<ll> nvals(nc, 0);
        size_t nmask = nc - 1;
        int shift = 64 - __builtin_ctzll(nc);
        for (size_t i = 0; i < cap; ++i) {
            uint64_t kk = keys[i];
            if (kk != empty_key) {
                size_t idx = (kk * 11400714819323198485ULL) >> shift;
                while (nkeys[idx] != empty_key) idx = (idx + 1) & nmask;
                nkeys[idx] = kk;
                nvals[idx] = vals[i];
            }
        }
        keys.swap(nkeys);
        vals.swap(nvals);
        cap = nc;
        mask = nmask;
    }
};

// Pre-allocate all working arrays to avoid repeated allocations
static vector<ll> dens, pref, suff, invs;

static void batch_inverse_inplace(int U, const vector<ll> &uvals, const vector<int> &ucnt, ll C, ll D) {
    // Build denominators
    for (int i = 0; i < U; ++i) {
        dens[i] = addmod(mulmod(C, uvals[i]), D);
    }

    pref[0] = 1;
    for (int i = 1; i <= U; ++i) pref[i] = mulmod(pref[i - 1], dens[i - 1]);

    ll totalProdInv = modpow(pref[U], MOD - 2);

    suff[U] = 1;
    for (int i = U - 1; i >= 0; --i) suff[i] = mulmod(suff[i + 1], dens[i]);

    for (int i = 0; i < U; ++i) {
        invs[i] = mulmod(totalProdInv, mulmod(pref[i], suff[i + 1]));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;
    
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
    
    vector<ll> uvals;
    vector<int> ucnt;
    uvals.reserve(N);
    ucnt.reserve(N);
    
    for (int i = 0; i < N; ) {
        int j = i + 1;
        while (j < N && orig[j] == orig[i]) ++j;
        uvals.push_back(orig[i]);
        ucnt.push_back(j - i);
        i = j;
    }
    int U = (int)uvals.size();

    // Pre-allocate working arrays
    dens.resize(U);
    pref.resize(U + 1);
    suff.resize(U + 1);
    invs.resize(U);

    // Initialize cache with better initial capacity
    FastMap cache;
    cache.init(max(16, M * 3));

    ll A = 1, B = 0, C = 0, D = 1;

    for (int qi = 0; qi < M; ++qi) {
        int type; cin >> type;
        if (type == 1) {
            ll X; cin >> X; X %= MOD;
            A = addmod(A, mulmod(X, C));
            B = addmod(B, mulmod(X, D));
        } else {
            swap(A, C);
            swap(B, D);
        }

        ll cur_sum;
        if (C == 0) {
            ll temp = addmod(mulmod(A, sum_orig), mulmod((ll)(N % MOD), B));
            ll invD = modpow(D, MOD - 2);
            cur_sum = mulmod(temp, invD);
        } else {
            uint64_t key = ((uint64_t)(uint32_t)C << 32) | (uint32_t)D;
            ll* pv = cache.find(key);
            ll cur_sum1;
            
            if (pv) {
                cur_sum1 = *pv;
            } else {
                batch_inverse_inplace(U, uvals, ucnt, C, D);

                ll s1 = 0;
                for (int i = 0; i < U; ++i) {
                    s1 = addmod(s1, mulmod(invs[i], (ll)ucnt[i]));
                }

                cur_sum1 = s1;
                cache.insert(key, cur_sum1);
            }

            ll invC = modpow(C, MOD - 2);
            ll temp = submod((ll)(N % MOD), mulmod(D, cur_sum1));
            ll sum2 = mulmod(invC, temp);
            cur_sum = addmod(mulmod(A, sum2), mulmod(B, cur_sum1));
        }

        cout << cur_sum << '\n';
    }

    return 0;
}

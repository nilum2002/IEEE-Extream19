// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);

//   const int N = 1000000;

  
//   vector<int> spf(N + 1, 0);
//   vector<int> primes;
//   spf[0] = 0; spf[1] = 1;
//   for (int i = 2; i <= N; ++i) {
//     if (spf[i] == 0) { spf[i] = i; primes.push_back(i); }
//     for (int p : primes) {
//       ll v = 1LL * p * i;
//       if (v > N) break;
//       spf[v] = p;
//       if (p == spf[i]) break;
//     }
//   }


//   vector<char> is_prime(N + 1, 0);
//   for (int p : primes) is_prime[p] = 1;

 
//   vector<int> pidx(N + 1, -1);
//   for (size_t i = 0; i < primes.size(); ++i) pidx[primes[i]] = (int)i;

  
//   vector<vector<int>> belongs(N + 1);
//   size_t P = primes.size();
//   for (size_t i = 0; i < P; ++i) {
//     int pi = primes[i];
//     for (size_t j = 0; j < P; ++j) {
//       ll prod = 1LL * pi * primes[j];
//       if (prod > N) break;
//       // push index of pi (matching original logic: for k = pi*pj, add pi index)
//       belongs[prod].push_back((int)i);
//     }
//   }

  
//   int T;
//   if (!(cin >> T)) return 0;
//   struct Query { int l, r, idx; };
//   vector<Query> queries;
//   queries.reserve(T);
//   for (int i = 0; i < T; ++i) {
//     int L, R; cin >> L >> R;
//     queries.push_back({L, R, i});
//   }

 
//   int block = max(1, (int)sqrt(N));
//   sort(queries.begin(), queries.end(), [block](const Query &a, const Query &b) {
//     int ba = a.l / block;
//     int bb = b.l / block;
//     if (ba != bb) return ba < bb;
//     if (ba & 1) return a.r > b.r; // odd block: descending r
//     else return a.r < b.r;        // even block: ascending r
//   });


//   vector<ll> answers(T);
//   ll cur_ans = 0;
//   int cur_l = 1, cur_r = 0;
//   vector<int> cnt(primes.size(), 0);

  
//   auto add_pos = [&](int pos) {
//     // pos might be 0 or 1: belongs[0] and belongs[1] will be empty
//     for (int gid : belongs[pos]) {
//       int old = cnt[gid];
//       cnt[gid] = old + 1;
//       cur_ans += old; // pairs formed by existing occurrences
//     }
//   };

//   auto rem_pos = [&](int pos) {
//     for (int gid : belongs[pos]) {
//       int old = cnt[gid];
//       // removing decreases number of pairs by (old - 1)
//       cnt[gid] = old - 1;
//       cur_ans -= (old - 1);
//     }
//   };

//   // process queries
//   for (auto &q : queries) {
//     int L = q.l, R = q.r;
//     while (cur_r < R) add_pos(++cur_r);
//     while (cur_r > R) rem_pos(cur_r--);
//     while (cur_l < L) rem_pos(cur_l++);
//     while (cur_l > L) add_pos(--cur_l);
//     answers[q.idx] = cur_ans;
//   }

//   // output
//   for (int i = 0; i < T; ++i) cout << answers[i] << '\n';
//   return 0;
// }
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Gilbert (Hilbert) order (recursive) for good Mo ordering
static inline long long gilbertOrder(int x, int y, int pow = 20, int rotate = 0) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    static const int rotateDelta[4] = {0, 3, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    long long subSquareSize = 1LL << (2 * pow - 2);
    long long ans = seg * subSquareSize;
    long long add = gilbertOrder(nx, ny, pow - 1, nrot);
    if (seg == 1 || seg == 2) ans += add;
    else ans += (subSquareSize - add - 1);
    return ans;
}

struct Query {
    int l, r, idx;
    long long ord;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int GLOBAL_N = 1000000; // safe cap
    int T;
    if (!(cin >> T)) return 0;

    vector<Query> queries;
    queries.reserve(T);
    int minL = INT_MAX, maxR = 0;
    for (int i = 0; i < T; ++i) {
        int L, R; cin >> L >> R;
        queries.push_back({L, R, i, 0});
        minL = min(minL, L);
        maxR = max(maxR, R);
    }
    if (maxR < 1) maxR = 1;
    if (maxR > GLOBAL_N) maxR = GLOBAL_N; // safety

    // 1) Linear sieve up to maxR
    int M = maxR;
    vector<int> spf(M + 1, 0);
    vector<int> primes;
    spf[0] = 0; if (M >= 1) spf[1] = 1;
    for (int i = 2; i <= M; ++i) {
        if (spf[i] == 0) { spf[i] = i; primes.push_back(i); }
        for (int p : primes) {
            ll v = 1LL * p * i;
            if (v > M) break;
            spf[v] = p;
            if (p == spf[i]) break;
        }
    }

    int P = (int)primes.size();
    // 2) Build belongs[] packed format: first count sizes
    vector<int> counts(M + 1, 0);
    for (int i = 0; i < P; ++i) {
        int pi = primes[i];
        for (int j = 0; j < P; ++j) {
            ll prod = 1LL * pi * primes[j];
            if (prod > M) break;
            counts[(int)prod] += 1;
        }
    }

    // prefix sums -> offsets
    vector<int> offsets(M + 2, 0);
    for (int i = 1; i <= M; ++i) offsets[i] = offsets[i - 1] + counts[i - 1];
    offsets[M + 1] = offsets[M] + counts[M];
    int total = offsets[M + 1];

    // fill flat array
    vector<int> flat(total);
    // temp cursor for fill
    vector<int> cur = offsets;
    for (int i = 0; i < P; ++i) {
        int pi = primes[i];
        for (int j = 0; j < P; ++j) {
            ll prod = 1LL * pi * primes[j];
            if (prod > M) break;
            int k = (int)prod;
            flat[cur[k]++] = i; // store index of prime pi (same semantics as original)
        }
    }
    // free counts/cur memory by letting them go out of scope (or reuse)
    counts.clear(); counts.shrink_to_fit();
    cur.clear(); cur.shrink_to_fit();

    // compute order for queries using gilbert (choose pow s.t. (1<<pow)>M)
    int pow = 0;
    while ((1 << pow) <= M) ++pow;
    for (auto &q : queries) {
        q.ord = gilbertOrder(q.l, q.r, pow, 0);
    }

    sort(queries.begin(), queries.end(), [](const Query &a, const Query &b) {
        if (a.ord != b.ord) return a.ord < b.ord;
        return a.idx < b.idx;
    });

    // Mo's
    vector<ll> answers(T);
    ll cur_ans = 0;
    int cur_l = 1, cur_r = 0;
    vector<int> cnt(P, 0);

    auto add_pos = [&](int pos) {
        if (pos < 2 || pos > M) return;
        int start = offsets[pos];
        int end = offsets[pos + 1];
        for (int i = start; i < end; ++i) {
            int gid = flat[i];
            int old = cnt[gid];
            cnt[gid] = old + 1;
            cur_ans += old;
        }
    };
    auto rem_pos = [&](int pos) {
        if (pos < 2 || pos > M) return;
        int start = offsets[pos];
        int end = offsets[pos + 1];
        for (int i = start; i < end; ++i) {
            int gid = flat[i];
            int old = cnt[gid];
            cnt[gid] = old - 1;
            cur_ans -= (old - 1);
        }
    };

    for (auto &q : queries) {
        int L = q.l, R = q.r;
        while (cur_r < R) add_pos(++cur_r);
        while (cur_r > R) rem_pos(cur_r--);
        while (cur_l < L) rem_pos(cur_l++);
        while (cur_l > L) add_pos(--cur_l);
        answers[q.idx] = cur_ans;
    }

    for (int i = 0; i < T; ++i) cout << answers[i] << '\n';
    return 0;
}

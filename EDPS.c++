// #include <bits/stdc++.h>
// using namespace std;

// bool dfs(int pos, int bal, stack<int>& st, multiset<int>& rem, vector<char>& s) {
//     int NN = s.size();
//     if (pos == NN) {
//         return true;
//     }
//     // try close
//     if (bal > 0) {
//         int op = st.top();
//         int d = pos - op - 1;
//         auto it = rem.find(d);
//         if (it != rem.end()) {
//             rem.erase(it);
//             st.pop();
//             s[pos] = ')';
//             if (dfs(pos + 1, bal - 1, st, rem, s)) return true;
//             st.push(op);
//             rem.insert(d);
//         }
//     }
//     // try open
//     int cur_opens = (pos + bal) / 2;
//     if (cur_opens < NN / 2) {
//         s[pos] = '(';
//         st.push(pos);
//         if (dfs(pos + 1, bal + 1, st, rem, s)) return true;
//         st.pop();
//     }
//     return false;
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(NULL);
//     int N;
//     cin >> N;
//     vector<int> A(N);
//     for (int i = 0; i < N; i++) cin >> A[i];
//     bool possible = true;
//     for (int x : A) {
//         if (x % 2 != 0 || x < 0 || x > 2 * N - 2) possible = false;
//     }
//     if (!possible) {
//         cout << "No\n";
//         return 0;
//     }
//     vector<char> s(2 * N);
//     multiset<int> rem(A.begin(), A.end());
//     stack<int> st;
//     if (dfs(0, 0, st, rem, s)) {
//         cout << "Yes\n";
//         for (char c : s) cout << c;
//         cout << '\n';
//     } else {
//         cout << "No\n";
//     }
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    vector<tuple<ll,ll,ll>> tests(T);
    ll maxN = 0;
    for (int i = 0; i < T; ++i) {
        ll N, M, A;
        cin >> N >> M >> A;
        tests[i] = {N, M, A};
        maxN = max(maxN, N);
    }

    vector<int> coins = {1,2,4,20,40,80,200,400,800};
    ll limit = 212 * maxN;

    // Use int dp to save memory (4 bytes each)
    vector<int> dp(limit + 1, 0);
    dp[0] = 1;
    for (int c : coins)
        for (int i = c; i <= limit; ++i)
            dp[i] = (dp[i] + dp[i - c]) % MOD;

    for (auto &[N, M, A] : tests) {
        ll amt = 212LL * N;
        ll actual = dp[amt];
        ll distM = abs(M - actual);
        ll distA = abs(A - actual);
        if (distM < distA) cout << "Mikel\n";
        else if (distA < distM) cout << "Andrew\n";
        else if (distM == 0) cout << "TIE\n";
        else cout << "NONE\n";
    }
}

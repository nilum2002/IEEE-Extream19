#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;
const int MAXN = 21200010;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<ll> dp(MAXN, 0LL);
    dp[0] = 1LL;
    vector<int> coins = {1,2,4,20,40,80,200,400,800};
    for (int i = 1; i < MAXN; ++i) {
        for (int c : coins) {
            if (i >= c) {
                dp[i] += dp[i - c];
                if (dp[i] >= MOD) dp[i] -= MOD;
            }
        }
    }
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        ll N, M, A;
        cin >> N >> M >> A;
        ll amt = 212LL * N;
        ll actual = dp[amt];
        ll distM = abs(M - actual);
        ll distA = abs(A - actual);
        if (distM < distA) {
            cout << "Mikel" << '\n';
        } else if (distA < distM) {
            cout << "Andrew" << '\n';
        } else {
            if (distM == 0) {
                cout << "TIE" << '\n';
            } else {
                cout << "NONE" << '\n';
            }
        }
    }
    return 0;
}
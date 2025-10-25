#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    long double dp[2][1024] = {};
    int cur = 0, nxt = 1;
    dp[cur][0] = 1.0L;
    
    for (int i = 0; i < n; i++) {
        fill(dp[nxt], dp[nxt] + 1024, 0.0L);
        for (int x = 0; x < 1024; x++) {
            dp[nxt][x] += dp[cur][x] * 0.5L;
            int nx = x ^ a[i];
            dp[nxt][nx] += dp[cur][x] * 0.5L;
        }
        swap(cur, nxt);
    }
    
    long double exp = 0.0L;
    for (int x = 0; x < 1024; x++) {
        long double pk = 1.0L;
        for (int j = 0; j < k; j++) {
            pk *= static_cast<long double>(x);
        }
        exp += dp[cur][x] * pk;
    }
    
    cout << fixed << setprecision(2) << exp << endl;
    
    return 0;
}
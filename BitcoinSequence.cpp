#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long ll;

const int MAX_M = 100005;
const ll MOD = 1000000007LL;

ll ans[MAX_M];
ll temp[MAX_M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;
    
    memset(ans, 0, sizeof(ll) * (M + 1));
    ans[0] = 1;

    for (ll i = M; i >= 1; --i) {
        memset(temp, 0, sizeof(ll) * (M + 1));
        
        for (ll n = i; n <= M; n += i) {
            temp[n] = (temp[n] + 1) % MOD;
        }
        
       
        for (ll r = 0; r < i; ++r) {
            ll sum1 = 0;
            ll sum2 = 0;
            ll j = 0;
            while (true) {
                ll t = r + j * i;
                if (t > M) break;
                
                ll c = ans[t];
                sum1 = (sum1 + c) % MOD;
                sum2 = (sum2 + j * c % MOD) % MOD;
                
                ll value = ((j + 1) * sum1 % MOD - sum2 + MOD) % MOD;
                temp[t] = (temp[t] + value) % MOD;
                
                ++j;
            }
        }
        
        memcpy(ans, temp, sizeof(ll) * (M + 1));
    }
    
    for (ll n = 1; n <= M; ++n) {
        cout << ans[n] << '\n';
    }
    
    return 0;
}
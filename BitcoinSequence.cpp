#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long M;
    cin >> M;
    const long long MOD = 1000000007;
    
    vector<long long> ans(M + 1, 0);
    vector<long long> temp(M + 1);
    
    for (long long i = M; i >= 1; --i) {
        fill(temp.begin(), temp.end(), 0);
        
       
        for (long long n = i; n <= M; n += i) {
            temp[n] = (temp[n] + 1) % MOD;
        }
        
       
        for (long long r = 0; r < i; ++r) {
            long long sum1 = 0;
            long long sum2 = 0;
            long long j = 0;
            while (true) {
                long long t = r + j * i;
                if (t > M) break;
                
                long long c = ans[t];
                sum1 = (sum1 + c) % MOD;
                sum2 = (sum2 + j * c % MOD) % MOD;
                
                long long value = ((j + 1) * sum1 % MOD - sum2 + MOD) % MOD; 
                temp[t] = (temp[t] + value) % MOD;
                
                ++j;
            }
        }
        
        ans = temp;
    }
    
    for (long long n = 1; n <= M; ++n) {
        cout << ans[n] << '\n';
    }
    
    return 0;
}
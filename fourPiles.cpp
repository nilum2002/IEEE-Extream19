#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

ll a1[4], b1[4];
ll gx;
ll mem[61][2][2][2][2][2][2][2];

ll dpf(int ps, int ta0, int tb0, int ta1, int tb1, int ta2, int tb2, int tx) {
    if (ps == -1) {
        return 1;
    }
    if (mem[ps][ta0][tb0][ta1][tb1][ta2][tb2][tx] != -1) {
        return mem[ps][ta0][tb0][ta1][tb1][ta2][tb2][tx];
    }

    ll an = 0;
    
    int la = (ta0) ? ((a1[0] >> ps) & 1) : 0;
    int ua  = (tb0) ? ((b1[0] >> ps) & 1) : 1;
    
    int lb = (ta1) ? ((a1[1] >> ps) & 1) : 0;
    int ub  = (tb1) ? ((b1[1] >> ps) & 1) : 1;
    
    int lc = (ta2) ? ((a1[2] >> ps) & 1) : 0;
    int uc  = (tb2) ? ((b1[2] >> ps) & 1) : 1;
    
    int ux  = (tx)  ? ((gx >> ps) & 1) : 1;

    for (int ba = la; ba <= ua; ++ba) {
        for (int bb = lb; bb <= ub; ++bb) {
            for (int bc = lc; bc <= uc; ++bc) {
                
                int bs = ba ^ bb ^ bc;
                
                if (bs > ux) {
                    continue;
                }
                
                int nta0 = ta0 && (ba == la);
                int ntb0 = tb0 && (ba == ua);
                int nta1 = ta1 && (bb == lb);
                int ntb1 = tb1 && (bb == ub);
                int nta2 = ta2 && (bc == lc);
                int ntb2 = tb2 && (bc == uc);
                int ntx  = tx  && (bs == ux);
                
                an = (an + dpf(ps - 1, nta0, ntb0, nta1, ntb1, nta2, ntb2, ntx)) % MOD;
            }
        }
    }
    
    return mem[ps][ta0][tb0][ta1][tb1][ta2][tb2][tx] = an;
}

ll solv(ll X) {
    if (X < 0) return 0;
    gx = X;
    memset(mem, -1, sizeof(mem));
    return dpf(60, 1, 1, 1, 1, 1, 1, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int qq;
    cin >> qq;
    while (qq--) {
        for (int ii = 0; ii < 4; ++ii) {
            cin >> a1[ii] >> b1[ii];
        }
        
        ll tot = 1;
        for (int ii = 0; ii < 4; ++ii) {
            ll len_i = ((b1[ii] % MOD) - (a1[ii] % MOD) + 1 + MOD) % MOD;
            
            tot = (tot * len_i) % MOD;
        }
        
        ll cnt_up_b3 = solv(b1[3]);
        ll cnt_up_a3_m1 = solv(a1[3] - 1);
        
        ll num_los = (cnt_up_b3 - cnt_up_a3_m1 + MOD) % MOD;
        
        ll num_win = (tot - num_los + MOD) % MOD;
        
        cout << num_win << "\n";
    }
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

const long long xyz = 998244353;

long long abc(long long def, long long ghi, long long jkl) {
    long long mno = 1;
    def %= jkl;
    while (ghi > 0) {
        if (ghi & 1) mno = ((__int128)mno * def) % jkl;
        def = ((__int128)def * def) % jkl;
        ghi >>= 1;
    }
    return mno;
}

long long pqr(long long stu, long long vwx) {
    return abc(stu, vwx - 2, vwx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int yza, bcd;
    cin >> yza >> bcd;
    
    vector<long long> efg(yza);
    long long sum_s = 0;
    for (int hij = 0; hij < yza; ++hij) {
        cin >> efg[hij];
        efg[hij] %= xyz;
        sum_s = (sum_s + efg[hij]) % xyz;
    }
    
    long long sum_inv = 0;
    for (int hij = 0; hij < yza; ++hij) {
        sum_inv = (sum_inv + pqr(efg[hij], xyz)) % xyz;
    }
    
    long long current_add = 0;
    
    for (int wxy = 0; wxy < bcd; ++wxy) {
        int zab;
        cin >> zab;
        if (zab == 1) {
            long long cde;
            cin >> cde;
            cde %= xyz;
            current_add = (current_add + cde) % xyz;
            sum_s = (sum_s + (__int128)yza * cde % xyz) % xyz;
        } else if (zab == 2) {
            // Update efg to the inverted values
            for (int ghi_ = 0; ghi_ < yza; ++ghi_) {
                long long current_s = (efg[ghi_] + current_add) % xyz;
                efg[ghi_] = pqr(current_s, xyz);
            }
            current_add = 0;
            // Swap sum_s and sum_inv
            swap(sum_s, sum_inv);
            
            sum_inv = 0;
            for (int hij = 0; hij < yza; ++hij) {
                sum_inv = (sum_inv + pqr(efg[hij], xyz)) % xyz;
            }
        }
        cout << sum_s << "\n";
    }
    
    return 0;
}
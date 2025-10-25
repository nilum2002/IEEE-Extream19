#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long getTz(long long n ){
    if (n == 0){
        return 0;
    }else{
        return __builtin_ctzll(n);
    }
}

vector<long long> sol(long long n){
    vector<long long> res; 
    long long tz = getTz(n);
    long long k = 1LL << (tz-1);

   
    long long a = n+k;
    long long  c = n/2;
    long long  b = c -k;
    if (b <= 0) return res;
    res.push_back(a);
    res.push_back(b);
    res.push_back(c);
    return res ;
    





}

int main() {
    int t; 
    cin >> t;
    while (t--){
        long long  n ;
        cin >>n;
        if (n%2 != 0){
            cout << -1 << endl;
        }else{
            vector<long long> res = sol(n);
            if (res.empty()){
                cout << -1 << endl;
            }
            for (auto val : res ){
                cout << val << " ";
            }
            cout << endl;
        }
    }
    return 0;

}
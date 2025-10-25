#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N,K;
  cin>>N>>K;
  vector<long long> A(N+1);
  for(int i=1;i<=N;i++) cin>>A[i];
  const int MAXB=20;
  vector<long long> sans(K+1,0);
  for(int b=1; b<MAXB; b++){
    long long V = 1LL<<b;
    vector<int> pref(N+1,0);
    for(int i=1;i<=N;i++){
      pref[i] = pref[i-1] + (A[i] >= V ? 1:0);
    }
    for(int m=1; m<=K; m++){
      long long contrib=0;
      int curr_r=0;
      for(int l=1; l<=N; l++){
        int target = m + pref[l-1];
        while(curr_r < N && (curr_r < l || pref[curr_r] < target)){
          curr_r++;
        }
        if(curr_r > N || pref[curr_r] < target) continue;
        long long rmin = curr_r;
        long long maxd = N - l +1;
        long long mind = rmin - l +1;
        if(mind > maxd) continue;
        long long sum1 = maxd * (maxd +1) /2;
        long long sum2 = (mind-1) * mind /2;
        contrib += sum1 - sum2;
      }
      sans[m] += contrib;
    }
  }
  for(int kk=1;kk<=K;kk++){
    cout<< sans[kk];
    if(kk<K) cout<<" ";
    else cout<<"\n";
  }
  return 0;
}
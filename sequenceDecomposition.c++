#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        string s;
        cin >> s;
        int n = s.length();
        
        // State machine for pattern {1,1,2,0,1,2}
        // State 0: need 1st '1'
        // State 1: need 2nd '1' 
        // State 2: need 1st '2'
        // State 3: need '0'
        // State 4: need 3rd '1'
        // State 5: need 2nd '2'
        
        vector<deque<int>> state(6);
        vector<vector<int>> subsequences;
        
        for (int i = 0; i < n; i++) {
            char c = s[i];
            int idx = i + 1; // 1-based
            
            if (c == '1') {
                // Priority: state 4 > state 1 > state 0 (start new)
                if (!state[4].empty()) {
                    int subId = state[4].front();
                    state[4].pop_front();
                    subsequences[subId].push_back(idx);
                    state[5].push_back(subId);
                } else if (!state[1].empty()) {
                    int subId = state[1].front();
                    state[1].pop_front();
                    subsequences[subId].push_back(idx);
                    state[2].push_back(subId);
                } else {
                    // Start new subsequence
                    int subId = subsequences.size();
                    subsequences.push_back({idx});
                    state[1].push_back(subId);
                }
            } else if (c == '2') {
                // Priority: state 5 > state 2
                if (!state[5].empty()) {
                    int subId = state[5].front();
                    state[5].pop_front();
                    subsequences[subId].push_back(idx);
                    // Completed, no further state
                } else if (!state[2].empty()) {
                    int subId = state[2].front();
                    state[2].pop_front();
                    subsequences[subId].push_back(idx);
                    state[3].push_back(subId);
                }
            } else { // c == '0'
                if (!state[3].empty()) {
                    int subId = state[3].front();
                    state[3].pop_front();
                    subsequences[subId].push_back(idx);
                    state[4].push_back(subId);
                }
            }
        }
        
        // Output all complete subsequences (those with 6 elements)
        for (auto& sub : subsequences) {
            if (sub.size() == 6) {
                for (int j = 0; j < 6; j++) {
                    if (j > 0) cout << " ";
                    cout << sub[j];
                }
                cout << "\n";
            }
        }
    }
    
    return 0;
}
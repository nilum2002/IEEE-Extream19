#include <iostream>
#include <vector>
#include <string>
#include <queue>

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
        
        // State: 1 = need 2nd '1', 2 = need 1st '2', 
        //        3 = need '0', 4 = need 3rd '1', 5 = need 2nd '2'
        
        vector<queue<int>> stateQueues(6); // indices 1 to 5 used
        vector<vector<int>> subsequences; // store indices for each subsequence
        
        for (int i = 0; i < n; i++) {
            char c = s[i];
            int idx = i + 1; // 1-based index
            
            if (c == '1') {
                // Try to add to existing subsequence needing '1'
                if (!stateQueues[1].empty()) {
                    int subId = stateQueues[1].front();
                    stateQueues[1].pop();
                    subsequences[subId].push_back(idx);
                    stateQueues[2].push(subId); // move to state 2
                } else if (!stateQueues[4].empty()) {
                    int subId = stateQueues[4].front();
                    stateQueues[4].pop();
                    subsequences[subId].push_back(idx);
                    stateQueues[5].push(subId); // move to state 5
                } else {
                    // Start new subsequence
                    int subId = subsequences.size();
                    subsequences.push_back({idx});
                    stateQueues[1].push(subId);
                }
            } else if (c == '2') {
                // Try to add to existing subsequence needing '2'
                if (!stateQueues[2].empty()) {
                    int subId = stateQueues[2].front();
                    stateQueues[2].pop();
                    subsequences[subId].push_back(idx);
                    stateQueues[3].push(subId); // move to state 3
                } else if (!stateQueues[5].empty()) {
                    int subId = stateQueues[5].front();
                    stateQueues[5].pop();
                    subsequences[subId].push_back(idx);
                    // Completed, do not push anywhere
                }
            } else { // c == '0'
                // Add to subsequence needing '0'
                if (!stateQueues[3].empty()) {
                    int subId = stateQueues[3].front();
                    stateQueues[3].pop();
                    subsequences[subId].push_back(idx);
                    stateQueues[4].push(subId); // move to state 4
                }
            }
        }
        
        // Output completed subsequences
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
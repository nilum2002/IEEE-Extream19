#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

// using infintiy as we are maximinzing the score
const ll INF = -1e18; 

int main() {
   
    int first_seq_len, second_seq_len;
    string first_dna, second_dna;
    ll match_score, mismatch_score, gap_score;

    cin >> first_seq_len >> first_dna >> second_seq_len >> second_dna >> match_score >> mismatch_score >> gap_score;

    // DP tables for our 3 states
    vector<vector<ll>> dp_match(first_seq_len + 1, vector<ll>(second_seq_len + 1, INF));
    vector<vector<ll>> dp_gap_first(first_seq_len + 1, vector<ll>(second_seq_len + 1, INF));
    vector<vector<ll>> dp_gap_second(first_seq_len + 1, vector<ll>(second_seq_len + 1, INF));

   
    
    // Base case, empty strings align with cost 0
    dp_match[0][0] = 0;

    // Base case, aligning first_dnawith an empty string (all gaps)
    for (int i = 1; i <= first_seq_len; ++i) {
        dp_gap_first[i][0] = 1LL * i * i * gap_score;
    }

    // Base case, aligning second_dnawith an empty string (all gaps)
    for (int j = 1; j <= second_seq_len; ++j) {
        dp_gap_second[0][j] = 1LL * j * j * gap_score;
    }

    //main DP Loop
    for (int i = 1; i <= first_seq_len; ++i) {
        for (int j = 1; j <= second_seq_len; ++j) {
            
            // calculating the mismathc
            // This state must come from a previous state 
            ll previous_best = max({dp_match[i-1][j-1], dp_gap_first[i-1][j-1], dp_gap_second[i-1][j-1]});
            if (previous_best != INF) {
                ll align_score = (first_dna[i - 1] == second_dna[j - 1]) ? match_score : mismatch_score;
                dp_match[i][j] = previous_best + align_score;
            }

            // calculating the gap in the fisrt sequenc
            // trying every possible gap length 'k' ending at 'i'.
            ll best_gap_a = INF;
            for (int k = 1; k <= i; ++k) {
                // the best score before this gap block started (at state (i-k, j))
               
                ll before_gap = max(dp_match[i - k][j], dp_gap_second[i - k][j]);
                
                if (before_gap != INF) {
                    ll current_cost = before_gap + 1LL * k * k * gap_score;
                    best_gap_a = max(best_gap_a, current_cost);
                }
            }
            dp_gap_first[i][j] = best_gap_a;

            // calculating the gap in the sefcon sequencce
            
            // We try every possible gap length 'k' ending at 'j'.
            ll best_gap_b = INF;
            for (int k = 1; k <= j; ++k) {
                // the best score before this gap block started (at state (i, j-k))
                ll before_gap = max(dp_match[i][j - k], dp_gap_first[i][j - k]);
                
                if (before_gap != INF) {
                    ll current_cost = before_gap + 1LL * k * k * gap_score;
                    best_gap_b = max(best_gap_b, current_cost);
                }
            }
            dp_gap_second[i][j] = best_gap_b;
        }
    }

    // Final answer is the best one
    ll final_answer = max({dp_match[first_seq_len][second_seq_len], 
                           dp_gap_first[first_seq_len][second_seq_len], 
                           dp_gap_second[first_seq_len][second_seq_len]});
    
    cout << final_answer << "\n";

    return 0;
}
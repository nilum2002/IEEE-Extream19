#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;

typedef long long ll;

const ll INF = -1e18;

struct Line {
    ll m, c;
};


using namespace std;

typedef long long ll; //64 bit to avoid overflow

// A large negative number, representing -Infinity as we are maximixing
const ll INF = -1e18;

// Representing a line y = m*x + c for the CHT optimization
struct Line {
    ll m, c; 
};

// Calculatint the value of the line at a pointc
// cheking whether there will be an overfloww
ll eval(Line l, ll x) {
    if (l.m > 0 && x > 0 && l.m > __LONG_LONG_MAX__ / x) return INF; 
    if (l.m < 0 && x < 0 && l.m < __LONG_LONG_MAX__ / x) return INF;
    if (l.m > 0 && x < 0 && l.m < -__LONG_LONG_MAX__ / x) return INF;
    if (l.m < 0 && x > 0 && l.m < -__LONG_LONG_MAX__ / x) return INF;

    ll val = l.m * x;
    if (val > 0 && l.c > 0 && val > __LONG_LONG_MAX__ - l.c) return INF;
    if (val < 0 && l.c < 0 && val < -__LONG_LONG_MAX__ - l.c) return INF;
    
    return val + l.c;
}

//chekcing whther the line 2 is redudanunat 
// Uses 128-bit integers to avoid overflow during the cross-product check.
bool isLineRedundant(Line line1, Line line2, Line line3) {
    return (__int128_t)(line3.c - line1.c) * (line1.m - line2.m) < 
           (__int128_t)(line2.c - line1.c) * (line1.m - line3.m);
}

// Addig a new line to the CHT hull (deque)
// removes any lines from the *back* that are now redundant.
void addLineToHull(deque<Line>& hull, Line new_line) {
    int size = hull.size();
    while (size >= 2 && isLineRedundant(hull[size - 2], hull[size - 1], new_line)) {
        hull.pop_back();
        size--;
    }
    hull.push_back(new_line);
}

//using the queries hull

ll queryHull(deque<Line>& hull, ll x_value) {
    if (hull.empty()) {
        return INF;
    }
    // Removing lines from the front that are no longer optimal

    while (hull.size() >= 2 && eval(hull[0], x_value) <= eval(hull[1], x_value)) {
        hull.pop_front();
    }
    return eval(hull[0], x_value);
}

int main() {
    // Faster C++ input/output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int first_seq_len, second_seq_len;
    string first_dna, second_dna;
    ll match_score, mismatch_score, gap_score;

    cin >> first_seq_len >> first_dna >> second_seq_len >> second_dna >> match_score >> mismatch_score >> gap_score;

    // DP tables for our 3 states
    vector<vector<ll>> dp_match(first_seq_len + 1, vector<ll>(second_seq_len + 1, INF));
    vector<vector<ll>> dp_gap_first(first_seq_len + 1, vector<ll>(second_seq_len + 1, INF));
    vector<vector<ll>> dp_gap_second(first_seq_len + 1, vector<ll>(second_seq_len + 1, INF));

    // CHT hulls: We need one hull for each *column* to calculate dp_gap_first
    vector<deque<Line>> column_hulls(second_seq_len + 1);

   
    dp_match[0][0] = 0; // Aligning empty strings costs 0

    // Aligning first_dna with an empty string
    for (int i = 1; i <= first_seq_len; ++i) {
        dp_gap_first[i][0] = 1LL * i * i * gap_score;
    }

    // Aligning second_dna with an empty string
    for (int j = 1; j <= second_seq_len; ++j) {
        dp_gap_second[0][j] = 1LL * j * j * gap_score;
    }

    // Initialize all column hulls with the p=0 (empty prefix) line
    for (int j = 0; j <= second_seq_len; ++j) {
        ll base_value = max(dp_match[0][j], dp_gap_second[0][j]);
        if (base_value != INF) {
            // Line for p=0: slope=0, constant=base_value
            ll slope = -2LL * 0 * gap_score; 
            ll constant = 1LL * 0 * 0 * gap_score + base_value;
            addLineToHull(column_hulls[j], {slope, constant});
        }
    }

    // main dp lbase case
    for (int i = 1; i <= first_seq_len; ++i) {
        // We build a *new* CHT hull for each *row* to calculate dp_gap_second
        deque<Line> row_hull;

        // Initialize this new row_hull with its p=0 (empty prefix) line
        ll row_base_value = max(dp_match[i][0], dp_gap_first[i][0]);
        if (row_base_value != INF) {
            ll slope = -2LL * 0 * gap_score;
            ll constant = 1LL * 0 * 0 * gap_score + row_base_value;
            addLineToHull(row_hull, {slope, constant});
        }

        for (int j = 1; j <= second_seq_len; ++j) {
            
        
            // calculating the match mismatch
            ll previous_best = max({dp_match[i-1][j-1], dp_gap_first[i-1][j-1], dp_gap_second[i-1][j-1]});
            if (previous_best != INF) {
                ll alignment_score = (first_dna[i - 1] == second_dna[j - 1]) ? match_score : mismatch_score;
                dp_match[i][j] = previous_best + alignment_score;
            }

            //calculating the gap squence
            ll gap_first_value = queryHull(column_hulls[j], i); // Query column j at x=i
            if (gap_first_value != INF) {
                dp_gap_first[i][j] = gap_first_value + 1LL * i * i * gap_score;
            }

           //calculating the gap in the second sequence
            ll gap_second_value = queryHull(row_hull, j); // Query row i at x=j
            if (gap_second_value != INF) {
                dp_gap_second[i][j] = gap_second_value + 1LL * j * j * gap_score;
            }

            // updating hull for the furrue-
            
            
            ll column_update_value = max(dp_match[i][j], dp_gap_second[i][j]);
            if (column_update_value != INF) {
                ll slope = -2LL * i * gap_score;
                ll constant = 1LL * i * i * gap_score + column_update_value;
                addLineToHull(column_hulls[j], {slope, constant});
            }

            // Add the new line from p=j to the row_hul
            ll row_update_value = max(dp_match[i][j], dp_gap_first[i][j]);
            if (row_update_value != INF) {
                ll slope = -2LL * j * gap_score;
                ll constant = 1LL * j * j * gap_score + row_update_value;
                addLineToHull(row_hull, {slope, constant});
            }
        }
    }

    // Final answer is the best of the 3 states at (n, m)
    ll final_answer = max({dp_match[first_seq_len][second_seq_len], 
                           dp_gap_first[first_seq_len][second_seq_len], 
                           dp_gap_second[first_seq_len][second_seq_len]});
    
    cout << final_answer << "\n";

    return 0;
}

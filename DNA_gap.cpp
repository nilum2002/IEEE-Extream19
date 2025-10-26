/*
 * Solution for the "Squared Gaps" sequence alignment problem.
 *
 * This problem is a variation of the classic sequence alignment problem,
 * solved with dynamic programming.
 *
 * The standard DP state DP(i, j) is insufficient because the cost of a gap
 * is non-linear (k^2 * gap_cost). The cost to extend a gap depends
 * on the current length of the gap block.
 *
 * To solve this, we use three DP states:
 * 1. dp_match[i][j]: Max cost of aligning a[1..i] and b[1..j],
 * where a[i] is aligned with b[j] (match/mismatch).
 * 2. dp_gapA[i][j]:   Max cost, where a[i] is aligned with a gap.
 * 3. dp_gapB[i][j]:   Max cost, where b[j] is aligned with a gap.
 *
 * The final answer is the maximum of these three states at (n, m).
 *
 * Transitions:
 *
 * 1. dp_match[i][j]:
 * This alignment must follow a state at (i-1, j-1).
 * dp_match[i][j] = score(a[i], b[j]) + max(
 * dp_match[i-1][j-1],
 * dp_gapA[i-1][j-1],
 * dp_gapB[i-1][j-1]
 * )
 * This is an O(1) calculation.
 *
 * 2. dp_gapA[i][j]:
 * a[i] is the end of a gap block of length k (k >= 1). This block
 * a[i-k+1 ... i] is aligned with b[j]. The previous alignment must
 * be at (i-k, j) and cannot have ended with a gap in 'a'.
 *
 * dp_gapA[i][j] = max_{1 <= k <= i} [
 * max(dp_match[i-k][j], dp_gapB[i-k][j])
 * + k^2 * gap
 * ]
 *
 * 3. dp_gapB[i][j]:
 * Symmetric to dp_gapA.
 * dp_gapB[i][j] = max_{1 <= k <= j} [
 * max(dp_match[i][j-k], dp_gapA[i][j-k])
 * + k^2 * gap
 * ]
 *
 * Complexity Problem:
 * The naive transitions for gaps take O(i) and O(j) time, leading to an
 * overall O(n*m*(n+m)) complexity, which is too slow.
 * The constraint n*m <= 10^6 implies a total complexity of O(n*m)
 * is required.
 *
 * Optimization (Convex Hull Trick):
 * Let's optimize the calculation for dp_gapA (dp_gapB is symmetric).
 * We process the DP table column by column (fix j, iterate i).
 *
 * Let S(p, j) = max(dp_match[p][j], dp_gapB[p][j]).
 * Let p = i - k.
 *
 * dp_gapA[i][j] = max_{0 <= p < i} [ S(p, j) + (i - p)^2 * gap ]
 * dp_gapA[i][j] = max_{0 <= p < i} [ S(p, j) + (i^2 - 2ip + p^2) * gap ]
 * dp_gapA[i][j] = i^2 * gap + max_{0 <= p < i} [ (S(p, j) + p^2 * gap) + (-2p * gap) * i ]
 *
 * This is a classic form for the Convex Hull Trick (CHT).
 * For a fixed column 'j', as we iterate 'i' from 1 to n, we are
 * querying for the maximum value of a set of lines at point x = i.
 *
 * Each 'p' (from 0 to i-1) defines a line:
 * Line: y = M * x + C
 * M = -2 * p * gap
 * C = S(p, j) + p^2 * gap
 * x = i
 *
 * Since gap < 0, (-2 * gap) is positive. As 'p' increases, the slope 'M'
 * increases. Since our queries 'x = i' are also increasing, we can
 * maintain the upper hull of these lines in O(1) amortized time
 * using a deque.
 *
 * This optimization reduces the cost of calculating all dp_gapA states
 * in a column from O(n^2) to O(n).
 *
 * Total Complexity:
 * We have n*m states. The dependencies are:
 * - dp_match[i][j] depends on (i-1, j-1).
 * - dp_gapA[i][j] depends on column 'j', rows p < i.
 * - dp_gapB[i][j] depends on row 'i', columns p < j.
 *
 * We can compute the table in a single O(n*m) pass.
 * Inside the loop (i, j):
 * 1. Compute dp_match[i][j] (O(1)).
 * 2. Compute dp_gapA[i][j] (O(1) amortized, using CHT on column 'j').
 * 3. Compute dp_gapB[i][j] (O(1) amortized, using CHT on row 'i').
 * 4. Update the CHT structures for column 'j' (with info from 'i')
 * and row 'i' (with info from 'j').
 *
 * Total complexity: O(n * m).
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;

// Use long long for costs
typedef long long ll;

// Define a large negative number for "infinity" since we are maximizing.
const ll INF = -1e18;

// Structure to represent a line for CHT
// y = m*x + c
struct Line {
    ll m, c;
};

// Evaluate the line at a given x
ll eval(Line l, ll x) {
    // Check for overflow before multiplication
    if (l.m > 0 && x > 0 && l.m > __LONG_LONG_MAX__ / x) return INF; 
    if (l.m < 0 && x < 0 && l.m < __LONG_LONG_MAX__ / x) return INF;
    if (l.m > 0 && x < 0 && l.m < -__LONG_LONG_MAX__ / x) return INF;
    if (l.m < 0 && x > 0 && l.m < -__LONG_LONG_MAX__ / x) return INF;

    ll val = l.m * x;
    if (val > 0 && l.c > 0 && val > __LONG_LONG_MAX__ - l.c) return INF;
    if (val < 0 && l.c < 0 && val < -__LONG_LONG_MAX__ - l.c) return INF;
    
    return val + l.c;
}

// Check if line l2 is redundant (non-convex) between l1 and l3
// We use 128-bit integers to prevent overflow during the cross-product
// This check is for an upper hull with increasing slopes.
bool bad(Line l1, Line l2, Line l3) {
    return (__int128_t)(l3.c - l1.c) * (l1.m - l2.m) < 
           (__int128_t)(l2.c - l1.c) * (l1.m - l3.m);
}

// Add a line to the CHT deque, maintaining convexity
void add_line(deque<Line>& hull, Line l) {
    int sz = hull.size();
    while (sz >= 2 && bad(hull[sz - 2], hull[sz - 1], l)) {
        hull.pop_back();
        sz--;
    }
    hull.push_back(l);
}

// Query the CHT deque for the max value at x
// Since query points 'x' are increasing, we pop from the front.
ll query(deque<Line>& hull, ll x) {
    if (hull.empty()) {
        return INF;
    }
    while (hull.size() >= 2 && eval(hull[0], x) <= eval(hull[1], x)) {
        hull.pop_front();
    }
    return eval(hull[0], x);
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    string a, b;
    ll match, mismatch, gap;

    cin >> n >> a >> m >> b >> match >> mismatch >> gap;

    // DP tables, initialized to -infinity
    vector<vector<ll>> dp_match(n + 1, vector<ll>(m + 1, INF));
    vector<vector<ll>> dp_gapA(n + 1, vector<ll>(m + 1, INF));
    vector<vector<ll>> dp_gapB(n + 1, vector<ll>(m + 1, INF));

    // CHT structures: one deque for each column (for dp_gapA)
    vector<deque<Line>> hull_A(m + 1);

    // --- Base Cases ---

    // Aligning empty string with empty string costs 0
    dp_match[0][0] = 0;

    // Base case: aligning a[1..i] with an empty string (all gaps in b)
    for (int i = 1; i <= n; ++i) {
        dp_gapA[i][0] = 1LL * i * i * gap;
    }

    // Base case: aligning b[1..j] with an empty string (all gaps in a)
    for (int j = 1; j <= m; ++j) {
        dp_gapB[0][j] = 1LL * j * j * gap;
    }

    // Initialize CHT hulls with p=0 (base case)
    // For hull_A[j] (column j), add the line for p=0
    for (int j = 0; j <= m; ++j) {
        ll S = max(dp_match[0][j], dp_gapB[0][j]);
        if (S != INF) {
            ll M = -2LL * 0 * gap; // M = 0
            ll C = 1LL * 0 * 0 * gap + S; // C = S
            add_line(hull_A[j], {M, C});
        }
    }


    // --- Fill DP Tables ---

    for (int i = 1; i <= n; ++i) {
        // CHT structure for the current row 'i' (for dp_gapB)
        deque<Line> hull_B;

        // Initialize hull_B with p=0 (base case for this row)
        ll S_B_base = max(dp_match[i][0], dp_gapA[i][0]);
        if (S_B_base != INF) {
            ll M = -2LL * 0 * gap; // M = 0
            ll C = 1LL * 0 * 0 * gap + S_B_base; // C = S_B_base
            add_line(hull_B, {M, C});
        }

        for (int j = 1; j <= m; ++j) {
            
            // 1. Calculate dp_match[i][j]
            // Depends only on (i-1, j-1) states, which are finalized
            ll prev_best = max({dp_match[i-1][j-1], dp_gapA[i-1][j-1], dp_gapB[i-1][j-1]});
            if (prev_best != INF) {
                ll score = (a[i - 1] == b[j - 1]) ? match : mismatch;
                dp_match[i][j] = prev_best + score;
            }

            // 2. Calculate dp_gapA[i][j]
            // Query CHT for column 'j' at x = i
            // This hull (hull_A[j]) contains lines from p = 0...i-1
            ll gapA_val = query(hull_A[j], i);
            if (gapA_val != INF) {
                dp_gapA[i][j] = gapA_val + 1LL * i * i * gap;
            }

            // 3. Calculate dp_gapB[i][j]
            // Query CHT for row 'i' at x = j
            // This hull (hull_B) contains lines from p = 0...j-1
            ll gapB_val = query(hull_B, j);
            if (gapB_val != INF) {
                dp_gapB[i][j] = gapB_val + 1LL * j * j * gap;
            }

            // 4. Update CHT hulls for future calculations

            // Add line for p=i to hull_A[j] (for use in future rows > i)
            ll S_A = max(dp_match[i][j], dp_gapB[i][j]);
            if (S_A != INF) {
                ll M = -2LL * i * gap;
                ll C = 1LL * i * i * gap + S_A;
                add_line(hull_A[j], {M, C});
            }

            // Add line for p=j to hull_B (for use in future columns > j)
            ll S_B = max(dp_match[i][j], dp_gapA[i][j]);
            if (S_B != INF) {
                ll M = -2LL * j * gap;
                ll C = 1LL * j * j * gap + S_B;
                add_line(hull_B, {M, C});
            }
        }
    }

    // --- Final Answer ---
    ll ans = max({dp_match[n][m], dp_gapA[n][m], dp_gapB[n][m]});
    cout << ans << "\n";

    return 0;
}
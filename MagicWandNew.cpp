#include <iostream>
#include <string>
#include <vector>
using namespace std;

// trunyinh t0 create the function again

int counting_theeee_wands(long long people, long long wand_range_dist, string mood) {
    if (wand_range_dist > people) {
        // Checing if every one is happ

        for (char c : mood) if (c != 'H') return -1;
        return 0;
    }

    vector<long long> flip_count(people + 1, 0);
    int wand_count = 0;

    // trying to do a greedy flip
    for (long long i = 0; i <= people - wand_range_dist; ++i) {

        if (mood[i] == 'S') {
            flip_count[i] += 1;
            flip_count[i + wand_range_dist] -= 1;
            ++wand_count;
        }
    }

    // Computeing  final state
    long long live_flips_current = 0;

    for (long long i = 0; i < people; ++i) {

        live_flips_current += flip_count[i];
        char final_string = (live_flips_current % 2 == 0) ? mood[i] : (mood[i] == 'H' ? 'S' : 'H');

        if (final_string != 'H') return -1; // Impossible state
    }

    return wand_count;
}

int main() {

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        long long people, wand_range_dist;
        string mood;
        cin >> people >> wand_range_dist >> mood;
        cout << counting_theeee_wands(people, wand_range_dist, mood) << "\n";
    }
    return 0;
}
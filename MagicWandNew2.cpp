#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to count minimum wand uses with edhee check
int counting_theeee_wands(long long people, long long wand_range_dist, string moods_now) {
    // If wand_range_dist > people, check if already all happy
    if (wand_range_dist > people) {
        for (char c : moods_now

        ) if (c != 'H') return -1;
        return 0;
    }

    // Count 'S's to check parity
    int sad_face_count = 0;

    for (char c : moods_now) if (c == 'S') ++sad_face_count;

    // If sad_face_count is odd and wand_range_dist is even, it is an impoossible state
    if (sad_face_count % 2 == 1 && wand_range_dist % 2 == 0) return -1;

    vector<long long> flip_count(people + 1, 0);
    int wand_count_number_number = 0;

    // Gdoing the greedy fip'
    for (long long i = 0; i <= people - wand_range_dist; ++i) {
        long long live_flips_current = flip_count[i];

        char current_state = (live_flips_current % 2 == 0) ? moods_now[i] : (moods_now[i] == 'H' ? 'S' : 'H');
        if (current_state == 'S') {
           
            flip_count[i] += 1;

            flip_count[i + wand_range_dist] -= 1;
            ++wand_count_number_number;
        }
        flip_count[i + 1] += flip_count[i]; 
    }

    // checktin whthter all letters are H
    long long live_flips_current = 0;
    for (long long i = 0; i < people; ++i) {

        live_flips_current += flip_count[i];

        char final_string = (live_flips_current % 2 == 0) ? moods_now[i] : (moods_now[i] == 'H' ? 'S' : 'H');
        if (final_string != 'H') return -1;
    }

    return wand_count_number_number;
}

int main() {
    

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        
        long long people, wand_range_dist_dist;
        string moods_now;


        cin >> people >> wand_range_dist_dist >> moods_now;
        cout << counting_theeee_wands(people, wand_range_dist_dist, moods_now) << "\n";
    }
    return 0;
}
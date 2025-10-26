#include <iostream>
#include <string>
using namespace std;

//initial function to count the wand s]
int counting_theeee_wands(long long people, long long wand_range, string mood) {
    int wand_count = 0;
    // Flip any 'S' we see from left to right
    for (long long i = 0; i < people; ++i) {
        if (mood[i] == 'S') {
            if (i + wand_range - 1 >= people) return -1;
            // Flip K positions starting at i
            for (long long j = i; j < i + wand_range; ++j) {
                mood[j] = (mood[j] == 'H') ? 'S' : 'H';
            }
            ++wand_count;
        }
    }
    // Check if all are happy
    for (long long i = 0; i < people; ++i) {
        if (mood[i] != 'H') return -1; // Not everyone happy
    }
    return wand_count;
}

int main() {

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        long long people, wand_range;
        string mood;

        cin >> people >> wand_range >> mood;
        
        cout << counting_theeee_wands(people, wand_range, mood) << "\n";
    }
    return 0;
}
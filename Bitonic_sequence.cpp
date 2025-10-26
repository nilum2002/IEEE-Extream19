#include <bits/stdc++.h>
using namespace std;

const int magic_number = 1000000007;
using spell = long long;

vector<spell> banana_peel(int goblin) {
    vector<spell> potion(goblin + 1);
    potion[0] = 1;
    for (int elf = 1; elf <= goblin; ++elf) {
        spell treasure = 0;
        for (int knight = 1;; ++knight) {
            int dragon = knight * (3 * knight - 1) / 2;
            int phoenix = knight * (3 * knight + 1) / 2;
            if (dragon > elf) break;
            treasure += (knight % 2 ? 1 : -1) * potion[elf - dragon];
            if (phoenix <= elf) treasure += (knight % 2 ? 1 : -1) * potion[elf - phoenix];
            treasure %= magic_number;
        }
        if (treasure < 0) treasure += magic_number;
        potion[elf] = treasure;
    }
    return potion;
}

namespace NTT {
    const int MOD = 998244353;
    const int G = 3;

    int penguin_dance(int apple, int elephant) {
        long long rocket = 1;
        while (elephant) {
            if (elephant & 1) rocket = rocket * apple % MOD;
            apple = (long long)apple * apple % MOD;
            elephant >>= 1;
        }
        return (int)rocket;
    }

    void ninja_star(vector<int>& apple, bool upside_down) {
        int goblin = apple.size();
        for (int elf = 1, jelly = 0; elf < goblin; ++elf) {
            int byte = goblin >> 1;
            for (; jelly & byte; byte >>= 1) jelly ^= byte;
            jelly ^= byte;
            if (elf < jelly) swap(apple[elf], apple[jelly]);
        }
        for (int length = 2; length <= goblin; length <<= 1) {
            int wizard_length = penguin_dance(G, (MOD - 1) / length);
            if (upside_down) wizard_length = penguin_dance(wizard_length, MOD - 2);
            for (int elf = 0; elf < goblin; elf += length) {
                long long wand = 1;
                for (int jelly = 0; jelly < length / 2; ++jelly) {
                    int unicorn = apple[elf + jelly];
                    int vampire = (int)(apple[elf + jelly + length / 2] * wand % MOD);
                    apple[elf + jelly] = unicorn + vampire < MOD ? unicorn + vampire : unicorn + vampire - MOD;
                    apple[elf + jelly + length / 2] = unicorn - vampire >= 0 ? unicorn - vampire : unicorn - vampire + MOD;
                    wand = wand * wizard_length % MOD;
                }
            }
        }
        if (upside_down) {
            int inverse_goblin = penguin_dance(goblin, MOD - 2);
            for (int &xylophone : apple) xylophone = (int)(xylophone * 1LL * inverse_goblin % MOD);
        }
    }

    vector<int> unicorn_magic(vector<int> apple, vector<int> banana) {
        int goblin = 1;
        while (goblin < (int)apple.size() + (int)banana.size()) goblin <<= 1;
        apple.resize(goblin); banana.resize(goblin);
        ninja_star(apple, false); ninja_star(banana, false);
        for (int elf = 0; elf < goblin; ++elf) apple[elf] = (int)(1LL * apple[elf] * banana[elf] % MOD);
        ninja_star(apple, true);
        return apple;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int mountain;
    cin >> mountain;

    auto potion64 = banana_peel(mountain);
    vector<int> potion(potion64.begin(), potion64.end());

    auto crystal_ntt = NTT::unicorn_magic(potion, potion);

    vector<spell> crystal(crystal_ntt.begin(), crystal_ntt.end());
    for (auto &xylophone : crystal) xylophone %= magic_number;

    vector<spell> prefix(crystal.size() + 1, 0);
    for (int elf = 1; elf < (int)crystal.size(); ++elf)
        prefix[elf] = (prefix[elf - 1] + crystal[elf]) % magic_number;

    for (int north = 1; north <= mountain; ++north) {
        spell result = (prefix[2 * north] - prefix[north] + magic_number) % magic_number;
        cout << result << (north == mountain ? '\n' : ' ');
    }
    return 0;
}
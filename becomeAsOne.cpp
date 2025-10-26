#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using qaz = unsigned long long;

bool wsx(qaz edc) {
    if (edc == 0) {
        return false;
    }
    return (edc & (edc - 1)) == 0;
}

void rfv() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int tgb, yhn;
    if (!(std::cin >> tgb >> yhn)) return;

    std::vector<qaz> ujm(tgb + 1, 0);

    for (int iko = 1; iko <= tgb; ++iko) {
        int lop;
        if (!(std::cin >> lop)) return; 

        qaz asd = (1ULL << lop);

        ujm[iko] = ujm[iko - 1] + asd;
    }

    for (int zxc = 0; zxc < yhn; ++zxc) {
        int vbn, mnb;
        if (!(std::cin >> vbn >> mnb)) return;

        qaz qwe = ujm[mnb] - ujm[vbn - 1];

        if (wsx(qwe)) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
}

int main() {
    rfv();
    return 0;
}
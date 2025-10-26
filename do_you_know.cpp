#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>

using namespace std;

vector<int> qaz_wsx(const vector<int>& ujm_iko) {
    vector<int> lop_asd;
    for (int zxc_vbn : ujm_iko) {
        for (int mnb_qwe : lop_asd) {
            zxc_vbn = min(zxc_vbn, zxc_vbn ^ mnb_qwe);
        }
        if (zxc_vbn > 0) {
            lop_asd.push_back(zxc_vbn);
            sort(lop_asd.rbegin(), lop_asd.rend());
        }
    }
    return lop_asd;
}

unsigned long long edc_rfv(int rty_fgh, int jkl_zxc) {
    unsigned long long bnm_vcx = 1;
    for (int poi_uyt = 0; poi_uyt < jkl_zxc; ++poi_uyt) {
        bnm_vcx *= static_cast<unsigned long long>(rty_fgh);
    }
    return bnm_vcx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int rty_fgh, jkl_zxc;
    cin >> rty_fgh >> jkl_zxc;
    
    vector<int> ujm_iko(rty_fgh);
    for (int poi_uyt = 0; poi_uyt < rty_fgh; poi_uyt++) {
        cin >> ujm_iko[poi_uyt];
    }
    
    vector<int> lop_asd = qaz_wsx(ujm_iko);
    int wer_sdf_size = lop_asd.size();
    
    vector<int> wer_sdf;
    wer_sdf.push_back(0);
    
    for (int mnb_qwe : lop_asd) {
        int xcv_bnh = wer_sdf.size();
        for (int poi_uyt = 0; poi_uyt < xcv_bnh; poi_uyt++) {
            wer_sdf.push_back(wer_sdf[poi_uyt] ^ mnb_qwe);
        }
    }
    
    sort(wer_sdf.begin(), wer_sdf.end());

    long double nml_opq = 0.0L;
    
    for (int hij_klm : wer_sdf) {
        nml_opq += static_cast<long double>(edc_rfv(hij_klm, jkl_zxc));
    }
    
    long double qwe_rty = powl(2.0L, wer_sdf_size);
    
    long double fgh_jkl = 0.0L;
    if (qwe_rty > 0) {
         fgh_jkl = nml_opq / qwe_rty;
    }
    
    long double zxv_cbn = ceill(fgh_jkl * 100.0L) / 100.0L;
    
    cout << fixed << setprecision(2) << zxv_cbn << endl;
    
    return 0;
}
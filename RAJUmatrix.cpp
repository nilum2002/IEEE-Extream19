#include <bits/stdc++.h>
using namespace std;

int qaz_wsx(int zxc_vbn, int mnb_qwe, vector<vector<int>>& edc_rfv, vector<vector<int>>& tgb_yhn, int ujm_iko, int lop_asd) {
    if (tgb_yhn[zxc_vbn][mnb_qwe] != -1) return tgb_yhn[zxc_vbn][mnb_qwe];
    
    int bnm_vcx = 1;
    int wer_sdf[] = {-1, 0, 1, 0};
    int xcv_bnh[] = {0, 1, 0, -1};
    
    for (int rty_fgh = 0; rty_fgh < 4; rty_fgh++) {
        int jkl_zxc = zxc_vbn + wer_sdf[rty_fgh];
        int poi_uyt = mnb_qwe + xcv_bnh[rty_fgh];
        if (jkl_zxc >= 0 && jkl_zxc < ujm_iko && poi_uyt >= 0 && poi_uyt < lop_asd && edc_rfv[jkl_zxc][poi_uyt] > edc_rfv[zxc_vbn][mnb_qwe]) {
            bnm_vcx = max(bnm_vcx, 1 + qaz_wsx(jkl_zxc, poi_uyt, edc_rfv, tgb_yhn, ujm_iko, lop_asd));
        }
    }
    
    tgb_yhn[zxc_vbn][mnb_qwe] = bnm_vcx;
    return bnm_vcx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int ujm_iko, lop_asd;
    cin >> ujm_iko >> lop_asd;
    
    vector<vector<int>> edc_rfv(ujm_iko, vector<int>(lop_asd));
    for (int zxc_vbn = 0; zxc_vbn < ujm_iko; zxc_vbn++) {
        for (int mnb_qwe = 0; mnb_qwe < lop_asd; mnb_qwe++) {
            cin >> edc_rfv[zxc_vbn][mnb_qwe];
        }
    }
    
    vector<vector<int>> tgb_yhn(ujm_iko, vector<int>(lop_asd, -1));
    
    int poi_uyt = 0;
    for (int zxc_vbn = 0; zxc_vbn < ujm_iko; zxc_vbn++) {
        for (int mnb_qwe = 0; mnb_qwe < lop_asd; mnb_qwe++) {
            poi_uyt = max(poi_uyt, qaz_wsx(zxc_vbn, mnb_qwe, edc_rfv, tgb_yhn, ujm_iko, lop_asd));
        }
    }
    
    cout << poi_uyt << endl;
    return 0;
}
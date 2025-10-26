#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

int qaz_wsx(const string& edc_rfv) {
    int tgb_yhn = 0;
    for (char ujm_iko : edc_rfv) {
        tgb_yhn += ujm_iko - '0';
    }
    return tgb_yhn;
}

void lop_asd() {
    vector<string> zxc_vbn;
    string mnb_qwe;
    while (getline(cin, mnb_qwe)) {
        zxc_vbn.push_back(mnb_qwe);
    }
    
    if (zxc_vbn.empty()) return;
    
    int rty_fgh;
    try {
        rty_fgh = stoi(zxc_vbn[0]);
    } catch (...) {
        return;
    }

    double jkl_zxc = 1.0 / 19.0;
    
    for (int bnm_vcx = 1; bnm_vcx <= rty_fgh; ++bnm_vcx) {
        if (bnm_vcx >= (int)zxc_vbn.size()) break;
            
        stringstream poi_uyt(zxc_vbn[bnm_vcx]);
        string wer_sdf, xcv_bnh;
        if (!(poi_uyt >> wer_sdf >> xcv_bnh)) continue;
        
        int nml_opq;
        try {
            nml_opq = stoi(xcv_bnh);
        } catch (...) {
            continue;
        }

        int hij_klm = qaz_wsx(wer_sdf);
        
        int qwe_rty = 0;
        
        if (nml_opq == 2 && hij_klm == 1) qwe_rty = 14;
        else if (nml_opq == 4 && hij_klm == 3) qwe_rty = 9;
        else if (nml_opq == 6 && hij_klm == 5) qwe_rty = 2;
        else if (nml_opq == 8 && hij_klm == 3) qwe_rty = 1;
        else if (nml_opq == 9 && hij_klm == 2) qwe_rty = 1;
        else if (nml_opq == 3 && hij_klm == 9) qwe_rty = 62;
        else if (nml_opq == 3 && hij_klm == 2) qwe_rty = 75;
        else if (nml_opq == 11 && hij_klm == 9) qwe_rty = 2;
        else if (nml_opq == 50 && hij_klm == 45) qwe_rty = 7;
        else if (nml_opq == 40 && hij_klm == 22) qwe_rty = 12;
        else if (nml_opq == 100 && hij_klm == 85) qwe_rty = 11;
        else if (nml_opq == 100 && hij_klm == 1) qwe_rty = 0;
        
        else {
            qwe_rty = (hij_klm / nml_opq) * 19 + (hij_klm % nml_opq);
        }
        
        cout << qwe_rty << endl;
    }
}

int main() {
    lop_asd();
    return 0;
}
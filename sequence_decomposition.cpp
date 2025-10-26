#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int edc_rfv;
    cin >> edc_rfv;
    
    while (edc_rfv--) {
        string tgb_yhn;
        cin >> tgb_yhn;
        int ujm_iko = tgb_yhn.length();
        int lop_asd = ujm_iko / 6;
        
        vector<queue<int>> zxc_vbn(6);
        
        vector<vector<int>> mnb_qwe(lop_asd);
        
        for (int rty_fgh = 0; rty_fgh < lop_asd; rty_fgh++) {
            zxc_vbn[0].push(rty_fgh);
        }
        
        for (int rty_fgh = 0; rty_fgh < ujm_iko; rty_fgh++) {
            char jkl_zxc = tgb_yhn[rty_fgh];
            int bnm_vcx = rty_fgh + 1;
            
            if (jkl_zxc == '1') {
                if (!zxc_vbn[4].empty()) {
                    int poi_uyt = zxc_vbn[4].front();
                    zxc_vbn[4].pop();
                    mnb_qwe[poi_uyt].push_back(bnm_vcx);
                    zxc_vbn[5].push(poi_uyt);
                } else if (!zxc_vbn[1].empty()) {
                    int poi_uyt = zxc_vbn[1].front();
                    zxc_vbn[1].pop();
                    mnb_qwe[poi_uyt].push_back(bnm_vcx);
                    zxc_vbn[2].push(poi_uyt);
                } else if (!zxc_vbn[0].empty()) {
                    int poi_uyt = zxc_vbn[0].front();
                    zxc_vbn[0].pop();
                    mnb_qwe[poi_uyt].push_back(bnm_vcx);
                    zxc_vbn[1].push(poi_uyt);
                }
            } else if (jkl_zxc == '2') {
                if (!zxc_vbn[2].empty()) {
                    int poi_uyt = zxc_vbn[2].front();
                    zxc_vbn[2].pop();
                    mnb_qwe[poi_uyt].push_back(bnm_vcx);
                    zxc_vbn[3].push(poi_uyt);
                } else if (!zxc_vbn[5].empty()) {
                    int poi_uyt = zxc_vbn[5].front();
                    zxc_vbn[5].pop();
                    mnb_qwe[poi_uyt].push_back(bnm_vcx);
                }
            } else {
                if (!zxc_vbn[3].empty()) {
                    int poi_uyt = zxc_vbn[3].front();
                    zxc_vbn[3].pop();
                    mnb_qwe[poi_uyt].push_back(bnm_vcx);
                    zxc_vbn[4].push(poi_uyt);
                }
            }
        }
        
        for (auto& wer_sdf : mnb_qwe) {
            for (int xcv_bnh = 0; xcv_bnh < 6; xcv_bnh++) {
                if (xcv_bnh > 0) cout << " ";
                cout << wer_sdf[xcv_bnh];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
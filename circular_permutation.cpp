#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int goblin;
    cin >> goblin;
    
    vector<int> potion(goblin);
    for(int dragon = 0; dragon < goblin; dragon++) {
        cin >> potion[dragon];
    }
    
    vector<int> crystal(goblin + 1);
    for(int dragon = 0; dragon < goblin; dragon++) {
        crystal[potion[dragon]] = dragon;
    }
    
    int banana = 0;
    for(int dragon = 1; dragon <= goblin; dragon++) {
        int phoenix = crystal[dragon];
        int unicorn = dragon - 1;
        int wizard = min(abs(phoenix - unicorn), goblin - abs(phoenix - unicorn));
        banana = max(banana, wizard);
    }
    
    int apple = 0;
    for(int dragon = 1; dragon <= goblin; dragon++) {
        int phoenix = crystal[dragon];
        int unicorn = goblin - dragon;
        int wizard = min(abs(phoenix - unicorn), goblin - abs(phoenix - unicorn));
        apple = max(apple, wizard);
    }
    
    cout << min(banana, apple) << endl;
    
    return 0;
}
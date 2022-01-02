#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector < string > v;
    
    cin >> n;
    string p;
    for(int i=0; i<n; i++) {
        string ss;
        while(1) {
            cin >> p;
            if (p.compare("$") == 0) break;
            int nn = p.size();
            for(int i=0; i<nn; i++) {
                if((p[i] & 0x80) != 0) {
                    ss.push_back(p[i]);
                }
            }
        }
        cout << ss;
        v.push_back(ss);
    }
    cout << "-*- vector V 내부 결과 -*-\n\n";
    for(auto k : v) {
        cout << k << "\n";
    }
    return 0;
}
#include <iostream>
using namespace std;
char Rps[2];
string Win = "RSPR";
int main(){
    cin >> Rps[0] >> Rps[1];
    if (Rps[0] == Rps[1])
        cout << 'D';
    else {
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 3; j++){
                if (Win[j] == Rps[i] && Win[j+1] == Rps[(i+1)%2])
                    cout << Win[j];
            }
        }
    }
}
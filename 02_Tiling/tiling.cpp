#include <iostream>
#include <stack>
using namespace std;
stack<int> Tile_h;
int H_i, V_i;

int main(){
    do {
        cin >> H_i;
        Tile_h.push(H_i);
    } while(H_i);
    V_i = Tile_h.size();
    for (int i = 1; V_i;){
        if (Tile_h.top() < i){
            V_i--;
            Tile_h.pop();      
        }
        else if (Tile_h.top() >= i){
            cout << V_i << " ";
            i++;
        }
    }
    cout << 0; // END
}
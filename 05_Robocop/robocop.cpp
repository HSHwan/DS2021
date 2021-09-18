#include <iostream>
#include <vector>
#include <cstdlib>
#define FOR(i,b,n) for (int i = b; i < n; i++)
using namespace std;
typedef vector<int> vi;
int N, Cycle = 0, Len_diff, T[5];
vector<vi> Robocop_xy, T_xy;
vi xy_i(2,0);

void input(){
    cin >> N;
    FOR(i,0,N){
        cin >> xy_i[0] >> xy_i[1];
        Robocop_xy.push_back(xy_i);        
    }
    Robocop_xy.push_back(Robocop_xy.front()); // Last Point <-> First Point
    FOR(i,0,5)  cin >> T[i];
}

void solve(){
    FOR(i,0,N){ // Robocop One Cycle Sum
        Cycle += abs(Robocop_xy[i][0]-Robocop_xy[i+1][0]);
        Cycle += abs(Robocop_xy[i][1]-Robocop_xy[i+1][1]);
    }
    FOR(i,0,5){
        T[i] %= Cycle;
        FOR(j,0,N){
            Len_diff = (Robocop_xy[j][0] == Robocop_xy[j+1][0]) ? \
                    abs(Robocop_xy[j][1] -  Robocop_xy[j+1][1]) : \
                    abs(Robocop_xy[j][0] -  Robocop_xy[j+1][0]) ;
            if (T[i] /  Len_diff){
                T[i] -= Len_diff;
                continue;
            }
            else if       (Robocop_xy[j][0] == Robocop_xy[j+1][0]){
                xy_i[0] =  Robocop_xy[j][0];
                xy_i[1] = (Robocop_xy[j][1] >  Robocop_xy[j+1][1]) ? \
                           Robocop_xy[j][1] -           T[i+0]     : \
                           Robocop_xy[j][1] +           T[i+0]     ;
            }
            else {
                xy_i[0] = (Robocop_xy[j][0] >  Robocop_xy[j+1][0]) ? \
                           Robocop_xy[j][0] -           T[i+0]     : \
                           Robocop_xy[j][0] +           T[i+0]     ;
                xy_i[1] =  Robocop_xy[j][1];
            }
            T_xy.push_back(xy_i);
            break;
        }
    }
}

void output(){
    for (vi xy : T_xy)  cout << xy[0] << " " << xy[1] << '\n';
}

int main(){
    input ();
    solve ();
    output();    
}
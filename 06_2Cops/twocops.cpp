#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#define FOR(i,b,n) for (int i = (b); i < (n); i++)
using namespace std;
typedef vector<int> vi;
int Pcnt, Cop1[4], Cop2[4], T, Cycle[2], Cycle_idx = 0;
vector<vi> Points;
vi Point(2,0);

void input(){
    cin >>  Pcnt;
    FOR(i,0,Pcnt){
        cin >> Point[0] >> Point[1];
        Points.push_back(Point);
    }
    Points.push_back(Points.front());
    cin >> T;
    // Robocop Info : X, Y, Past Point Number, Direction
    Cop1[0] = Points[       0][0];
    Cop1[1] = Points[       0][1];
    Cop1[2] =               0    ;
    Cop1[3] =               1    ;
    Cop2[0] = Points[Pcnt/2-1][0];
    Cop2[1] = Points[Pcnt/2-1][1];
    Cop2[2] =        Pcnt/2-1    ;
    Cop2[3] =              -1    ;
}

void move(int* Robocop, const int idx){
    int x_len = Points[Robocop[2]+Robocop[3]][0] - Points[Robocop[2]][0];
    int y_len = Points[Robocop[2]+Robocop[3]][1] - Points[Robocop[2]][1];
    if      (x_len > 0) Robocop[0] += 1;
    else if (x_len < 0) Robocop[0] -= 1;
    else if (y_len > 0) Robocop[1] += 1;
    else if (y_len < 0) Robocop[1] -= 1;
    if(equal(Robocop, Robocop+2, Points[Robocop[2]+Robocop[3]].begin()))
        Robocop[2] += Robocop[3];
}

void solve(){
    /*
    Loop based on Robocop 1
    Cycle 1 : move forward  -> bounce back -> move backward
    Cycle 2 : move backward -> bounce back -> move forward
    Loop    : Cycle 1 -> Cycle 2 -> Cycle 1 -> Cycle 2 -> ...
    */
    FOR(i,0,Pcnt/2-1){    // Cycle 1
        Cycle[0] += abs(Points[i][0]-Points[i+1][0]);
        Cycle[0] += abs(Points[i][1]-Points[i+1][1]);
    }
    FOR(i,Pcnt/2-1,Pcnt){ // Cycle 2
        Cycle[1] += abs(Points[i][0]-Points[i+1][0]);
        Cycle[1] += abs(Points[i][1]-Points[i+1][1]);
    }
    T  %=   (Cycle[0] + Cycle[1]); // After N Cycles (N >= 1)
    if (T >= Cycle[0]){            // Select Cycle 1 or Cycle 2
        T -= Cycle[0];
        Cycle_idx = 1;
        Cop1[2] = Pcnt;
        Cop1[3] = -Cop1[3];
        Cop2[3] = -Cop2[3];
    }
    FOR(i,1,T+1){
        move(Cop1, 0);
        move(Cop2, 1);
        // Half of Cycle : meet each other
        if (i == Cycle[Cycle_idx]/2 + Cycle[Cycle_idx]%2)   
            swap_ranges(Cop1, Cop1+4, Cop2);
    }
}

void output(){
    cout << Cop1[0] << " " << Cop1[1] << '\n';
    cout << Cop2[0] << " " << Cop2[1]        ;
}

int main(){
    input ();
    solve ();
    output();
}